#include <stdio.h>
#include <limits.h>
 
int flag_h(int x);
int flag_p(int x);
int flag_s(int x);
int flag_e(int x);
int flag_a(int x);
int flag_f(int x);
 
int main(int argc, char *argv[]){
    if (argc != 3){
        printf("некорректное количество аргументов\n");
        return 1;
    }
 
    int x, pos;
    if (sscanf(argv[1], "%d%n", &x, &pos) != 1 || argv[1][pos] != '\0'){
        printf("некорректное число\n");
        return 1;
    }
 
    if (argv[2][0] != '-' && argv[2][0] != '/'){
        printf("флаг должен начинаться с / или -\n");
        return 1;
    }
 
    char flag = argv[2][1];
    switch (flag){
        case 'h':
            flag_h(x);
            break;
            
        case 'p':
            flag_p(x);
            break;
            
        case 's':
            flag_s(x);
            break;
            
        case 'e':
            flag_e(x);
            break;
            
        case 'a':
            flag_a(x);
            break;
            
        case 'f':
            flag_f(x);
            break;
            
        default:
            printf("Ошибка: неизвестный флаг '%c'\n", flag);
            return 1;
    }
    return 0;
} 
 
int flag_h(int x){
    if (x > 100 || x <= 0){
        printf("нет таких чисел\n");
        return 0;
    }
    int count = 0;
    for (int i = 1; i < 101; i++){
        if (i % x == 0){
            printf("%d ", i);
            count++;
        }
    }
    if (count == 0)
        printf("нет таких чисел\n");
    printf("\n");
    return 0;
}
 
int flag_p(int x){
    if (x <= 1){
        printf("не является простым или составным\n");
        return 0;
    }
    for (int i = 2; i * i <= x; i++){
        if (x % i == 0){
            printf("составное\n");
            return 0;
        }
    }
    printf("простое\n");
    return 0;
}
 
int flag_s(int x){
    if (x <= 0){
        printf("число должно быть положительным\n");
        return 1;
    }
    char hex[10]; 
    sprintf(hex, "%x", x);
    for (int i = 0; hex[i] != '\0'; i++){
        printf("%c ", hex[i]);
    }
    printf("\n");
    return 0;
}
 
int flag_e(int x){
    if (x < 0 || x > 10){
        printf("число должно быть от 0 до 10\n");
        return 1;
    }
    for (int i = 1; i < 11; i++){
        long long e = i;
        for (int j = 1; j < x + 1; j ++){
            printf("%lld ", e);
            e *= i;
        }
        printf("\n");
    }
    return 0;
}
 
int flag_a(int x){
    if (x < 0){
        printf("число должно быть положительным");
        return 1;
    }
    long long sum = 0;
    for (int i = 1; i < x + 1; i++){
        sum+=i;
    }
    printf("%lld\n", sum);
    return 0;
}
 
int flag_f(int x){
        if (x < 0){
        printf("число должно быть положительным");
        return 1;
    }
    long long fact = 1;
    for (int i = 1; i < x+1; i++){
        if (fact > LLONG_MAX / i){
            printf("переполнение при вычислении факториала\n");
            return 1;
        }
        fact *= i;
    }
    printf("%lld\n", fact);
    return 0;
}