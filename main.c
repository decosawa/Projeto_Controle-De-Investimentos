/*
    Projeto Controle de Investimentos

    Autores:

    André Luiz Gonçalves da Silva Teixeira
    Arthur Henrique Caron
    João Pedro Trevisan Borghi
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Date{
    int day;
    int month;
    int year;
} Date;

typedef struct Telephone{
    int DDD;
    long int number;
} Telephone;

typedef struct Customer{
    char name[50];
    char cpf[15];
    Telephone phone;
    Date birth;
} Customer;

typedef struct Investment{
    int applicationType;
    Date applicationDate;
    double applicationValue;
    double tax;
    Date withdrawalDate;
    double withdrawalValue;
} Investment;

int main(){

    return 0;
}