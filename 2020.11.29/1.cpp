#include<stdio.h>
#include<string.h>
#include <assert.h>
void search(int a[], int num)
{
	assert(a);
	assert(num);
	int x = 0;
	int y = 0;
	int sum = a[0];
	for (int i = 0; i < num; i++)
	{
		sum ^= a[i];
	}
	int pos = 1;
	{
		while (sum & 1)
		{
			sum = sum >> 1;
			pos = pos << 1;
		}
	}
	for (int i = 0; i < num; i++)
	{
		if (a[i] & pos)
		{
			x ^= a[i];
		}
		else
		{
			y ^= a[i];
		}
	}
	printf("%d %d", x, y);
}
int main()

{

	int a[] = { 1, 2, 3, 7, 4, 5, 1, 2, 3, 7 };
	int num = sizeof(a) / sizeof(a[0]);
	search(a, num);
	return 0;

}