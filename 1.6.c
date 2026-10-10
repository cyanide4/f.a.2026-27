#include <stdio.h>
#include <stdarg.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>
 
bool first(int n, ...){
    if (n < 3) return false;
    va_list coor;
    va_start(coor, n);
    int sign = 1;
    double cross, x1, y1, x2, y2, x3, y3;
    double xx1, yy1, xx2, yy2;
    for (int i = 0; i < n; i++){
        if (i == 0){
            x1 = va_arg(coor, double);
            y1 = va_arg(coor, double);
            x2 = va_arg(coor, double);
            y2 = va_arg(coor, double);
            x3 = va_arg(coor, double);
            y3 = va_arg(coor, double);
            xx1 = x1;
            yy1 = y1;
            xx2 = x2;
            yy2 = y2;
            cross = (x2-x1)*(y3-y1) - (y2-y1)*(x3-x1);
            if (cross < 0) sign = -1;
        }else if (i < n - 2){
            x1 = x2;
            y1 = y2;
            x2 = x3;
            y2 = y3;
            x3 = va_arg(coor, double);
            y3 = va_arg(coor, double);
            cross = (x2-x1)*(y3-y1) - (y2-y1)*(x3-x1);
            if ((cross > 0 && sign < 0) || (cross < 0 && sign > 0)) return false;
        }else if(i == n - 2){
            x1 = x2;
            y1 = y2;
            x2 = x3;
            y2 = y3;
            x3 = xx1;
            y3 = yy1;
            cross = (x2-x1)*(y3-y1) - (y2-y1)*(x3-x1);
            if ((cross > 0 && sign < 0) || (cross < 0 && sign > 0)) return false;
        } else if (i == n - 1){
            x1 = x2;
            y1 = y2;
            x2 = x3;
            y2 = y3;
            x3 = xx2;
            y3 = yy2;
            cross = (x2-x1)*(y3-y1) - (y2-y1)*(x3-x1);
            if ((cross > 0 && sign < 0) || (cross < 0 && sign > 0)) return false;
        }
    }
    va_end(coor);
    return true;
}
 
double second(double x, int n, ...){
    if (n < 0 || n > 10) return NAN;
    double sum = 0;
    va_list coef;
    va_start(coef, n);
    for (int i = n; i >= 0; i--){
        sum += va_arg(coef, double) * pow(x, i);
    }
    return sum;
}
 
int is_kaprekar(unsigned long long n, int base) {
    if (n == 0) return 0;
    int d = 0;
    unsigned long long bd = 1;
    unsigned long long temp = n;
    while (temp > 0) {
        d++;
        bd *= base;
        temp /= base;
    }
    unsigned long long n_sq = n * n;
    unsigned long long B = n_sq % bd;
    unsigned long long A = n_sq / bd;
    return (A + B == n);
}
 
void third(int base, ...) {
    va_list args;
    va_start(args, base);   
    char *str;
    while ((str = va_arg(args, char *)) != NULL) {
        char *endptr;
        unsigned long long n = strtoull(str, &endptr, base);       
        if (*endptr == '\0' && endptr != str && is_kaprekar(n, base)) {
            printf("%s сс %d\n", str, base);
        }
    }
    va_end(args);
}
 
double fourth(int n, ...){
    double mult = 1.0;
    va_list list;
    va_start(list, n);
    for (int i = 0; i < n; i++){
        mult *= va_arg(list, double);
    }
    va_end(list);
    if (mult < 0){
        printf("число должно быть >0\n");
        return NAN;
    }
    return pow(mult, 1.0/n);
}
 
double fifth(double x, int power){
    if (power == 0) return 1.0;
    if (power < 0) return 1.0/fifth(x, -power);
    double xx = fifth(x, power/2);
    if (power % 2 == 0) return xx * xx;
    if (power % 2 != 0) return xx * xx * x; 
}
 
double sixth(double (*f)(double), double a, double b, double eps){
    if (f(a) * f(b) >= 0) {
        printf("f(a) и f(b) должны иметь разные знаки\n");
        return NAN;
    }
    double c;
    while (b - a > eps) {
        c = (a + b) / 2.0;
        if (f(a) * f(c) < 0) {
            b = c;
        } else {
            a = c;
        }
    }
    return (a + b) / 2.0;
}
 
double f1(double x){
    return x * x - 2;
}
double f2(double x){
    return x * x * x - x - 3;
} 
 
int main(){
    printf("1) %d\n", first(5, 0.0, 0.0, 5.0, 0.0, 5.0, 4.0, 2.0, 4.0, 2.0, 1.0));
    printf("1) %d\n", first(4, 1.0, 1.0, 5.0, 0.0, 6.0, 4.0, 2.0, 5.0));
    printf("2) %lf\n", second(6.0, 3, 1.0, 0.0, -4.0, 9.0));
    printf("3) ");
    third(10, "1", "9", "45", "55", "99", "297", "703", "999", NULL);
    printf("3) ");
    third(16, "1", "F", "45", "AB", "FF", NULL);
    printf("4) %lf\n", fourth(3, 2.0, 4.0, 8.0));
    printf("4) %lf\n", fourth(5, 5.8, 4.0, 3.9, 168.25, 61.8));
    printf("5) %lf\n", fifth(1.5, 4));
    printf("5) %lf\n", fifth(2.0, -3));
    printf("6) %lf\n", sixth(f1, 1.0, 2.0, 1e-6));
    printf("6) %lf\n", sixth(f2, 1.0, 2.0, 1e-6));
    return 0;
}
 