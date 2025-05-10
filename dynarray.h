#ifndef ESSENTIALS_VEC_H
#define ESSENTIALS_VEC_H

#define DEF_GENERIC_VEC(TYPE, NAME) \
  typedef struct { \
    int64_t size; \
    TYPE *array; \
    int64_t top; \
    int64_t cap; \
  } NAME;
#define GENERIC_VEC_HEADERS(TYPE, NAME) \
  NAME NAME##Make(); \
  void NAME##Free(NAME *); \
  void NAME##Push(NAME *, TYPE);			\
  TYPE NAME##Pop(NAME *); \
  TYPE NAME##Peek(const NAME *); \
  TYPE NAME##Get(const NAME *, int);		\
  void NAME##Remove(NAME *, int);		\
  void NAME##Resize(NAME *);

#define IMPL_GENERIC_VEC(TYPE, NAME) \
  NAME NAME##Make() { \
    return (NAME) { \
      .size = 0, \
      .top = 0; \
      .array = malloc(sizeof(TYPE)*16); \
    }; \
  } \
  void NAME##Free(NAME *x) { \
    free(x->array); \
  } \
  void NAME##Push(NAME *v, TYPE t) {		\
    if (v->size + 1 >= cap) \
       NAME##Resize(v); \
    v->array[v->top] = t; \
    v->top++; \
  } \
  TYPE NAME##Pop(NAME *v) { \
    
  
  

#define GENERIC_VEC(TYPE, NAME) \
  DEF_GENERIC_VEC(TYPE, NAME) \
    GENERIC_VEC_HEADERS(TYPE, NAME) \
    IMPL_GENERIC_VEC(TYPE, NAME) 

#endif // ESSENTIALS_VEC_H
