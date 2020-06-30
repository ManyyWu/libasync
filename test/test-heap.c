#include "run_test.h"
#include "heap.h"

struct myheap_node {
  struct heap_node node;
  int data;
};

#define INIT_MYNODE(node) do { (node).parent = (node).left = (node).right = NULL; } while (0)

static unsigned int
Log2(unsigned int n) {
  unsigned int ans;

  ans = 0;
  while (n >>= 1)
    ans++;

  return ans;
}

static void
print_heap(int array[], int count) {
  int depth, i, j, k, w, index;

  index = 0;
  depth = (int) Log2(count) + 1;

  for (j = 0; j < depth; j++) {
    w = 1 << (depth - j + 1);
    if (j == 0)
      printf("%*c\n", w, '_');
    else {
      for (i = 0; i < 1 << (j - 1); i++) {
        printf("%*c", w + 1, ' ');
        for (k = 0; k < w - 3; k++)
          printf("_");
        printf("/ \\");
        for (k = 0; k < w - 3; k++)
          printf("_");
        printf("%*c", w + 2, ' ');
      }
      printf("\n");
      for (i = 0; i < 1 << (j - 1); i++)
        printf("%*c/%*c_%*c", w, '_', w * 2 - 2, '\\', w, ' ');
      printf("\n");
    }
    for (i = 0; i < 1 << j; i++)
      if (index < count)
        printf("%*c%-3d)%*c", w - 1, '(', array[index++], w - 3, ' ');
      else
        printf("%*c%s)%*c", w - 1, '(', "___", w - 3, ' ');
    printf("\n");
  }
}


static
int
less_than (const struct heap_node* a, const struct heap_node* b) {
  return (((struct myheap_node *)a)->data < ((struct myheap_node *)b)->data);
}

UNIT_TEST(heap) {
  int i;
  int array[] = {43, 24, 3, 42, 45, 4, 75, 7, 24, 87, 32, 23, 3, 42, 4, 42, 42, 9};
  int result[] = {3, 3, 4, 4, 7, 9, 23, 24, 24, 32, 42, 42, 42, 42, 43, 45, 75, 87};
#define NODE_NUM (sizeof(array) / sizeof(array[0]))
  int temp[NODE_NUM];
  struct heap h;
  struct heap_node *min;
  struct myheap_node nodes[NODE_NUM];

  heap_init(&h, less_than);
  for (i = 0; i < NODE_NUM; ++i) {
    INIT_MYNODE(nodes[i].node);
    nodes[i].data = array[i];
    heap_insert(&h, &nodes[i].node);
  }
  assert_int_equal(h.count, NODE_NUM);

  for (i = 0; i < NODE_NUM; ++i) {
    min = heap_min(&h);
    assert_true(min);
    temp[i] = ((struct myheap_node *)min)->data;
    assert_int_equal(((struct myheap_node *)min)->data, result[i]);
    heap_pop(&h);
  }
  //print_heap(temp, NODE_NUM);
  assert_true(!heap_min(&h));
}
