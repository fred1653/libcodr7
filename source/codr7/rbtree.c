#include <stddef.h>

#include "codr7/rbtree.h"

void c7_rbtree_init(struct c7_rbtree *tree, 
		    c7_compare_t compare,
		    struct c7_rbpool *pool) {
  tree->compare = compare;
  tree->pool = pool;
  tree->root = NULL;
  tree->count = 0;
}

void c7_rbtree_clear(struct c7_rbtree *tree) {
  if (tree->root) {
    c7_rbnode_deinit(tree->root, tree);
    tree->root = NULL;
    tree->count = 0;
  }
}

void *c7_rbtree_find(struct c7_rbtree *tree, const void *key) {
  return c7_rbnode_find(tree->root, tree, key);
}

void *c7_rbtree_add(struct c7_rbtree *tree, const void *key) {
  void *v = NULL;
  tree->root = c7_rbnode_add(tree->root, tree, key, &v);
  tree->root->red = false;
  return v;
}

void *c7_rbtree_remove(struct c7_rbtree *tree, const void *key) {
  void *v = NULL;
  tree->root = c7_rbnode_remove(tree->root, tree, key, &v);
  tree->root->red = false;
  return v;
}
