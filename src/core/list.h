/*
 * Copyright (C) 2008 Karel Zak <kzak@redhat.com>
 * Copyright (C) 1999-2008 by Theodore Ts'o
 *
 * This file may be redistributed under the terms of the
 * GNU Lesser General Public License.
 *
 * (based on list.h from e2fsprogs)
 * Merge sort based on kernel's implementation.
 */

#ifndef ASYNC_LIST_H
#define ASYNC_LIST_H

#include "async.h"

#define LIST_HEAD_INIT(name) { &(name), &(name) }

#define LIST_HEAD(name) as_list_head_t name = LIST_HEAD_INIT(name)

#define INIT_LIST_HEAD(ptr) \
    do { (ptr)->next = (ptr); (ptr)->prev = (ptr); } while (0)

AS_INLINE void
__list_add (as_list_head_t* add,
            as_list_head_t* prev,
            as_list_head_t* next) {
  next->prev = add;
  add->next = next;
  add->prev = prev;
  prev->next = add;
}

AS_INLINE void
list_add (as_list_head_t* add, as_list_head_t* head) {
  __list_add(add, head, head->next);
}

AS_INLINE void
list_add_tail (as_list_head_t* add, as_list_head_t* head) {
  __list_add(add, head->prev, head);
}

AS_INLINE void
__list_del (as_list_head_t* prev, as_list_head_t* next) {
  next->prev = prev;
  prev->next = next;
}

AS_INLINE void
list_del (as_list_head_t* entry) {
  __list_del(entry->prev, entry->next);
}

AS_INLINE void
list_del_init (as_list_head_t* entry) {
  __list_del(entry->prev, entry->next);
  INIT_LIST_HEAD(entry);
}

AS_INLINE int
list_empty (as_list_head_t* head) {
  return head->next == head;
}

AS_INLINE int
list_entry_is_last (as_list_head_t* entry, as_list_head_t* head) {
  return head->prev == entry;
}

AS_INLINE int
list_entry_is_first (as_list_head_t* entry, as_list_head_t* head) {
  return head->next == entry;
}

AS_INLINE void
list_splice (as_list_head_t* list, as_list_head_t* head) {
  as_list_head_t* first = list->next;

  if (first != list) {
    as_list_head_t *last = list->prev;
    as_list_head_t *at = head->next;

    first->prev = head;
    head->next = first;

    last->next = at;
    at->prev = last;
  }
}

#define list_entry(ptr, type, member) \
    container_of(ptr, type, member)

#define list_first_entry(head, type, member) \
    ((head) && (head)->next != (head) ? list_entry((head)->next, type, member) : NULL)

#define list_last_entry(head, type, member) \
    ((head) && (head)->prev != (head) ? list_entry((head)->prev, type, member) : NULL)

#define list_for_each(pos, head) \
    for (pos = (head)->next; pos != (head); pos = pos->next)

#define list_for_each_backwardly(pos, head) \
    for (pos = (head)->prev; pos != (head); pos = pos->prev)

#define list_for_each_safe(pos, pnext, head) \
    for (pos = (head)->next, pnext = pos->next; pos != (head); \
         pos = pnext, pnext = pos->next)

AS_INLINE size_t
list_count_entries (as_list_head_t *head) {
  as_list_head_t *pos;
  size_t ct = 0;

  list_for_each(pos, head)
    ct++;

  return ct;
}

#endif
