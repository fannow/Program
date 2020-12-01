#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void move(char ch[], int k)
 {
	for (int i = 0; i < k; i++)
	{
		char temp = ch[0];
		for (int j = 0; j < (strlen(ch) - 1); j++)
		{
			ch[j] = ch[j + 1];
		}
		ch[strlen(ch) - 1] = temp;
	}
}
int compiex(char ch[], char ch1[]) {
	if (strcmp(ch,ch1)) {
		return 0;
	}
	else {
		return 1;
	
	}
}
int main()
{
	char ch[] = "ABCD";
	char ch1[] = "BCDA";
    int k = 0;  
	scanf_s("%d", &k);
	move(ch, k);
	printf("%d", compiex(ch, ch1));
	return 0;
}