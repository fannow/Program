#include<stdio.h>
#include<string>
const char* my_strstr(const char* str, const char* srt) {
	while (*str) {
		const char *q = srt;
		const char *p = str;
		while (*p && *q && *q == *p) {
			p++;
			q++;
		}
		if (*q == '\0') {
			return str;
		}
		str++;
	}
	return NULL;
}
int main() {
	const char* str = "abc 1234 abb 12345";
	const char *srt = "1234 ";
	printf("%s",my_strstr(str, srt));
	return 0;
}