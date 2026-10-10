#include <stdio.h>
#include <string.h>
 
int flag_d(FILE *f_in, FILE *f_out);
int flag_i(FILE *f_in, FILE *f_out);
int flag_s(FILE *f_in, FILE *f_out);
int flag_a(FILE *f_in, FILE *f_out);
 
int main(int argc, char *argv[]){
    if (argc < 3 || argc > 4){
        printf("некорректное количество аргументов\n");
        return 1;
    }
    char *flagg = argv[1];
    if (flagg[0] != '-' && flagg[0] != '/'){
        printf("флаг должен начинаться с '-' или '/'\n");
        return 1;
    }
    char op_flag;
    if (flagg[1] == 'n'){
        if (argc != 4){
            printf("некорректное количество аргументов\n");
            return 1;
        }
        if (flagg[2] == '\0' || flagg[3] != '\0'){
            printf("некорректный формат флага\n");
            return 1;
        }
        op_flag = flagg[2];
    } else {
        if (argc != 3){
            printf("некорректное количество аргументов или флаг\n");
            return 1;
        }
        if (flagg[1] == '\0' || flagg[2] != '\0'){
            printf("некорректный формат флага\n");
            return 1;
        }
        op_flag = flagg[1];
    }
    if (op_flag != 'd' && op_flag != 'i' && op_flag != 's' && op_flag != 'a'){
        printf("неизвестный флаг операции\n");
        return 1;
    }
    char *path = argv[2];
    if (path[0] == '\0'){
        printf("путь к входному файлу не может быть пустым\n");
        return 1;
    }
    char out_path[256];
    if (flagg[1] == 'n'){
        if (argv[3][0] == '\0'){
            printf("путь к выходному файлу не может быть пустым\n");
            return 1;
        }
        strcpy(out_path, argv[3]);
    } else {
        strcpy(out_path, "out_");
        strcat(out_path, path);
    }
    if (strcmp(path, out_path) == 0){
        printf("входной и выходной файлы не могут совпадать\n");
        return 1;
    }
    FILE *f_in = fopen(path, "r");
    FILE *f_out = fopen(out_path, "w");
    if (f_in == NULL || f_out == NULL){
        if (f_in != NULL) fclose(f_in);
        if (f_out != NULL) fclose(f_out);
        printf("ошибка открытия файлов\n");
        return 1;
    }
    int status = 0;
    if (op_flag == 'd'){
        status = flag_d(f_in, f_out);
    } else if (op_flag == 'i'){
        status = flag_i(f_in, f_out);
    } else if (op_flag == 's'){
        status = flag_s(f_in, f_out);
    } else if (op_flag == 'a'){
        status = flag_a(f_in, f_out);
    }
    fclose(f_in);
    fclose(f_out);
    return status;
}
 
int flag_d(FILE *f_in, FILE *f_out){
    int c;
    while ((c = getc(f_in)) != EOF){
        if (c < '0' || c > '9'){
            fputc(c, f_out);
        }
    }
    return 0;
}
 
int flag_i(FILE *f_in, FILE *f_out){
    int c;
    int count = 0;
    while ((c = getc(f_in)) != EOF){
        if (c == '\n'){
            fprintf(f_out, "%d\n", count);
            count = 0;
        } else if (('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z')){
            count++;
        }
    }
    fprintf(f_out, "%d\n", count);
    return 0;
}
 
int flag_s(FILE *f_in, FILE *f_out){
    int c;
    int count = 0;
    while ((c = getc(f_in)) != EOF){
        if (c == '\n'){
            fprintf(f_out, "%d\n", count);
            count = 0;
        } else if (!(('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z') || ('0' <= c && c <= '9') || (c == ' '))){
            count++;
        }
    }
    fprintf(f_out, "%d\n", count);
    return 0;
}
 
int flag_a(FILE *f_in, FILE *f_out){
    int c;
    while ((c = getc(f_in)) != EOF){
        if (c >= '0' && c <= '9'){
            fputc(c, f_out);
        } else {
            fprintf(f_out, "%X", c);
        }
    }
    return 0;
}