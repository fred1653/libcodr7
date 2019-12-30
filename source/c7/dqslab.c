#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "c7/dqslab.h"
#include "c7/dqpool.h"

struct c7_dqslab *c7_dqslab_new(struct c7_dqpool *pool) {
  return c7_dqslab_init(malloc(sizeof(struct c7_dqslab) +
			       pool->slab_size * pool->item_size));
}

struct c7_dqslab *c7_dqslab_init(struct c7_dqslab *slab) {
  slab->front = slab->back = 0;
  return slab;
}

void *c7_dqslab_get(struct c7_dqslab *slab, struct c7_dqpool *pool, uint16_t i) {
  return slab->items + i * pool->item_size;
}

uint16_t c7_dqslab_count(struct c7_dqslab *slab) {
  return slab->back - slab->front;
}

void *c7_dqslab_front(struct c7_dqslab *slab, struct c7_dqpool *pool) {
  return c7_dqslab_get(slab, pool, slab->front);
}

void *c7_dqslab_push_front(struct c7_dqslab *slab, struct c7_dqpool *pool) {
  return c7_dqslab_get(slab,
		       pool,
		       slab->front ? --slab->front : slab->back++);
}

void c7_dqslab_pop_front(struct c7_dqslab *slab) {
  slab->front++;
}

void *c7_dqslab_back(struct c7_dqslab *slab, struct c7_dqpool *pool) {
  return c7_dqslab_get(slab, pool, slab->back - 1);
}

void *c7_dqslab_push_back(struct c7_dqslab *slab, struct c7_dqpool *pool) {
  return c7_dqslab_get(slab, pool, slab->back++);
}

void c7_dqslab_pop_back(struct c7_dqslab *slab) {
  slab->back--;
}
