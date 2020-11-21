#include<stdio.h>
char *my_strcpy(const char* arr,char* str) {
	 const char* _arr = arr;
	 char* _str = str;
	while (*_str=*_arr) {
		_arr++;
		_str++;
	}
	return _str;
}
int main(){
	 const char* arr = "abcdef";
	 char* str;
	printf("%s",str );
	return 0;
}