#include<stdio.h>
int my_strcmp(const char* arr, const char* str) {
	const char* _arr = arr;
	const char* _str = str;
		while (*_str) {
			if (*_str > *_arr) {
				return 1;
			}
			else if (*_str < *_arr) {
				return -1;
			}
			_arr++;
			_str++;
		}
		return 0;
	}


int main() {
	const char* arr = "afffc";
	const char* str = "afffcdf";
	int num = my_strcmp(arr, str);
	printf("%d", num);
	return 0;
}