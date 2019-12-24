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
    char str[255];
    printf ("%s", "your string: ");
   /* size_t size;
    scanf("%d", &size);
    str = malloc((size) * sizeof(char));
    //size++;
    for (int i = 0; i < size; i++) {
        char c = 'j';
        scanf("%c", &c);
        str[i] = c;
    }
    str[size] = NULL;*/
    scanf("%s", str);
    int result = 0;
    char out[255] = {0};
    for (int i = 2, j = 0; i < strlen(str); i += 3, j += 4) {
        int first = (str[i - 2] >> 2) << 18; printf("%d\n", first);
        int firstTail = (str[i - 2] & 0b11) << 4;
        int second = (firstTail | (str[i - 1] >> 4)) <<  12;printf("%d\n", second);
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
        printf("%s", out);

    return 0;
}
