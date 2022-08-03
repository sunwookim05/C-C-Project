#include <stdio.h>
#include <stdlib.h>
#include "main.h"

typedef struct _Student{
    String name;
    uint32_t grade;
}Student;

int main(void){
    Student temp;
    temp.name = calloc(sizeof(char) * 10);
    uint32_t a = 0, b = 0;
    scanf("%d %d", &a, &b);
    Student student[a + 1];
    student[a].name = " ";
    student[a].grade = 0;
    for(uint32_t i = 0; i < a; i++){
        student[i].name = calloc(sizeof(char) * 10);
        scanf("%s %d", student[i].name, &student[i].grade);
    }
    for(uint32_t j = 0; j < a; j++){
        for(uint32_t i = 0; i < a; i++){
            if(student[i].grade < student[i + 1].grade){
                temp = student[i];
                student[i] = student[i + 1];
                student[i + 1] = temp;
            }
        }
    }
    for(uint32_t i = 0; i < b; i++){
        printf("%s\n", student[i].name);
    }

    return 0;
}