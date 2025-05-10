#ifndef ESSENTIALS_VEC_H
#define ESSENTIALS_VEC_H

#include <stdlib.h>
#include <stdbool.h>

#define DEF_GENERIC_VEC(TYPE, NAME) \
  typedef struct {		    \
    int64_t size;		    \
    TYPE *array;		    \
    int64_t top;		    \
    int64_t cap;		    \
  } NAME;
#define GENERIC_VEC_HEADERS(TYPE, NAME)			\
  NAME NAME##Make();					\
  void NAME##Free(NAME *);				\
  void NAME##Push(NAME *, TYPE);			\
  TYPE *NAME##Pop(NAME *);				\
  TYPE *NAME##Peek(const NAME *);			\
  TYPE *NAME##Get(const NAME *, int);			\
  void NAME##Remove(NAME *, int);			\
  void NAME##Resize(NAME *);

#define IMPL_GENERIC_VEC(TYPE, NAME)				\
  NAME NAME##Make() {						\
    return (NAME) {						\
      .size = 0,						\
      .top = 0;							\
      .array = malloc(sizeof(TYPE)*16);				\
    };								\
  }								\
  void NAME##Free(NAME *x) {					\
    free(x->array);						\
  }								\
  void NAME##Push(NAME *v, TYPE t) {				\
    if (v->size + 1 >= cap)					\
      NAME##Resize(v);						\
    v->array[v->top] = t;					\
    v->top++;							\
    v->size++;							\
  }								\
  TYPE *NAME##Pop(NAME *v) {					\
    if (v->size == 0)						\
      return NULL;						\
    TYPE *res = malloc(sizeof(TYPE));				\
    *res = v->array[v->top];					\
    v->top -= 1;						\
    v->size -= 1;						\
    return res;							\
  }								\
  TYPE *NAME##Peek(NAME *v) {					\
    if (v->size == 0)						\
      return NULL;						\
    TYPE *res = malloc(sizeof(TYPE));				\
    *res = v->array[v->top];					\
    return res;							\
  }								\
  TYPE *NAME##Get(const NAME *v, int idx) {			\
  if (idx < 0 || idx > v->size-1)				\
    return NULL;						\
  TYPE *res = malloc(sizeof(TYPE));				\
  *res = v->array[idx];						\
  return res;							\
  }								\
   void NAME##Remove(NAME *v, int idx) {			\
     if (idx < 0 || idx > v->size-1)				\
       return;							\
     for (int i = idx; i < v->size-1; idx++) {			\
       v->array[i] = v->array[i+1];				\
     }								\
     v->top--;							\
     v->size--;							\
   }								\
   void NAME##Resize(NAME *v) {					\
     v->array = realloc(v->array, v->cap * 2 * sizeof(TYPE));	\
     v->cap *= 2;						\
   }						
     

#define GENERIC_VEC(TYPE, NAME)	    \
  DEF_GENERIC_VEC(TYPE, NAME)	    \
    GENERIC_VEC_HEADERS(TYPE, NAME) \
    IMPL_GENERIC_VEC(TYPE, NAME)

typedef struct {
  unsigned char *array;
  int64_t size;
  int64_t cap;
  int64_t top;
  int64_t byte;
} BitVec;

BitVec BitVecMake();
void BitVecFree(BitVec *);
void BitVecPush(BitVec *, bool);
bool *BitVecPop(BitVec *);
bool *BitVecPeek(const BitVec *);
bool *BitVecGet(const BitVec *, int);
void BitVecRemove(BitVec *, int);
void BitVecResize(BitVec *);

#endif // ESSENTIALS_VEC_H
