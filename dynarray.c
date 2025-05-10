#include "dynarray.h"
#include <stdlib.h>
#include <stdio.h>

GENERIC_VEC(int, IntVec)

IntVec IntVecMake()
{
  return (IntVec)
  {
    .size = 0,
    .array = malloc(sizeof(int)*8)
  };
}

int main()
{
  IntVec vec = IntVecMake();
  printf("%lld\n", vec.size);
  return 0;
}
