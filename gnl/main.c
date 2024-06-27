#include "get_next_line.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
void a()
{
	system("leaks a.out");
}
int main()
{
	atexit(a);
    int i;
    char *tmp;
    int idx = 1;
    i = open("test.txt", O_RDONLY);
    while (1)
    {
        tmp = get_next_line(i);
        printf("call No.%d: %s", idx++, tmp);
        if (!tmp)
            break;
    }

    return 0;
}
