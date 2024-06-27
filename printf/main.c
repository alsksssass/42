#include "ft_printf.h"
#include <stdio.h>
int main()
{
	printf("%d",ft_printf("%z      s\n","hello"));
//	printf("%d",printf("%s %z \n","hello"));
	return 0;
}
