#include <stdio.h>
#include <math.h>
 
double e_lim(double epsilon);
double e_row(double epsilon);
double e_eq(double epsilon);
double pi_lim(double epsilon);
double pi_row(double epsilon);
double pi_eq(double epsilon);
double ln2_lim(double epsilon);
double ln2_row(double epsilon);
double ln2_eq(double epsilon);
double sqrt2_lim(double epsilon);
double sqrt2_row(double epsilon);
double sqrt2_eq(double epsilon);
double gamma_lim(double epsilon);
double gamma_row(double epsilon);
double gamma_eq(double epsilon);
 
int is_prime(int n) {
    if (n < 2) return 0;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) return 0;
    }
    return 1;
}
 
int main(int argc, char *argv[]){
    if (argc != 2){
        printf("некорректное число флагов\n");
        return 1;
    }
    double epsilon;
    sscanf(argv[1], "%lf", &epsilon);
    if (epsilon < 0.0 || epsilon >= 1.0) {
        printf("эпсилон должен быть положительным и < 1\n");
        return 1;
    }
    printf("e\n");
    printf("%.15f\n", e_lim(epsilon));
    printf("%.15f\n", e_row(epsilon));
    printf("%.15f\n", e_eq(epsilon));
    printf("\npi\n");
    printf("%.15f\n", pi_lim(epsilon));
    printf("%.15f\n", pi_row(epsilon));
    printf("%.15f\n", pi_eq(epsilon));
    printf("\nln2\n");
    printf("%.15f\n", ln2_lim(epsilon));
    printf("%.15f\n", ln2_row(epsilon));
    printf("%.15f\n", ln2_eq(epsilon));
    printf("\nкорень из 2\n");
    printf("%.15f\n", sqrt2_lim(epsilon));
    printf("%.15f\n", sqrt2_row(epsilon));
    printf("%.15f\n", sqrt2_eq(epsilon));
    printf("\ngamma\n");
    printf("%.15f\n", gamma_lim(epsilon));
    printf("%.15f\n", gamma_row(epsilon));
    printf("%.15f\n", gamma_eq(epsilon));
 
    return 0;
}
 
double e_lim(double epsilon) {
    double prev = 0.0;
    double curr = 1.0;
    long n = 1; 
    while (fabs(curr - prev) >= epsilon) {
        prev = curr;
        curr = pow(1.0 + 1.0/n, n);
        n *= 2; 
    }
    return curr;
}
 
double e_row(double epsilon) {
    double sum = 1.0; 
    double curr = 1.0;
    long n = 1;
    while (curr >= epsilon) {
        curr = curr / n; //факториал
        sum += curr;
        n++;
    }
    return sum;
}
 
double e_eq(double epsilon){
    double x = 2.0;
    double prev = 0.0;
    while (fabs(prev - x) >= epsilon){
        prev = x;
        x = x * (2.0 - log(x));
    }
    return x;
}
 
double pi_lim(double epsilon){ //рекккурентно
    double cur = 4.0;  //a(1) = 4
    int n = 1;
    double prev = 0.0;
    while (fabs(cur - prev) >= epsilon){
        prev = cur;
        n++;
        cur = cur * (4.0 * n * (n + 1)) / ((2.0 * n + 1.0) * (2.0 * n + 1));
    }
    return cur;
}
 
double pi_row(double epsilon){
    double sum = 0.0;
    int n = 0;
    double sign = 1.0;
    double cur;
    while (1.0 / (2 * n + 1) >= epsilon) {
        cur = sign / (2 * n + 1);
        sum += cur;
        sign = -sign;
        n++;
    }
    return 4.0 * sum;
}
 
double pi_eq(double epsilon){
    double x = 3.0;
    double prev = 0.0;
    while (fabs(x - prev) >= epsilon) {
        prev = x;
        x = x + (cos(x) + 1.0) / sin(x);
    }
    return x;
}
 
double ln2_lim(double epsilon){ //напрямую чз формулу
    double cur = 1.0 * (pow(2, 1.0/1) - 1);
    double prev = 0.0;
    int n = 1;
    while (fabs(cur - prev) >= epsilon){
        prev = cur;
        n++;
        cur = n * (pow(2, 1.0/n) - 1);
    }
    return cur;
}
 
double ln2_row(double epsilon){
    double sum = 0.0;
    int n = 1;
    double sign = 1.0;
    double cur;
    while (1.0 / n >= epsilon) {
        cur = sign / n;
        sum += cur;
        sign = -sign;
        n++;
    }
    return sum;
}
 
double ln2_eq(double epsilon){
    double x = 1.0;
    double prev = 0.0;
    while (fabs(x - prev) >= epsilon) {
        prev = x;
        x = x - 1.0 + 2.0 / exp(x);
    }
    return x;
}
 
double sqrt2_lim(double epsilon){
    double cur = -0.5;
    double prev = 0.0;
    while (fabs(cur - prev) >= epsilon) {
        prev = cur;
        cur = cur - (cur * cur) / 2.0 + 1.0;
    }
    return cur;
}
 
double sqrt2_row(double epsilon){
    double mul = 1.0;
    double prev = 0.0;
    long k = 2;
    while (fabs(mul - prev) >= epsilon) {
        prev = mul;
        mul *= pow(2.0, pow(2.0, -k));
        k++;
    }
    return mul;
}
 
double sqrt2_eq(double epsilon){
    double x = 1.0;
    double prev = 0.0;
    while (fabs(x - prev) >= epsilon) {
        prev = x;
        x = x / 2.0 + 1.0 / x;
    }
    return x;
}
 
double gamma_lim(double epsilon) {
    long double sum = 0.0;
    long double prev_sum = 0.0;
    int m = 1;
    int max_iter = 40;
    while (m <= max_iter) {
        prev_sum = sum;
        sum = 0.0;
        long double C = 1.0;
        long double ln_fact = 0.0;
        long double sign = -1.0;
        
        for (int k = 1; k <= m; k++) {
            C = C * (m - k + 1) / k;
            ln_fact += logl(k);
            sum += C * sign / k * ln_fact;
            sign = -sign;
        }
        if (m >= 2 && fabsl(sum - prev_sum) < epsilon) {
            break;
        }
        
        m++;
    }
    return (double)sum;
}
 
double gamma_row(double epsilon){
    double sum = 0.0;
    int k = 2;
    double term = 1.0;
    while (fabs(term) >= epsilon || k < 10000) {
        int s = (int)sqrt((double)k);
        term = 1.0 / (s * s) - 1.0 / k;
        sum += term;
        k++;
    }
    return -M_PI * M_PI / 6.0 + sum;
}
 
double gamma_eq(double epsilon) {
    long double product = 1.0;
    long double prev = -1.0;
    long double cur = 0.0;
    int t = 2;
    int max_t = 10000000; 
    while (fabsl(cur - prev) >= epsilon && t < max_t) {
        prev = cur;
        if (is_prime(t)) {
            product *= (t - 1.0) / t;
        }
        long double expr = logl(t) * product;
        if (expr > 0) {
            cur = -logl(expr);
        }
        t++;
    }
    return (double)cur;
}