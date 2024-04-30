#include "btree.h"

#include <functional>
#include <iostream>

// Creation of node
pNode NewNode(Data data) {
  pNode node = new BtreeNode;
  node->data = data;
  node->left = node->right = nullptr;
  return node;
}

// Delete
void Delete(pNode node) {
  if (node) delete node;
}

// Pre-Processing traversal
void PreProcess(pNode root, pFunction Function) {
  if (root != nullptr) {
    Function(root);
    PreProcess(root->left, Function);
    PreProcess(root->right, Function);
  }
}

// Post-Processing traversal
void PostProcess(pNode root, pFunction Function) {
  if (root != nullptr) {
    PostProcess(root->left, Function);
    PostProcess(root->right, Function);
    Function(root);
  }
}

// Insertion
void Insert(pNode* p_root, Data data) {
  pNode root = *p_root;
  if (root == nullptr) {
    *p_root = NewNode(data);
  } else {
    if (data < root->data) {
      Insert(&root->left, data);
    } else {
      Insert(&root->right, data);
    }
  }
}

// Finding
pNode Find(pNode root, pNode* p_parent, int* p_LR, Data data) {
  *p_parent = 0;
  *p_LR = 0;
  while (root) {
    if (data < root->data) {
      *p_parent = root;
      *p_LR = 0;
      root = root->left;
    } else {
      if (data > root->data) {
        *p_parent = root;
        *p_LR = 1;
        root = root->right;
      } else {
        return root;
      }
    }
  }
  return 0;
}

// Search for right mininmum
pNode FindRightMin(pNode root, pNode* p_parent) {
  while (root->left) {
    *p_parent = root;
    root = root->left;
  }
  return root;
}

void DeleteNode(pNode* ROOT, Data D) {
  int LR = 0;
  pNode parent = 0, root = Find(*ROOT, &parent, &LR, D);
  if (root) {
    if (root->left && root->right) {
      pNode MinrightParent = root;
      pNode Minright = FindRightMin(root->right, &MinrightParent);
      Minright->left = root->left;
      MinrightParent->left = Minright->right;
      Minright->right = root->right;
      if (parent) {
        if (LR) {
          parent->right = Minright;
        } else {
          parent->left = Minright;
        }
      } else {
        *ROOT = Minright;
      }
    } else {
      if (parent) {
        if (LR) {
          parent->right = root->right ? root->right : root->left;
        } else {
          parent->left = root->right ? root->right : root->left;
        }
      } else {
        *ROOT = root->right ? root->right : root->left;
        Delete(root);
      }
    }
  }
}

void RotateRight(pNode* pLev0) {
#define Lev0 (*pLev0)
  pNode Lev1 = Lev0->left;
  Lev0->left = Lev1->right;
  Lev1->right = Lev0;
  Lev0 = Lev1;
#undef Lev0
}

void RotateLeft(pNode* pLev0) {
#define Lev0 (*pLev0)
  pNode Lev1 = Lev0->right;
  Lev0->right = Lev1->left;
  Lev1->left = Lev0;
  Lev0 = Lev1;
#undef Lev0
}

void InsertRoot(pNode* proot, Data D) {
#define root (*proot)
  if (!root) {
    root = NewNode(D);
  } else {
    if (D < root->data) {
      InsertRoot(&(root->left), D);
      RotateRight(&(root));
    } else {
      InsertRoot(&(root->right), D);
      RotateLeft(&(root));
    }
  }
#undef root
}

void PrintTree(pNode root) {
  PreProcess(root, [](pNode node) {
    std::cout << "\t" << node->data << "\n";
    std::cout << (node->left ? node->left->data : -1) << "\t\t" << (node->right ? node->right->data : -1) << "\n";
  });
  std::cout << std::endl;
}

int GetHeight(pNode root) {
  if (root == nullptr) {
    return 0;
  }
  return 1 + std::max(GetHeight(root->left), GetHeight(root->right));
}

int count = 0;

static void IncrementCount(pNode node) {
  // static int count = 0;
  count++;
}

int GetNodeCount(pNode root) {
  // int count = 0;
  PostProcess(root, IncrementCount);
  return count;
}

void DestroyBtree(pNode root) {
  PostProcess(root, Delete);
}

int CountVowelsOnEvenLevels(pNode root) {
  int count = 0;
  int level = 0; // Корень дерева считается уровнем 0
  setlocale(LC_ALL, "ru_RU.utf8");
  std::function<void(pNode)> traverse = [&](pNode node) {
    if (node == nullptr) return;
    
    if (level % 2 == 0) { // Проверяем, четный ли уровень
      wchar_t c = tolower(node->data); // Приводим к нижнему регистру для удобства
      if (c == L'а' || c == L'е' || c == L'ё' || c == L'и' || c == L'о' || c == L'у' ||
          c == L'ы' || c == L'э' || c == L'ю' || c == L'я') {
        count++;
      }
    }
    
    level++; // Увеличиваем уровень при спуске
    traverse(node->left);
    traverse(node->right);
    level--; // Уменьшаем уровень при подъеме
  };

  traverse(root);
  return count;
}