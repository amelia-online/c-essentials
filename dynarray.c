#include "dynarray.h"
#include <stdlib.h>
#include <stdbool.h>

BitVec BitVecMake()
{
  return (BitVec)
    {
      .array = malloc(sizeof(unsigned char)),
      .cap = 8,
      .size = 0,
      .top = 0,
      .byte = 0;
    };
}

void BitVecFree(BitVec *v)
{
  free(v->array);
}

void BitVecResize(BitVec *v)
{
  v->array = realloc(v->array, v->cap/8 * 2);
  v->cap *= 2;
}

void BitVecPush(BitVec *v, bool bit)
{
  if (v->size + 1 >= v->cap)
    BitVecResize(v);

  if (!bit)
    {
      v->top++;
      v->size++;
      return;
    }
  
  int idx = v->top / 8;
  int bitIdx = v->top % 8;
  v->array[idx] = v->array[idx] | (128 >> bitIdx);
  v->top++;
  v->size++;
}

bool *BitVecPop(BitVec *v)
{
  if (v->size == 0)
    return NULL;

  bool *res = malloc(sizeof(bool));

  int byte = v->top / 8;
  int idx = v->top % 8;

  *res = (bool) (v->array[byte] >> (8-idx)) & 1;

  v->size--;
  v->top--;
  
  return res;
}

bool *BitVecPeek(const BitVec *v)
{
  if (v->size == 0)
    return NULL;

  bool *res = malloc(sizeof(bool));

  int byte = v->top / 8;
  int idx = v->top % 8;

  *res = (bool) (v->array[byte] >> (8-idx)) & 1;
  
  return res;
}

bool *BitVecGet(const BitVec *v, int idx)
{
  if (idx < 0 || idx > v->size)
    return NULL;

  bool *res = malloc(sizeof(bool));
  int byte = idx / 8;
  int bitIdx = idx % 8;

  *res = (bool) (v->array[byte] >> (8-bitIdx)) & 1;
  
  return res;
}

void BitVecRemove(BitVec *v, int idx)
{
  if (idx < 0 || idx > v->size)
    return;

  for (int i = idx; i < v->top-1; i++)
    {
      int backByte = i / 8;
      int backBitIdx = i % 8;

      int frontByte = (i+1)/8;
      int frontBitIdx = (i+1)%8;

      char frontBit = (char)(v->array[frontByte] >> (8-frontBitIdx)) & 1;
      v->array[backByte] = v->array[backByte] | (frontBit << backByteIdx);
      
      

    }

}
