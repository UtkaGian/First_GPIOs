#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define GPIO "18"

void write_File(const char *path, const char *value);

char read_File(const char *path);

int main(void){
    write_File("/sys/class/gpio/export", GPIO);
    sleep(1);
    write_File("/sys/class/gpio/gpio18/direction", "out");
    write_File("/sys/class/gpio/gpio18/value", "1");
    sleep(1);
    char value = read_File("/sys/class/gpio/gpio18/value");
    printf("El estado del GPIO %s es: %c\n", GPIO, value);
    write_File("/sys/class/gpio/gpio18/value", "0");
    sleep(1);
    value = read_File("/sys/class/gpio/gpio18/value");
    printf("El estado del GPIO %s es: %c\n", GPIO, value);

    write_File("/sys/class/gpio/unexport", GPIO);
    return 0;
}

void write_File(const char *path, const char *value){
    FILE *fp = fopen(path, "w");
    if (fp == NULL) {
        perror("Error al abrir archivo");
        exit(1);
    }
    fprintf(fp, "%s", value);
    fclose(fp);
}

char read_File(const char *path){
    FILE *fp = fopen(path, "r");
    if (fp == NULL) {
        perror("Error al leer archivo");
        exit(1);
    }
    char value;
    fscanf(fp, "%c", &value);
    fclose(fp);
    return value;
}
