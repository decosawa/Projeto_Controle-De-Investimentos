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

int verifyDate(Date date){
    if(date.day>30) return 1;
    else if(date.month>12) return 2;
    else if(date.year<1900 && date.year>2003) return 3;
    else return 0;
    
};

int main(){

    int validDate=0;
    Customer Customer;
    char ask = 'x';

    do{
        scanf("%d %li", &Customer.phone.DDD, &Customer.phone.number);
        scanf("%d %d %d", &Customer.birth.day, &Customer.birth.month, &Customer.birth.year);
        fgets(Customer.name, 50, stdin);
        fgets(Customer.cpf, 15, stdin);
        validDate = verifyDate(Customer.birth);
        if(validDate!=0){
            do{
                printf("Data incorreta!");
                scanf("%d %d %d", &Customer.birth.day, &Customer.birth.month, &Customer.birth.year);
            }while(validDate==0);
            break;
        }
        scanf("%c ", &ask);
    }while(ask=='n');
    
    return 0;
}