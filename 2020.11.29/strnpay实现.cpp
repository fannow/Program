#include<stdio.h>
#include<assert.h>
#include<stdlib.h>
char* my_strncat(char* destination, const char* source, size_t n)
{
	assert((destination != NULL) && (source != NULL));
	char* dest = destination;
	const char* src = source;
	while (n) {
		*dest = *src;
		dest++;
		src++;
		--n;
	}
	return dest;
}


int main()
{
	char arr[20] = { "hellow" };
	const char* str = "wor";
	my_strncat(arr, str, 4);
	printf("%s\n", arr);
	return 0;
}