#include <stdio.h>
#include <stdlib.h>
#include "main.h"

typedef struct _Gread{
    uint32_t kor, math, social, science, eng;
}Gread;

typedef struct _Student{
    String name;
    Gread gread;
    uint32_t average;
}Student;

int main(void){
    Student temp;
    Student student[10 + 1];
    student[10].gread.eng = 0;
    student[10].gread.kor = 0;
    student[10].gread.math = 0;
    student[10].gread.science = 0;
    student[10].gread.social = 0;
    puts("이름 국어 수학 사회 과학 영어");
    for(uint32_t i = 0; i < 10; i++){
        student[i].name = malloc(sizeof(char) * 20);
        scanf("%s %d %d %d %d %d", student[i].name, &student[i].gread.kor, &student[i].gread.math, &student[i].gread.social, &student[i].gread.science, &student[i].gread.eng);
        student[i].average = ((student[i].gread.kor + student[i].gread.math + student[i].gread.social + student[i].gread.science + student[i].gread.eng) / 5);
    }
    for(uint32_t j = 0; j < 10; j++){
        for(uint32_t i = 0; i < 10; i ++){
            if(student[i].average < student[i + 1].average){
                temp = student[i];
                student[i] = student[i + 1];
                student[i + 1] = temp;
            }
        }
    }
    for(uint32_t i = 0; i < 10; i++){
        printf("%s %d\n", student[i].name, student[i].average);
    }

    return 0;
}