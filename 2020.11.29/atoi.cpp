#include<stdio.h>
#include<assert.h>
#include<stdlib.h>
#include<ctype.h>
#include<limits.h>
enum Ret
{
	VALID,
	INVALID,
};
enum Ret state = INVALID;
int My_atoi(const char* str)
{
	int flag = 1;
	long long ret = 0;
	assert(str);
	if (str == NULL)
	{
		return 0;
	}
	if (*str == '\0')
	{
		return (int)ret;
	}
	while (isspace(*str))
	{
		str++;
	}
	if (*str == '-')
	{
		flag = -1;
	}
	if (*str == '+' || *str == '-')
	{
		str++;
	}
	while (*str)
	{
		if (*str >= '0' && *str <= '9')
		{
			ret = ret * 10 + flag * (*str - '0');
			if (ret > INT_MAX || ret < INT_MIN)
			{
				ret = 0;
				break;
			}
		}
		else
		{
			break;
		}
		str++;
	}
	if (*str == '\0')
	{
		state = VALID;
	}
	return ret;
}
int main()
{
	char arr[20] = { "-54855548" };
	int ret = 0;
	ret = My_atoi(arr);
	printf("%d\n", ret);
	return 0;
}