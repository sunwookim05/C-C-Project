#include <stdio.h>
#include <stdlib.h>
#include "main.h"

typedef struct _Grade{
    uint32_t first, second, third;
}Grade;

typedef struct _Student{
    String name;
    Grade grade;
}Student;

int main(void){
    Student temp;
    String name;
    uint32_t grade2, grade3;
    uint32_t a;
    scanf("%d", &a);
    Student student[a + 1];
    student[a].grade.first = 0;
    student[a].grade.second = 0;
    student[a].grade.third = 0;
    for(uint32_t i = 0; i < a; i++){
        student[i].name = malloc(sizeof(char) * 10);
        scanf("%s %d %d %d", student[i].name, &student[i].grade.first, &student[i].grade.second, &student[i].grade.third);
    }
    for(uint32_t j = 0; j < a; j++){
        for(uint32_t i = 0; i < a; i++){
            if(student[i].grade.first < student[i + 1].grade.first){
                temp = student[i];
                student[i] = student[i + 1];
                student[i + 1] = temp;
            }
        }
    }
    name = student[0].name;
    for(uint32_t j = 0; j < a; j++){
        for(uint32_t i = 0; i < a; i++){
            if(student[i].grade.second < student[i + 1].grade.second){
                temp = student[i];
                student[i] = student[i + 1];
                student[i + 1] = temp;
            }
        }
    }
    for(uint32_t i = 0; i < a; i++){
        if(student[i].name == name){
            grade2 = i + 1;
            break;
        }
    }
    for(uint32_t j = 0; j < a; j++){
        for(uint32_t i = 0; i < a; i++){
            if(student[i].grade.first < student[i + 1].grade.first){
                temp = student[i];
                student[i] = student[i + 1];
                student[i + 1] = temp;
            }
        }
    }
    for(uint32_t j = 0; j < a; j++){
        for(uint32_t i = 0; i < a; i++){
            if(student[i].grade.third < student[i + 1].grade.third){
                temp = student[i];
                student[i] = student[i + 1];
                student[i + 1] = temp;
            }
        }
    }
    for(uint32_t i = 0; i < a; i++){
        if(student[i].name == name){
            grade3 = i + 1;
            break;
        }
    }
    printf("%s %d %d", name, grade2, grade3);

    return 0;
}
