#include <stdio.h>
#include <stdlib.h>
#include <math.h>
 
int flag_q(double eps, double a, double b, double c);
int flag_m(int a, int b);
int flag_t(double eps, double a, double b, double c);
 
int main(int argc, char *argv[]){
    if (argc < 2){
        printf("некорректное количество аргументов\n");
        return 1;
    }
    if (argv[1][0] != '-' && argv[1][0] != '/'){
        printf("некорректный ввод\n");
        return 1;
    }
    char flag = argv[1][1];
    
    if (flag == 'q'){
        if (argc != 6){
            printf("неправильное число аргументов\n");
            return 1;
        }
        double eps, a, b, c;
        int pos;
        if (sscanf(argv[2], "%lf%n", &eps, &pos) != 1 || argv[2][pos] != '\0' ||
            sscanf(argv[3], "%lf%n", &a, &pos) != 1 || argv[3][pos] != '\0' ||
            sscanf(argv[4], "%lf%n", &b, &pos) != 1 || argv[4][pos] != '\0' ||
            sscanf(argv[5], "%lf%n", &c, &pos) != 1 || argv[5][pos] != '\0'){
            printf("некорректное число\n");
            return 1;
        }
        if (eps <= 0){
            printf("число должно быть > 0\n");
            return 1;
        }
        if (flag_q(eps, a, b, c) != 0) return 1;
    }
    else if (flag == 'm'){
        if (argc != 4){
            printf("неправильное число аргументов\n");
            return 1;
        }
        int a, b, pos;
        if (sscanf(argv[2], "%d%n", &a, &pos) != 1 || argv[2][pos] != '\0' ||
            sscanf(argv[3], "%d%n", &b, &pos) != 1 || argv[3][pos] != '\0'){
            printf("некорректное число\n");
            return 1;
        }
        flag_m(a, b);
    }
    else if (flag == 't'){
        if (argc != 6){
            printf("неправильное число аргументов\n");
            return 1;
        }
        double eps, a, b, c;
        int pos;
        if (sscanf(argv[2], "%lf%n", &eps, &pos) != 1 || argv[2][pos] != '\0' ||
            sscanf(argv[3], "%lf%n", &a, &pos) != 1 || argv[3][pos] != '\0' ||
            sscanf(argv[4], "%lf%n", &b, &pos) != 1 || argv[4][pos] != '\0' ||
            sscanf(argv[5], "%lf%n", &c, &pos) != 1 || argv[5][pos] != '\0'){
            printf("некорректное число\n");
            return 1;
        }
        if (eps <= 0){
            printf("число должно быть > 0\n");
            return 1;
        }
        flag_t(eps, a, b, c);
    }
    else{
        printf("нет такого флага\n");
    }
    return 0;
}
 
int flag_q(double eps, double a, double b, double c){
    double p[6][3] = {{a,b,c}, {a,c,b}, {b,a,c}, {b,c,a}, {c,a,b}, {c,b,a}};
    for (int i = 0; i < 6; i++){
        int dup = 0;
        for (int j = 0; j < i; j++){
            if (fabs(p[i][0] - p[j][0]) < eps &&
                fabs(p[i][1] - p[j][1]) < eps &&
                fabs(p[i][2] - p[j][2]) < eps){
                dup = 1;
                break;
            }
        }
        if (dup)
            continue;
 
        double aa = p[i][0], bb = p[i][1], cc = p[i][2];
        printf("a=%.2f b=%.2f c=%.2f : ", aa, bb, cc);
 
        if (fabs(aa) < eps){
            if (fabs(bb) < eps)
                printf("не является уравнением\n");
            else
                printf("%lf\n", -cc / bb);
        } else {
            double D = bb * bb - 4 * aa * cc;
            if (D > eps)
                printf("%lf %lf\n", (-bb + sqrt(D)) / (2 * aa), (-bb - sqrt(D)) / (2 * aa));
            else if (fabs(D) < eps)
                printf("%lf\n", -bb / (2 * aa));
            else
                printf("нет корней\n");
        }
    }
    return 0;
}
 
int flag_m(int a, int b){
    if (a == 0 || b == 0){
        printf("введите не 0\n");
        return 1;
    }
    if (a % b == 0){
        printf("%d кратно %d\n", a, b);
    } else {
         printf("%d не кратно %d\n", a, b);
    }
    return 0;
}
 
int flag_t(double eps, double a, double b, double c){
    if (a <= 0 || b <= 0 || c <= 0){
        printf("числа должны быть положительными\n");
        return 1;
    }
    if (fabs(a*a + b*b - c*c) < eps || fabs(a*a + c*c - b*b) < eps || fabs(b*b + c*c - a*a) < eps)
        printf("может быть прямоугольным треугольником\n");
    else
        printf("не может быть прямоугольным треугольником\n");
    return 0;
}
