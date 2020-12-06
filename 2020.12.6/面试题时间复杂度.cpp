#include<stdio.h>

int* singleNumbers(int* nums, int numsSize, int* returnSize) {
		int ret = 0;
		for (int i = 0; i < numsSize; i++) {
			ret ^= nums[i];
		}
		int div = 0;
		while (0 == (ret & 1) && (div < 32))
		{
			ret >>= 1;
			div++;
		}
		int* arr = (int*)malloc(sizeof(int) * 2);
		int a = 0, b = 0;
		for (int i = 0; i < numsSize; i++) {
			if (0 == (((nums[i]) >> div) & 1))
				a ^= nums[i];
			else
				b ^= nums[i];
		}
		arr[0] = b;
		arr[1] = a;
		*returnSize = 2;
		return arr;
	}

int main() {
	int a[10] = { 1,1,2,2,2,4,4,9 };
	int num = sizeof(a) / sizeof(int);
	int b[2];
	singleNumbers(a, num, b);
	for (int i = 0; i < 2; i++) {
		printf("%d\n", b[i]);
	}
}