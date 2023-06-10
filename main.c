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
    double interestrate;
    Date withdrawalDate;
    double withdrawalValue;
} Investment;


int verifyDate(Date date){
    if(date.day<1 || date.day>30) return 1;
    else if(date.month<1 || date.month>12) return 2;
    else if(date.year<1900 || date.year>2023) return 3;
    else return 0;

};

int verifyTelephone(Telephone ph){
  if(ph.DDD<11 || ph.DDD>92) return 1;
  else if(ph.number>=10000000 && ph.number<=99999999) return 0;
  else if(ph.number>=900000000 && ph.number<=999999999) return 0;
  else return 2;
};

int main(){

    int validDate=0, validTelephone=0;
    Customer Customer;
    char ask = 'x';

    do{
        
        printf("Informe o DDD: ");
        scanf("%d", &Customer.phone.DDD);
        validTelephone = verifyTelephone(Customer.phone);
        while(validTelephone==1){
            printf("(Inválido) Informe o DDD: ");
            scanf("%d", &Customer.phone.DDD);
            validTelephone = verifyTelephone(Customer.phone);
        }
        
        printf("Informe o número: ");
        scanf("%li", &Customer.phone.number);
        validTelephone = verifyTelephone(Customer.phone);
        while(validTelephone==2){
            printf("(Inválido) Informe o número: ");
            scanf("%li", &Customer.phone.number);
            validTelephone = verifyTelephone(Customer.phone);
        }
        
        
        printf("Dia de nascimento: ");
        scanf("%d", &Customer.birth.day);
        validDate = verifyDate(Customer.birth);
        while(validDate==1){
            printf("(1 a 30) - Dia de nascimento: ");
            scanf("%d", &Customer.birth.day);
            validDate = verifyDate(Customer.birth);
        }
        
        printf("Mês de nascimento: ");
        scanf("%d", &Customer.birth.month);
        validDate = verifyDate(Customer.birth);
        while(validDate==2){
            printf("(1 a 12) - Mês de nascimento: ");
            scanf("%d", &Customer.birth.month);
            validDate = verifyDate(Customer.birth);
        }
        
        printf("Ano de nascimento: ");
        scanf("%d", &Customer.birth.year);
        validDate = verifyDate(Customer.birth);
        while(validDate==3){
            printf("(1900 a 2023) - Dia de nascimento: ");
            scanf("%d", &Customer.birth.year);
            validDate = verifyDate(Customer.birth);
        }

        getchar();
        printf("Nome: ");
        fgets(Customer.name, 50, stdin);
        Customer.name[strlen(Customer.name)-1] = '0';
        
        printf("CPF: ");
        fgets(Customer.cpf, 15, stdin);
        Customer.cpf[strlen(Customer.cpf)-1] = '0';
        
        printf("Deseja continuar? (""y"" se sim, ""n"" se não): ");
        scanf("%c", &ask);

    }while(ask!='n');

    return 0;
}