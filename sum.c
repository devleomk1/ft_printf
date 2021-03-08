#include <stdio.h>
#include <stdarg.h>     //va_list, va_start, va_arg, va_end가 정의된 헤더파일.

//가변인자 사용법을 익혀봅시다.
int sum(int count, ...) //가변 인자의 갯수를 받는다
{
    int res = 0;
    va_list ap;
    int i;

    i = 0;
    va_start(ap, count);
    while (i<count)
    {
        res = res + va_arg(ap, int);
        i++;
    }
    va_end(ap);
    return res;
}
int main(void)
{
    printf("%d\n", sum(5, 1,2,3,4,5,6,7,8,9,10));
    printf("Color %s, Number %d, Float %4.2f\n\n", "red", 123456, 3.14);
    printf("%2$d %2$#x; %1$d %1$#x\n\n", 16, 17);
    printf("[%-5d]\n", 10);       //[10   ]
    printf("[%5d]\n", 10);        //[   10]
    printf("[%0*d]\n", 5, 10);    //[00010]
    printf("% d\n", 10);          // 10
    printf("% d\n", -10);         //-10
    printf("%.2f\n", 3.141592);   //3.14

    return (0);
}
