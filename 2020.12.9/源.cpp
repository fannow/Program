#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

typedef int SLDateType;
typedef struct SeqList
{
	SLDateType* a;
	size_t size;
	size_t capacity; // unsigned int
}SeqList;

// 初始化
int  SeqListInit(SeqList* ps,int city) {

	
		ps->a = (SLDateType*)malloc(4 * sizeof(SLDateType));
		if (ps->a == NULL) {
		
			printf("申请内存失败！");
		}
		if (!ps->a) exit(city);
		ps->size = 0;
		ps->capacity = 4;
		return 1;

}
//顺序表销毁
void SeqListDestory(SeqList* ps) {
		if (ps->a) {
			free(ps->a);
			ps->a = NULL;
			ps->size = 0;
			ps->capacity = 0;
		}
		else {
			printf("销毁失败！");
		}
		printf("销毁成功！");
}
//打印
void SeqListPrint(SeqList* ps) {
	for (int i = 0; i < ps->size; i++) {
		printf("%d  ", ps->a[i]);
	
	}

}
//线性表增容
void SeqListExpansion(SeqList* ps) {
	if (ps->size == ps->capacity) {
		ps->capacity *= 2;
		ps->a = (SLDateType*)realloc(ps->a, ps->capacity * sizeof(SLDateType));
		if (ps->a == NULL) {
			printf("增容失败！");
			exit(-1);
		}
	}
}

//头插
void SeqListPushFront(SeqList* ps, SLDateType x) {
	SeqListExpansion(ps);
	int end = ps->size;
	while (end) {
		ps->a[end] = ps->a[end - 1];
		end--;
	}
	ps->a[0] = x;
	ps->size++;
}
//头删
void SeqListPopFront(SeqList* ps) {
	int end = ps->size;
	int i = 0;
	while (i<end) {
		 ps->a[i]=ps->a[i+1];
		 i++;
	}
	ps->size--;
}
//尾删
void SeqListPopBack(SeqList* ps) {

	ps->size--;	
}
//
//// 顺序表查找
int SeqListFind(SeqList* ps, SLDateType x) {
	assert(ps);
	int i = 0;
	while (i < ps->size) {
		if (ps->a[i] == x) {
		
			return i;
		}
	
		i++;
	}
	return -1;
}
// 顺序表在pos位置插入x
void SeqListInsert(SeqList* ps, size_t pos, SLDateType x) {
	assert(ps);
	assert(pos <= ps->size&&pos>=0);
	SeqListExpansion(ps);
	int end = ps->size-1;
	while (end >= pos) {
		ps->a[end+1] = ps->a[end];
		--end;
	}
	ps->a[pos] = x;
	ps->size++;
}
//尾插；
void SeqListPushBack(SeqList* ps, SLDateType x) {
	SeqListExpansion(ps);
	ps->a[ps->size] = x;
	ps->size++;
}
// 顺序表删除pos位置的值
void SeqListErase(SeqList* ps, size_t pos) {
	assert(ps);
	assert(pos < ps->size&& pos >= 0);
	SeqListExpansion(ps);
	int end = ps->size - 1;
	while (end > pos) {
		ps->a[pos]=ps->a[pos+1] ;
		pos++;
	}
	ps->size--;

}
void Splist() {
	SeqList s;
	int b=SeqListInit(&s, 0);
	if (b == 1) {
		printf("初始化成功\n");
	
	}
	SeqListPushBack(&s, 1);
	SeqListPushBack(&s, 2);
	SeqListPushBack(&s, 1);
	SeqListPushBack(&s, 2);
	SeqListPushBack(&s, 1);
	SeqListPushBack(&s, 2);
	SeqListPushBack(&s, 1);
	SeqListPushBack(&s, 2);
	SeqListPushBack(&s, 1);
	SeqListPushBack(&s, 2);
	SeqListPushBack(&s, 1);
	SeqListPushBack(&s, 2);
	SeqListPushBack(&s, 1);
	SeqListPushBack(&s, 2);
	SeqListPushBack(&s, 1);
	SeqListPushBack(&s, 2);
	SeqListPushBack(&s, 1);
	SeqListPushBack(&s, 2);
	SeqListPushBack(&s, 1);
	SeqListPushBack(&s, 2);
	SeqListPushBack(&s, 1);
	SeqListPushBack(&s, 7);
	SeqListPushBack(&s, 7);
	SeqListPushBack(&s, 9);
	SeqListPrint(&s);
	SeqListPopBack(&s);
	printf("\n");
	SeqListPrint(&s);
	SeqListPushFront(&s, 0);
	printf("\n");
	SeqListPrint(&s);
	SeqListPushFront(&s, 9);
	printf("\n");
	SeqListPrint(&s);
	SeqListPopFront(&s);
	printf("\n");
	SeqListPrint(&s);
	SeqListInsert(&s, 2, 9);
	printf("\n");
	SeqListPrint(&s);
	SeqListErase(&s, 1);
	printf("\n");
	SeqListPrint(&s);
	printf("\n");
	SeqListDestory(&s);
}
int main(){
	Splist();
	return 0;
}