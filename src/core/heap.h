#ifndef ASYNC_HEAP_H
#define ASYNC_HEAP_H

struct heap_node {
  struct heap_node *left;
  struct heap_node *right;
  struct heap_node *parent;
};

typedef int (*heap_compare_fn) (const struct heap_node *a, const struct heap_node *b);

struct heap {
  struct heap_node *min;
  unsigned int      count;
  heap_compare_fn   less_than;
};

AS_INLINE void
heap_init (struct heap *heap, heap_compare_fn less_than) {
  heap->min = NULL;
  heap->count = 0;
  heap->less_than = less_than;
}

AS_INLINE struct heap_node*
heap_min (const struct heap *heap) {
  return heap->min;
}

AS_INLINE void
heap_node_swap (struct heap *heap, struct heap_node *parent, struct heap_node *child) {
  struct heap_node *sibling;
  struct heap_node t;

  t = *parent;
  *parent = *child;
  *child = t;

  parent->parent = child;
  if (child->left == child) {
    child->left = parent;
    sibling = child->right;
  } else {
    child->right = parent;
    sibling = child->left;
  }
  if (sibling != NULL)
    sibling->parent = child;

  if (parent->left != NULL)
    parent->left->parent = parent;
  if (parent->right != NULL)
    parent->right->parent = parent;

  if (child->parent == NULL)
    heap->min = child;
  else if (child->parent->left == parent)
    child->parent->left = child;
  else
    child->parent->right = child;
}

AS_INLINE void
heap_insert (struct heap *heap, struct heap_node *newnode) {
  struct heap_node **parent;
  struct heap_node **child;
  unsigned int path;
  unsigned int n;
  unsigned int k;

  newnode->left = NULL;
  newnode->right = NULL;
  newnode->parent = NULL;

  path = 0;
  for (k = 0, n = 1 + heap->count; n >= 2; k += 1, n /= 2)
    path = (path << 1) | (n & 1);

  parent = child = &heap->min;
  while (k > 0) {
    parent = child;
    if (path & 1)
      child = &(*child)->right;
    else
      child = &(*child)->left;
    path >>= 1;
    k -= 1;
  }

  newnode->parent = *parent;
  *child = newnode;
  heap->count += 1;

  while (newnode->parent != NULL && heap->less_than(newnode, newnode->parent))
    heap_node_swap(heap, newnode->parent, newnode);
}

AS_INLINE void
heap_remove (struct heap *heap, struct heap_node *node) {
  struct heap_node *smallest;
  struct heap_node **max;
  struct heap_node *child;
  unsigned int path;
  unsigned int k;
  unsigned int n;

  if (heap->count == 0)
    return;

  path = 0;
  for (k = 0, n = heap->count; n >= 2; k += 1, n /= 2)
    path = (path << 1) | (n & 1);

  max = &heap->min;
  while (k > 0) {
    if (path & 1)
      max = &(*max)->right;
    else
      max = &(*max)->left;
    path >>= 1;
    k -= 1;
  }

  heap->count -= 1;

  child = *max;
  *max = NULL;

  if (child == node) {
    if (child == heap->min) {
      heap->min = NULL;
    }
    return;
  }

  child->left = node->left;
  child->right = node->right;
  child->parent = node->parent;

  if (child->left != NULL) {
    child->left->parent = child;
  }

  if (child->right != NULL) {
    child->right->parent = child;
  }

  if (node->parent == NULL) {
    heap->min = child;
  } else if (node->parent->left == node) {
    node->parent->left = child;
  } else {
    node->parent->right = child;
  }

  for (;;) {
    smallest = child;
    if (child->left != NULL && heap->less_than(child->left, smallest))
      smallest = child->left;
    if (child->right != NULL && heap->less_than(child->right, smallest))
      smallest = child->right;
    if (smallest == child)
      break;
    heap_node_swap(heap, child, smallest);
  }

  while (child->parent != NULL && heap->less_than(child, child->parent))
    heap_node_swap(heap, child->parent, child);
}

AS_INLINE void
heap_pop (struct heap *heap) {
  heap_remove(heap, heap->min);
}

#endif