#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

int main()
{
    const char map[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q',
                        'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h',
                        'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y',
                        'z', '0','1','2','3','4','5','6','7', '8', '9', '+', '/'};
    char *str;
    size_t strSize;
    printf("%s", "write size of string: ");
    scanf("%ud", &strSize);
    str = malloc(strSize * sizeof(char));
    printf ("%s", "your string: ");
    scanf("%s", str);
    int result = 0;
    char out[256] = {0};
    for (int i = 2, j = 0; i < strSize; i += 3, j += 4)
    {
        int first = (str[i - 2] >> 2) << 18; //printf("%d\n", first);
        int firstTail = (str[i - 2] & 0b11) << 4;
        int second = (firstTail | (str[i - 1] >> 4)) <<  12;//printf("%d\n", second);
        int secondTail = (str[i - 1] & 0b1111) << 2;//
        int third = (secondTail | (str[i] >> 6)) << 6;//printf("%d\n", third);
        int fourth = str[i] & 0b111111; //printf("%d\n", fourth);
        result += first | second | third | fourth;
        int iter = (result & 0xFC0000) >> 18;
        //printf("%d %s",iter," (ITER)");
        out[j] = map[iter];
        iter = (result & (0xFC0000 >> 6)) >> 12;
        out[j + 1] = map[iter];
        iter = (result & (0xFC0000 >> 12)) >> 6;
        out[j + 2] = map[iter];
        iter = (result & (0xFC0000 >> 18));
        out[j + 3] = map[iter];
        result = 0;
    }
    if (strSize % 3 == 1)
    {
        char addStr[4] = {(char)str[strSize - 1]};
        strcat(addStr, "00");
        //printf("%s\n", addStr);
        int lastOut = strlen(out) - 1;
        int first = addStr[0] >> 2;
        out[lastOut + 1] = map[first];
        int firstTail = (addStr[0] & 0b11) << 4;
        out[lastOut + 2] = map[firstTail];
        out[lastOut + 3] = '=';
        out[lastOut + 4] = '=';
    }
    if (strSize % 3 == 2)
    {
        char addStr[4] = {(char)str[strSize - 2], (char)str[strSize - 1]};
        strcat(addStr, "00");
        //printf("%s\n", addStr);
        int lastOut = strlen(out) - 1;
        int first = addStr[0] >> 2;
        out[lastOut + 1] = map[first];
        int firstTail = (addStr[0] & 0b11) << 4;
        int second = addStr[1] >> 4;
        out[lastOut + 2] = map[firstTail | second];
        int secondTail = (addStr[1] & 0b1111) << 2;
        int third = addStr[2] >> 6;
        out[lastOut + 3] = map[secondTail];
        out[lastOut + 4] = '=';
    }
    printf("%s", out);
    return 0;
}
