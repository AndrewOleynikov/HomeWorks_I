#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int normalize(int x)
{
    if ('A' <= x && x <='Z')
	{
		return (x - 65);
	}
	if ('a' <= x && x <= 'z')
	{
		return (x - 71);
	}
    if ('0' <= x && x <= '9')
	{
		return (x + 4);
	}
	if (x == '+')
	{
		return 62;
	}
	if (x == '/')
	{
		return 63;
	}
	if (x == '=')
	{
		return 0;
	}

}

int main()
{
    char str[256] = {0};
    printf("write base64_string: ");
    scanf("%s", &str);
    int strSize = strlen(str);
    //printf("%d %c\n",normalize(str[3]), str[3]);
    char out[256] = {0};
    for (int j = 0, i = 3; i < strSize; i += 4, j += 3)
    {
        int stringBits = normalize(str[i - 3]) << 18 |
                         normalize(str[i - 2]) << 12 |
                         normalize(str[i - 1]) << 6 |
                         normalize(str[i - 0]) << 0;
        //printf("%d", stringBits);
        int mask = 0xff0000;
        int first = (mask & stringBits) >> 16;
        int second = ((mask >> 8) & stringBits) >> 8;
        int third = ((mask >> 16) & stringBits);
        out[j] = (char)first;
        out[j + 1] = (char)second;
        out[j + 2] = (char)third;
    }
    printf("%s", out);
    return 0;
}
///TWFuaQ==
