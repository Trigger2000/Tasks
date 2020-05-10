#include <stdio.h>

int bar(int);
int foo(int, int);

#define N 50000

int main()
{
  int i;
  int r = 0;
  for (i = 0; i < N; i++)
    r += foo(100000, -i);
  printf("%d\n",r);
  return 0;
}

int foo(int n, int t)
{
  int i;
  int r = 0;
  for (i = 0; i < n; i++)
  {
    if(i < 2)
    {
      r += t;
    }
    else if (i < n/2)
    {
      r += bar(i) + t;
    }
    else
    {
      r += bar(i+t);
    }
  }
  return r;
}

int bar(int x)
{
  return x > 1 ? x : 0;
}
