#include <stdio.h>

#include<string.h>

#pragma warning(disable:4996)

void* arrt(const void* str, void* arr, int num) {

	char* arr1 = (char*)arr;

	const char* srt = (const char*)str;

	while (num) {

		*arr1 = *srt;

		arr1++;

		srt++;

		num--;

	}

	return arr;

}

int main()

{

	char str[15] = "abcdefghi";

	int num = strlen(str);

	arrt(str + 1, str, num + 1);

	printf("%s\n", str);

	return 0;

}