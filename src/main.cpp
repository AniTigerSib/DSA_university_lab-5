#include <clocale>
#include <iostream>
#include <random>

#include "btree.h"
#define NUM_OF_TESTS 10
// Variant #6

typedef enum TypeOfKeys {
  RANDOM,
  ORDERED
} TypeOfKeys;

pNode MakeRandomisedBtree(char type, int size);
pNode MakeSimpleBtree(char type, int size);
int RandomInt();

int main(int argc, char** argv) {
  setlocale(LC_ALL, "Russian");
  int step = atoi(argv[1]);
  int size = step;
  for (int i = 0; i < NUM_OF_TESTS; i++) {
    std::cout << size << "\t";
    for (int j = 0; j < 2; j++) {
      pNode root = nullptr;
      if (atoi(argv[2]) == 1) {
        root = MakeSimpleBtree(j, size);\
      } else {
        root = MakeRandomisedBtree(j, size);
      }
      std::cout << GetHeight(root) << "\t";
      DestroyBtree(root);
    }
    std::cout << "\n";
    std::cout.flush();
    size += step;
  }
}

pNode MakeRandomisedBtree(char type, int size) {
  pNode root = nullptr;
  for (int i = 0; i < size; ++i) {
    if (type == RANDOM) {
      InsertRoot(&root, RandomInt());
    } else {
      InsertRoot(&root, i);
    }
  }
  return root;
}

pNode MakeSimpleBtree(char type, int size) {
  pNode root = nullptr;
  for (int i = 0; i < size; ++i) {
    if (type == RANDOM) {
      Insert(&root, RandomInt());
    } else {
      Insert(&root, i);
    }
  }
  return root;
}

int RandomInt() {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> distrib(1, 100);
  return distrib(gen);
}