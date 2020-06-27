#include "run_test.h"
#include "core/list.h"

struct node {
  struct list_head head;
  int index;
};

UNIT_TEST(doubly_list) {
#define NODE_NUM 10
  int i;
  struct node nodes[NODE_NUM];
  struct list_head* pos, *next;
  LIST_HEAD(l);

  for (i = 0; i < NODE_NUM; ++i) {
    INIT_LIST_HEAD(&nodes[i].head);
    nodes[i].index = i;
  }

  assert_true(list_empty(&l));
  for (i = 0; i < NODE_NUM; ++i) {
    list_add_tail(&nodes[i].head, &l);
  }
  assert_true(!list_empty(&l));
  assert_int_equal(list_count_entries(&l), NODE_NUM);

  assert_true(list_entry_is_first(&nodes[0].head, &l));
  assert_true(list_entry_is_last(&nodes[NODE_NUM - 1].head, &l));

  i = 0;
  printf(">> ");
  list_for_each_safe(pos, next, &l) {
    struct node *entry = list_entry(pos, struct node, head);
    assert_true(pos && entry);
    assert_int_equal(i, entry->index);
    printf("%d ", entry->index);
    ++i;
  }
  printf("\n");

  i = NODE_NUM - 1;
  printf(">> ");
  list_for_each_backwardly(pos, &l) {
    struct node *entry = list_entry(pos, struct node, head);
    assert_true(pos && entry);
    assert_int_equal(i, entry->index);
    printf("%d ", entry->index);
    --i;
  }
  printf("\n");

  list_for_each_safe(pos, next, &l) {
    list_del_init(pos);
  }
  assert_true(list_empty(&l));
}
