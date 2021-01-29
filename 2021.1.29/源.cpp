#include<stdio.h>
#include<assert.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
// 插入排序
void InsertSort(int* a, int n) {
	assert(a);
	for (int i = 0; i < n-1; i++) {
		int end = i;
		int temp = a[end + 1];
		while (end >= 0) {
			if (temp < a[end]) {
				a[end + 1] = a[end];
				end--;
			}
			else {
				break;
			}
		}
		a[end + 1] = temp;
	}
}
// 希尔排序
void shellsort(int* a, int n) {
	int gap=n;
	while (gap > 1) {
		gap = gap / 3+1;
		for (int i = 0; i < n - gap; i++) {
			int end = i;
			int temp = a[end + gap];
			while (end >= 0) {
				if (a[end] > temp) {
					a[end + gap] = a[end];
					end -= gap;
				}
				else { break; }
				a[end + gap] = temp;
			}
		}
	}
}
void swap(int* p1, int* p2) {

	int temo = *p1;
	*p1 = *p2;
	*p2 = temo;
}
// 选择排序
void SelectSort(int* a, int n) {
	assert(a);
	int begin=0, end=n-1;
	
	while (begin < end) {
		int min, max;
		min = max = begin;
		for (int i = begin + 1; i <= end; i++) {
			if (a[min] > a[i]) {
				 min =i;
			}
			if (a[max] < a[i]) {
				  max=i;
			}
		}
		swap(&a[begin], &a[min]);
		if (begin == end) {
			max = min;
		}
		swap(&a[max], &a[end]);
		++begin;
		--end;
	}
}

// 堆排序
void AdjustDwon(int* a, int n, int root)
{
	int parent = root;
	int child = parent * 2 + 1;
	while (child < n)
	{
		if (child + 1 < n && a[child + 1] > a[child])
		{
			++child;
		}

		if (a[child] > a[parent])
		{
			swap(&a[child], &a[parent]);
			parent = child;
			child = parent * 2 + 1;
		}
		else
		{
			break;
		}
	}
}

void HeapSort(int* a, int n)
{
	// 排升序，建大堆还是小堆?
	for (int i = (n - 1 - 1) / 2; i >= 0; --i)
	{
		AdjustDwon(a, n, i);
	}

	int end = n - 1;
	while (end > 0)
	{
		swap(&a[0], &a[end]);
		AdjustDwon(a, end, 0);
		--end;
	}
}

