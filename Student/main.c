#include "main.h"

#pragma pack(push, 1)
typedef struct _Student{
    uint8_t id;
    String name;
    uint8_t age;
}Student;
#pragma pack(pop)

Student* new_Student(uint8_t id, String name, uint8_t age){
    Student* this = malloc(sizeof(Student));
    assert(this);

    this->id = id;
    this->name = name;
    this->age = age;

    return this;
}

void delete_Student(Student* this){
    free(this);
}

int main(void){
    uint32_t i = 0;
    uint8_t id = 0;
    String name = malloc(sizeof(char) * 100);
    uint8_t age = 0;
    System.out.print("How many students do you want to create? : ");
    scanf("%d", &i);

    Student* students = malloc(sizeof(Student) * i);

    for(uint32_t j = 0; j < i; j++){
        System.out.println("Student %d", j + 1);
        System.out.print("ID : ");
        scanf("%d", &id);
        System.out.print("Name : ");
        scanf("%s", name);
        System.out.print("Age : ");
        scanf("%d", &age);
        students[j] = *new_Student(id, name, age);
        System.out.println("");
    }

    for(uint32_t j = 0; j < i; j++){
        System.out.println("Student %d", j);
        System.out.println("ID : %d", students[j].id);
        System.out.println("Name : %s", students[j].name);
        System.out.println("Age : %d", students[j].age);
        System.out.println("");
    }

    for(uint32_t j = 0; j < i; j++){
        delete_Student(&students[j]);
    }


    return 0;
}