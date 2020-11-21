#include <stdio.h>
#include<string.h>
void*my_move(const void* str, void* arr,int num) {
	char *arr1=(char*)arr;
	const char* srt = (const char*)str;
	if (arr1 > srt && arr1 < srt + num) {
		arr1 = arr1 + num-1;
		srt = srt + num-1;
		while (num) {
			*arr1 = *srt;
			arr1--;
			srt--;
			num--;
		}
	}
	else {
		while (num) {
			*arr1 = *srt;
			arr1++;
			srt++;
			num--;
		}
	}
	return arr;
}
int main()
{
	char str[15] = "abcdefghi";
	int num = strlen(str);
	my_move(str+4, str+1, num+1);
	printf("%s\n", str);
	return 0;
}