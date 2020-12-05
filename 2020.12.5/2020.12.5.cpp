#include <stdio.h> 
#include <stdlib.h>
#include<string.h>
int comp( void* p1,  void* p2)
{
	int* _p1 = (int*)p1;
	int* _p2 = (int*)p2;
	if (*_p1 > *_p2) {
		return -1;
	}
	if (*_p1 < *_p2) {
		return 1;
	}
	else {
		return 0;
	}
}

void swap1(void* p1, void* p2, int size)
{
	char* p11 = (char*)p1;
	char* p22 = (char*)p2;

	int i = 0;
	while(size){
		char tmp = *p11;
			*p11 = *p22;
			*p22 = tmp;
			size--;
			p11++;
			p22++;
	}
}

void my_qsort(const void* base, int count, int size, int(*cmp)(void*,  void*))
{
	int i = 0;
	int j = 0;
	char* e = (char*)base;
	for (i = 0; i < count - 1; i++){
		int flag = 0;
		for (j = 0; j < count - i - 1; j++)
		{
			if (comp(e + j * size, e + (j + 1) * size) > 0)
			{
				flag= 1;
				swap1(e + j * size, e + (j + 1) * size, size);
			}
		}
		if (flag == 0) {
			break;
		}
	}
}
int main()
{
	int arr[] = { 0,5,8,4,9,10,25,48};
	int i = 0;
	my_qsort(arr, sizeof(arr) / sizeof(arr[0]), sizeof(int), comp);
	for (i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		printf("%d ", arr[i]);
	}
	printf("\n");
	return 0;
}