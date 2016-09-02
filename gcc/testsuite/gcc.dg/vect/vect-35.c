/* { dg-do run { target powerpc*-*-* } } */
/* { dg-do run { target i?86-*-* x86_64-*-* } } */
/* { dg-options "-O2 -ftree-vectorize -fdump-tree-vect-stats -maltivec" { target powerpc*-*-* } } */
/* { dg-options "-O2 -ftree-vectorize -fdump-tree-vect-stats -msse2" { target i?86-*-* x86_64-*-* } } */

#include <stdarg.h>
#include "tree-vect.h"

typedef char achar __attribute__ ((__aligned__(16)));

#define N 16
achar x[N];
 
int main1 ()
{  
  union {
    achar a[N];
    achar b[N];
  } s;
  int i;

  for (i = 0; i < N; i++)
    {
      s.b[i] = 3*i;
    }

  for (i = 0; i < N; i++)
    {
      s.a[i] = s.b[i] + 1;
    }

  /* check results:  */
  for (i = 0; i < N; i++)
    {
      if (s.a[i] != s.b[i])
	abort ();
    }

  return 0;
}

int main (void)
{ 
  check_vect ();
  
  return main1 ();
} 


/* { dg-final { scan-tree-dump-times "vectorized 0 loops" 1 "vect" } } */