// O(N^2)
void BubbleSort(int* a, int n)
{
	int end = n;
	while (end > 0)
	{
		int exchange = 0;
		for (int i = 1; i < end; ++i)
		{
			if (a[i - 1] > a[i])
			{
				swap(&a[i - 1], &a[i]);
				exchange = 1;
			}
		}

		if (exchange == 0)
		{
			break;
		}

		--end;
	}
}
// 快速排序递归实现
// 快速排序hoare版本
int GetMidIndex(int* a, int begin, int end) {
	int mid = (begin + end) / 2;
	if (a[begin] < a[mid]){
		if (a[mid] < a[end])
			return mid;
		else if (a[begin] > a[end])
			return begin;
		else
			return end;
}

	else {
		if (a[mid] > a[end])
			return mid;
		else if (a[begin] < a[end])
			return begin;
		else
			return end;
	}
}
int PartSort1(int* a, int left, int right) {
	int mid=GetMidIndex(a, left, right);
	swap(&a[mid], &a[right]);
	int key = right;
	while (left <right) {
		while(left <right&&a[left] <=a[key]) {
			++left;
		}
		while (left <right&&a[right] >=a[key]) {
		
			--right;
		}
		swap(&a[left], &a[right]);	
	}
	swap(&a[left], &a[key]);
	return left;
}
// 快速排序挖坑法
int PartSort2(int* a, int left, int right) {
	int mid = GetMidIndex(a, left, right);
	swap(&a[mid], &a[right]);
	int key = a[right];
	while (left < right) {
	
		while (left < right && a[left] <= key) {
			++left;
		
		}
		a[right] = a[left];
		while (left < right && a[right] >= key) {
			--right;
		}
		a[left] = a[right];
	}
	a[left] = key;
	return left;
}
// 快速排序前后指针法
int PartSort3(int* a, int left, int right) {\
	int mid = GetMidIndex(a, left, right);
	swap(&a[mid], &a[right]);
	int key = right;
	int cur = left;
	int prev = left - 1;
	while (cur < right) {
	
		if (a[cur]<a[key]&&++prev !=cur) {
			
			swap(&a[prev], &a[cur]);
		}
		++cur;
	}
	swap(&a[++prev], &a[cur]);
	return prev;
	
}
void QuickSort(int* a, int left, int right) {
	assert(a);
	if (left > right) {
		return;
	}
	int div = PartSort3(a, left, right);
	QuickSort(a, left, div-1);
	QuickSort(a, div + 1, right);


}
// 快速排序 非递归实现
void QuickSortNonR(int* a, int left, int right);
//// 归并排序递归实现
void MergeSort(int* a, int n);
void ShellSort(int* a, int n);
void _MergeSort(int* a, int left, int right, int* tmp) {
	if (left >= right)
		return;
	int mid = (left + right) / 2;
		_MergeSort(a, left, mid, tmp);
	_MergeSort(a, mid + 1, right, tmp);
	//归并[left, mid] [mid+1, right]有序，
	int begin1 = left, end1 = mid;
	int begin2 = mid + 1, end2 = right;
	int index = begin1;
	while (begin1 <= end1 && begin2 <= end2)
		if (a[begin1] < a[begin2])
			tmp[index++] = a[begin1++];
		else
			tmp[index++] = a[begin2++];
	while (begin1 <= end1)
		tmp[index++] = a[begin1++];
	while (begin2 <= end2)
		tmp[index++] = a[begin2++];
	for (int i = left; i <= right; ++i)
		a[i] = tmp[i];
}
void MergeSort(int* a,int n){
		assert(a);
	int* tmp =(int*) malloc(sizeof(int) * n);
	_MergeSort(a,0,n - 1,tmp);
	free(tmp);
}
//// 归并排序非递归实现
//void MergeSortNonR(int* a, int n)
//// 计数排序
//void CountSort(int* a, int n)
/*void _Mfile(const char *file1,const char *file2,const char*mfile){
	FILE *fout1 = fopen(file1，"r");
	if (fout1 == NULL)
{
	printf("打开文件朱败\n");
	exit(-1);
}
	FILE*fout2 = fopen(file2，"r");
	if (fout2 == NULL)
{
	printf("打开文件失败\n"); exit(-1);
}
	FILE*fin = fopen(mfile, "w");
if (fin == NULL) {
	printf("打开文件失败\n");
	exit(-1);
}
int num1，num2;
int ret1 = fscanf(fout1，"%d\n"， &num1);
int ret2 = fscanf(fout2，"%d\n", &num2); 
while (ret1 != EOF && ret2 != EOF)
{
	if (num1 < num2) {
		fprintf(fin，"%d\n", num1);
		ret1 = fscanf(fout1，"%d\n"， &num1);
	}
	else {
		fprintf(fin，"%d\n", num2);
		ret2 = fscanf(fout2，"%d\n"， &num2);
}
}
while (ret1 != EOF) {
	fprintf(fin, "%d\n"，num1);
	ret1 = fscanf(fout1，"%d\n"， &num1);
}
while (ret2 != EOF)
{
	fprintf(fin，"%d \n", num2);
	ret2 = fscanf(fout2，"%d\n"， &num2);
}
	fclose(fout1); 
	fclose(fout2); 
	fclose(fin);
}
void MergeSortFile(const char* file) {
	FILE* fout = fopen(file, "r");
	if (fout == NULL) {
		printf("打开文件失败\n");
		exit(-1);
	}
	// 分割成一段一段数据，内存排序后写到，小文件，
	int n = 10;
	int a[10];
	int i = 0;
	int num = 0;
	char subfile[20];
	int filei = 1;
	memset(a, 0, sizeof(int) * n);
	while (fscanf(fout, "%d\n", &num) != EOF)
		if (i < n - 1)
			a[i++] = num;
		else {
			a[i] = num;
			QuickSort(a, 0, n - 1);
			sprintf(subfile, "%d", filei++);
		}

	FILE* fin = fopen(subfile, "w");

	if (fin = NULL) {
		printf("打开文件失败\n");
		exit(-1);
	}
	for (int i = 0; i < n; i++)
		fprintf(fin, "%d\n", a[i]);
	fclose(fin);
	i = 0;
	memset(a, 0, sizeof(int) * n);
	//利用互相归并到文件，实现整体有序
	char mfile[100];
	char file1[100];
	char file2[100];
	for (int i = 2; i <= n; ++i) {
		//读取file1和file2, 进行归并出mfile
		_Mfile(file1, file2, mfile);
		strcpy(file1, mfile);
		sprintf(file2, "%d", i + 1);
		sprintf(mfile, "%s%d", mfile, i + 1);
	}

	fclose(fout);
}

void CountSort(int* a, int n) {
	assert(a);
	int min = a[0];
	int max = a[0];
	for (int i = 0; i < n; i++) {
		if (a[i] > max)
			max = a[i];
		if (a[i] < min)
			min = a[i];
	}
	int range=max-min + 1;
	int* countArr = (int*)malloc(sizeof(int) * range);
	memset(countArr,0, sizeof(int) * range);
	for (int i = 0; i < n; ++i) {
		countArr[a[i] - min]++;
	}
	//排序
	int index = 0;
	for (int j = 0; j < range; ++j)
		while (countArr[j]--)
			a[index++] = j + min;
	free(countArr);
}*/
void printfarry(int* a, int n) {
	for (int i = 0; i < n; i++) {
		printf("%d ", a[i]);
	}
	printf("\n");

}
void treeInsertSort() {
	int a[] = { 1,3,4,5,4,8,4,5,9,7,8,9};
	printfarry(a, sizeof(a) / sizeof(int));
	MergeSort(a,sizeof(a) / sizeof(int));
	printfarry(a, sizeof(a) / sizeof(int));
	

}
int main() {
	treeInsertSort();
	return 0;
}