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
  	if (n < 3)
  	{
		return n*t;
  	}

	if (n == 3)
	{
		return t*2 + bar(2 + t);
	}

  	int tmp = n / 2;
  	int r = t * tmp;
  	r += (1 + tmp) * (tmp - 2) / 2;

	if (t < 2 - tmp)
	{
		tmp = 2 - t;
	}

	if (tmp < n)
	{
		unsigned long long a = tmp + t + n - 1 + t;
		int b = n - tmp;
		r += a * b / 2;
	}

  	return r;
}

int bar(int x)
{
  	return x > 1 ? x : 0;
}
