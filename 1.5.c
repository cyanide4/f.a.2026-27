#include <stdio.h>
#include <stdlib.h>
#include <math.h>
 
int sum_1a(double x, double eps, double *res);
int sum_1b(double x, double eps, double *res);
int sum_1c(double x, double eps, double *res);
int sum_1d(double x, double eps, double *res);
int sum_2a(double eps, double *res);
int sum_2b(double eps, double *res);
int sum_2c(double eps, double *res);
int sum_2d(double eps, double *res);
 
int main(int argc, char *argv[]){
    if (argc != 3){
        printf("некорректное количество аргументов\n");
        return 1;
    }
    double eps, x;
    if (sscanf(argv[1], "%lf", &eps) != 1){
        printf("введите число\n");
        return 1;
    }
    if (sscanf(argv[2], "%lf", &x) != 1){
        printf("введите число\n");
        return 1;
    }
    if (eps <= 0){
        printf("число должно быть >0\n");
        return 1;
    }
 
    double res_1a, res_1b, res_1c, res_1d;
    if (sum_1a(x, eps, &res_1a) == 0)
        printf("1a) %lf\n", res_1a);
    else
        printf("1a) ошибка вычисления или ряд не сходится\n");
 
    if (sum_1b(x, eps, &res_1b) == 0)
        printf("1b) %lf\n", res_1b);
    else
        printf("1b) ошибка вычисления или ряд не сходится\n");
 
    if (sum_1c(x, eps, &res_1c) == 0)
        printf("1c) %lf\n", res_1c);
    else
        printf("1c) ошибка вычисления или ряд не сходится\n");
 
    if (sum_1d(x, eps, &res_1d) == 0)
        printf("1d) %lf\n", res_1d);
    else
        printf("1d) ошибка вычисления или ряд не сходиться\n");
 
    double res_2a, res_2b, res_2c, res_2d;
    if (sum_2a(eps, &res_2a) == 0)
        printf("2a) %lf\n", res_2a);
    else
        printf("2a) ошибка вычисления\n");
 
    if (sum_2b(eps, &res_2b) == 0)
        printf("2b) %lf\n", res_2b);
    else
        printf("2b) ошибка вычисления\n");
 
    if (sum_2c(eps, &res_2c) == 0)
        printf("2c) %lf\n", res_2c);
    else
        printf("2c) ошибка вычисления\n");
 
    if (sum_2d(eps, &res_2d) == 0)
        printf("2d) %lf\n", res_2d);
    else
        printf("2d) ошибка вычисления\n");
    return 0;
}
 
int sum_1a(double x, double eps, double *res){ //x^n/n!
    if (res == NULL)
        return 1;
    double sum = 1.0;
    double term = 1.0;
    int n = 1;
 
    while (fabs(term) > eps){
        term = term * x / n;
        sum += term;
        n++;
    }
    *res = sum;
    return 0;
}
 
int sum_1b(double x, double eps, double *res){ //(-1)^n*x^(2n) / (2n)!
    if (res == NULL)
        return 1;
    double sum = 1.0;
    double term = 1.0;
    int n = 1;
 
    while (fabs(term) > eps){
        term = term * (-1.0) * x * x / ((2 * n - 1) * (2 * n));
        sum += term;
        n++;
    }
    *res = sum;
    return 0;
}
 
int sum_1c(double x, double eps, double *res){ //3^(3n) * (n!)^3 * x^(2n) / (3n)!   брать числа <1
    if (res == NULL)
        return 1;
    double sum = 1.0;
    double term = 1.0;
    int n = 1;
    int max_iter = 10000;
 
    while (fabs(term) > eps && n < max_iter){
        double factor = 27.0 * (double)n * (double)n * (double)n * x * x / ((3 * n - 2) * (3 * n - 1) * (3 * n));
        term = term * factor;
        sum += term;
        n++;
    }
    if (n >= max_iter) return 1;
    *res = sum;
    return 0;
}
 
int sum_1d(double x, double eps, double *res){ //(-1)^n * (2n-1)!! * x^(2n) / (2n)!!   тут тоже <1
    if (res == NULL)
        return 1;
    double term = -x*x / 2.0;
    double sum = term;
    int n = 1;
    int max_iter = 10000;
 
    while (fabs(term) > eps && n < max_iter){
        term = term * (-1.0) * (2 * n + 1) * x * x / (2 * n + 2);
        sum += term;
        n++;
    }
    if (n >= max_iter) return 1;
    *res = sum;
    return 0;
}
 
int sum_2a(double eps, double *res){ //ln(1+x)/x dx
    if (res == NULL)
        return 1;
    double sum = 0.0;
    double term = 1.0;
    int n = 0;
    int max_iter = 10000;
 
    while (fabs(term) > eps && n < max_iter){
        term = 1.0 / ((n + 1) * (n + 1));
        if (n % 2 == 1)
            term = -term;
        sum += term;
        n++;
    }
    if (n >= max_iter) return 1;
    *res = sum;
    return 0;
}
 
int sum_2b(double eps, double *res){ //e^(-x²/2) dx
    if (res == NULL)
        return 1;
    double sum = 0.0;
    double term = 1.0;
    int n = 0;
    int max_iter = 10000;
 
    while (fabs(term) > eps && n < max_iter){
        if (n == 0)
            term = 1.0;
        else
            term = term * (-1.0) / (2.0 * n * (2.0 * n + 1.0));
        sum += term;
        n++;
    }
    if (n >= max_iter) return 1;
    *res = sum;
    return 0;
}
 
int sum_2c(double eps, double *res){ //ln(1/(1-x)) dx
    if (res == NULL)
        return 1;
    double sum = 0.0;
    double term = 1.0;
    int n = 1;
    int max_iter = 10000;
 
    while (fabs(term) > eps && n < max_iter){
        term = 1.0 / (n * (n + 1));
        sum += term;
        n++;
    }
    if (n >= max_iter) return 1;
    *res = sum;
    return 0;
}
 
int sum_2d(double eps, double *res){ //x^x dx
    if (res == NULL)
        return 1;
    double sum = 0.0;
    double term = 1.0;
    int n = 0;
    int max_iter = 10000;
 
    while (fabs(term) > eps && n < max_iter){
        if (n == 0)
            term = 1.0;
        else {
            double denom = pow(n + 1, n + 1);
            if (n % 2 == 1)
                term = -1.0 / denom;
            else
                term = 1.0 / denom;
        }
        sum += term;
        n++;
    }
    if (n >= max_iter) return 1;
    *res = sum;
    return 0;
}