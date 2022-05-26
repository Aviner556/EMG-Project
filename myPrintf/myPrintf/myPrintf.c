// myPrintf.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <stdio.h>
#include <stdarg.h>

int revers(int num, int * cnt) 
{
    int temp = num;
    int rev = 0;
    *cnt = 0;
    while (temp % 10 == 0) {
        (*cnt)++;
        temp /= 10;
    }
    temp = num;
    while (temp != 0) {
        rev = rev * 10 + temp % 10;
        temp /= 10;
    }
    return rev;
}

void myPrintf(char *s, const char *format, ...) //the 3 dots is the possible vars that can be added
{    
    va_list argptr;
    va_start(argptr, format);

    int flag = 0;
    int minFlag = 0;
    int cnt = 0;
    while (*format != '\0') {
        if (flag == 1 && *format == 'd') {
            int n = va_arg(argptr, int);
            if (n < 0) {
                n *= -1;
                *s = '-';
                s++;
            }
            n = revers(n, &cnt);
            while (n != 0) {
                *s = (char)(n % 10) + '0';
                s++;
                n /= 10;
            }
            while (cnt != 0) {
                *s = '0';
                cnt--;
                s++;
            }
            format++;
            flag = 0;
        }
        else if (flag == 1 && *format == 's') {
            char* c = va_arg(argptr, char*);
            while (*c != '\0') {
                *s = *c;
                c++;
                s++;
            }
            format++;
            flag = 0;
        }
        if (*format == '%') {
            flag = 1;
        }
        if (flag == 0) {
            *s = *format;
            s++;
        }
        format++;
    }
    *s = '\0';
}

void mySPrintf(char* s, const char* format)
{
    while (*format != '\0') {
        *s = *format;
        format++;
        s++;
    }
    *s = '\0';

}

int main()
{
    char s[1000];
    myPrintf(s, "hello %s%s%d\r\n", "avi"," and Sarit ", -99900);
    printf(s);
}