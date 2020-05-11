#include <stdio.h>
#include <assert.h>

int result_foo(int n, int t);
int original_foo(int n, int t);
int bar(int x);

void test(int first, int second);
void test0();

int main()
{
    test0();
    test(-5, 3);
    test(0, 3);
    test(1, 3);
    test(2, 3);
    test(3, 3);
    test(1, -3);
    test(2, -3);
    test(3, -3);
    test(5, 3);
    test(10, -15);
    test(4, -4);
    test(11, 0);
    test(10000, 5000);
    test(10001, 5001);


    return 0;
}

void test(int first, int second)
{
    int result1 = 0;
    int result2 = 0;

	for (int i = 0; i < 100; i++)
	{
		result1 += original_foo(first, second);
        result2 += result_foo(first, second);
	}
    assert(result1 == result2);
}

void test0()
{
    int result1 = 0;
    int result2 = 0;

	for (int i = 0; i < 100; i++)
	{
		result1 += original_foo(10000, -i);
        result2 += result_foo(10000, -i);
	}
    assert(result1 == result2);
}

int result_foo(int n, int t)
{
	if (n < 0)
	{
		return 0;
	}

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

int original_foo(int n, int t)
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