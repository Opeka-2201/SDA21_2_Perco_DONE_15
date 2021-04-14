#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "UnionFind.h"

typedef struct tree_node_t TreeNode;

struct tree_node_t{
  size_t nodeIndex;
  TreeNode* parent;
};

struct union_find_t{
  TreeNode** nodes;
  size_t totalTrees;
  size_t size;
};

TreeNode* newNode(size_t,TreeNode*);
void freeNodeTable(TreeNode**,size_t);
size_t getIndex(TreeNode*);
TreeNode* getRoot(TreeNode* node);

UnionFind* ufCreate(size_t n_items){
  UnionFind* UnionFind = malloc(sizeof(UnionFind));
  if(UnionFind == NULL){
    fprintf(stderr, "Erreur d'allocation de mémoire\n");
    abort();
  }

  TreeNode** nodesTable = (TreeNode**)malloc(n_items*sizeof(TreeNode*));
  if(nodesTable == NULL){
    fprintf(stderr, "Erreur d'allocation de mémoire\n");
    abort();
  }
  for(int i = 0; i < (int)n_items ; i++){
    nodesTable[i] = newNode(i,NULL);
  }

  UnionFind->nodes = nodesTable;
  UnionFind->totalTrees = n_items;
  UnionFind->size = n_items;

  return UnionFind;
}

void ufFree(UnionFind* union_find){
  freeNodeTable(union_find->nodes,union_find->size);
  free(union_find);
}

ufStatus ufUnion(UnionFind* union_find, size_t item1, size_t item2){
  fprintf(stderr, "%zu , %zu\n",item1, item2);

  TreeNode** nodes = union_find->nodes;

  if(item1 == item2)
    return UF_SAME;

  if(nodes[item1] == NULL || nodes[item2] == NULL)
    return UF_ERROR;

  fprintf(stderr,"%s\n","SUS");

  size_t indexItem1 = getIndex(nodes[item1]);
  size_t indexItem2 = getIndex(nodes[item2]);

  fprintf(stderr, "%s\n", "OH OH");

  TreeNode* rootItem1 = getRoot(nodes[item1]);
  TreeNode* rootItem2 = getRoot(nodes[item2]);

  fprintf(stderr,"%s\n","AMOGUS");

  if(rootItem1 == rootItem2)
    return UF_SAME;

  if(indexItem1 <= indexItem2)
    rootItem1->parent = rootItem2;
  else
    rootItem2->parent = rootItem1;

  union_find->totalTrees--;
  return UF_MERGED;
}

size_t ufFind(const UnionFind* union_find, size_t item){
  TreeNode* node = union_find->nodes[item];
  TreeNode* copy = node;
  if (copy->parent == copy)
    return copy->nodeIndex;
  while(copy->parent != NULL)
    copy = copy->parent;
  node->parent = copy;
  return copy->nodeIndex;
}

size_t ufComponentsCount(const UnionFind* union_find){
  return union_find->totalTrees;
}

TreeNode* newNode(size_t nodeIndex, TreeNode* parent){
  TreeNode* toReturn = (TreeNode*)malloc(sizeof(TreeNode));
  if(toReturn == NULL){
    fprintf(stderr, "Erreur d'allocation de mémoire\n");
    abort();
  }

  toReturn->nodeIndex = nodeIndex;
  toReturn->parent = parent;

  return toReturn;
}

void freeNodeTable(TreeNode** nodesTable, size_t size){
  for(int i = 0; i < (int)size; i++){
    free(nodesTable[i]);
  }
  free(nodesTable);
}

size_t getIndex(TreeNode* node){
  size_t index = 0;
  while(node->parent != NULL){
    node = node->parent;
    index++;
  }
  fprintf(stderr, "%zu\n",index);
  return index;
}

TreeNode* getRoot(TreeNode* node){
  while(node->parent != NULL)
    node = node->parent;
  return node;
}
