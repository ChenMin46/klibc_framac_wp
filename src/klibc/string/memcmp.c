/*
 * memcmp.c
 */

#include <string.h>

/*@
  requires n >= 0;
  requires \valid(((char*)s1)+(0..n-1));
  requires \valid(((char*)s2)+(0..n-1));
  requires \separated(((char*)s1)+(0..n-1), ((char*)s2)+(0..n-1));

  assigns \nothing;
  behavior eq:
    assumes n >= 0;
    assumes \forall integer i; 0 <= i < n ==> ((unsigned char*)s1)[i] == ((unsigned char*)s2)[i];
    ensures \result == 0;

  behavior not_eq:
    assumes n > 0;
    assumes \exists integer i; 0 <= i < n && ((unsigned char*)s1)[i] != ((unsigned char*)s2)[i];
    ensures \result != 0;

  complete behaviors;
  disjoint behaviors;
@*/
int memcmp(const void *s1, const void *s2, size_t n)
{
  const unsigned char *c1 = s1, *c2 = s2;
  int d = 0;

  /*@
    loop invariant N_RANGE: 0 <= n <= \at(n, Pre);
    //loop invariant (unsigned char*)s1 <= c1 <= (unsigned char*)s1+\at(n, Pre);
    //loop invariant (unsigned char*)s2 <= c2 <= (unsigned char*)s2+\at(n, Pre);
    loop invariant C1_RANGE: c1 == (unsigned char*)s1+(\at(n,Pre) - n);
    loop invariant C2_RANGE: c2 == (unsigned char*)s2+(\at(n,Pre) - n);
    loop invariant COMPARE: \forall integer i; 0 <= i < (\at(n, Pre) - n) ==> ((unsigned char*)s1)[i] == ((unsigned char*)s2)[i];
    loop invariant D_ZERO: d == 0;

    loop assigns n, d, c1, c2;
    loop variant n;
  @*/
  while (/*n--*/ n) {
    d = (int)*c1++ - (int)*c2++;
    if (d)
      break;

    n--; //inserted code
  }

  return d;
}
