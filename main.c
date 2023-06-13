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

#define MAXCUST 100 //Constante para máximo de consumidores.
#define MAXINVEST 30 //Constante para máximo de investimentos.

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
    char cpf[13];
    Telephone phone;
    Date birth;
} Customer;

typedef struct Investment{
    int applicationType;
    char emitter[52];
    float interestRate;
    char isActive;
} Investment;

typedef struct Trade{
    int tradeId;
    Customer customer;
    Investment investment;
    Date applicationDate;
    float applicationValue;
    Date withdrawDate;
    float withdrawValue;
} Trade;

int verifyDate(Date date);
int verifyTelephone(Telephone ph);
int verifyCPF(char cpf[12]);
void showCustumer(Customer sCustomer[], int registred);
int difDate(Date finalDate, Date startDate); //Função que retorna diferença de dias entre duas datas
float calcInvest(Investment cInvest);
Investment registerInvestiment(Investment rInvestiment);
int getch();

int main(){

    int validDate=0, 
        validTelephone=0,
        validCPF=0,
        i = 0, //Número de clientes cadastrados.
        j = 0; //Número de investimentos cadastrados
    Customer Customer[MAXCUST];
    char ask = 'x'; //Verifica se o usuário quer ou não continuar cadastrando clientes. Verifica, também, a opção escolhida no menu.
    Investment Investment[MAXINVEST];

    do{
        printf("\n********Menu********\n");
        printf("1) Cadastrar investimento\n");
        printf("2) Mostrar todos os clientes cadastrados\n");
        printf("3) Apresentar extrato\n");
        printf("4) Cadastrar cliente\n");
        printf("5) Sair\n");

        ask = getch();
        
        printf("********Menu********\n\n");

        switch(ask){
            case '1':
                do{
                    if(j >= 30){
                        printf("Número máximo de investimentos cadastrados já foi atingido.\n\n");

                        break;
                    }

                    Investment[j] = registerInvestiment(Investment[j]);
                    j++; //Incrementa o número de investimentos cadastrados

                    if(j < 30){ //Verifica se o número máximo não foi atingido
                        printf("Deseja continuar cadastrando? (y/n) ");
                        scanf(" %c", &ask);
                        getchar();
                    }

                    while(ask != 'y' && ask != 'n'){
                        printf("Opção inválida. Digite novamente. ");
                        scanf(" %c", &ask);
                    }
                } while(ask != 'n');

                 printf("\n--------------------------------------------------------------\n");

                break;
            case '2':
                showCustumer(Customer, i);

                break;
            case '3':
            case '4':
                do{
                    if(i >= MAXCUST){ //Verifica se o número máximo de cadastros já não foi atingido.
                        printf("Número máximo de clientes cadastrados já foi atingido.\n\n");

                        break;
                    }

                    printf("Informe o DDD: ");
                    scanf("%d", &Customer[i].phone.DDD);
            
                    validTelephone = verifyTelephone(Customer[i].phone);
                    
                    while(validTelephone==1){
                        printf("(Inválido) Informe o DDD: ");
                        scanf("%d", &Customer[i].phone.DDD);
                        
                        validTelephone = verifyTelephone(Customer[i].phone);
                    }
                    
                    printf("Informe o número: ");
                    scanf("%li", &Customer[i].phone.number);
                
                    validTelephone = verifyTelephone(Customer[i].phone);
                
                    while(validTelephone==2){
                        printf("(Inválido) Informe o número: ");
                        scanf("%li", &Customer[i].phone.number);
                    
                        validTelephone = verifyTelephone(Customer[i].phone);
                    }
                    
                    printf("Dia de nascimento: ");
                    scanf("%d", &Customer[i].birth.day);
                    
                    validDate = verifyDate(Customer[i].birth);
                    
                    while(validDate==1){
                        printf("(1 a 30) - Dia de nascimento: ");
                        scanf("%d", &Customer[i].birth.day);
                    
                        validDate = verifyDate(Customer[i].birth);
                    }
                    
                    printf("Mês de nascimento: ");
                    scanf("%d", &Customer[i].birth.month);
                    
                    validDate = verifyDate(Customer[i].birth);
                    
                    while(validDate==2){
                        printf("(1 a 12) - Mês de nascimento: ");
                        scanf("%d", &Customer[i].birth.month);
                    
                        validDate = verifyDate(Customer[i].birth);
                    }
                    
                    printf("Ano de nascimento: ");
                    scanf("%d", &Customer[i].birth.year);
                    
                    validDate = verifyDate(Customer[i].birth);
                    
                    while(validDate==3){
                        printf("(1900 a 2023) - Ano de nascimento: ");
                        scanf("%d", &Customer[i].birth.year);
                        
                        validDate = verifyDate(Customer[i].birth);
                    }

                    getchar();
                    printf("Nome: ");
                    fgets(Customer[i].name, 50, stdin);
                
                    Customer[i].name[strlen(Customer[i].name)-1] = '\0';

                    printf("(Apenas os 11 números, sem pontos e hífen) CPF: ");
                    fgets(Customer[i].cpf, 13, stdin);
                    Customer[i].cpf[strlen(Customer[i].cpf)-1] = '\0';
                    validCPF = verifyCPF(Customer[i].cpf);     

                    while(validCPF!=0){
                        printf("(Apenas os 11 números, sem pontos e hífen) CPF: ");
                        fgets(Customer[i].cpf, 13, stdin);
                        Customer[i].cpf[strlen(Customer[i].cpf)-1] = '\0';
                        
                        validCPF = verifyCPF(Customer[i].cpf);   
                    }
                    
                    i++; //Inteirando i para indicar novo cadastro.

                    if(i < MAXCUST){ //Verifica se o número máximo de cadastros não foi atingido (de novo).
                        printf("Deseja continuar cadastrando? (""y"" se sim, ""n"" se não): ");
                        scanf("%c", &ask);

                        while(ask != 'y' && ask != 'n'){
                            printf("(Inválido) Deseja continuar cadastrando? ");
                            scanf(" %c", &ask);
                        }
                    } else {
                        ask = 'n';
                    }

                } while(ask != 'n');

                break;
            case '5':
                printf("Encerrando programa...\n");
                
                break;

            default:
                printf("(Inválido)\n");
        }

    } while(ask != '5');
        
    return 0;
}

int verifyDate(Date date){
    if(date.day<1 || date.day>30) return 1;
    else if(date.month<1 || date.month>12) return 2;
    else if(date.year<1900 || date.year>2023) return 3;
    else return 0;

    /* A função retorna 0 para caso a data seja válida. Se há um problema
       no dia, a função retorna 1. Se há um problema no mês, retorna 2, e
       se há no ano, retorna 3. o retorno de 1 não garante que o mês e o
       ano estejam corretos, mas o retorno de 3 garante que dia e mês estão
       corretos. Analogamente para o retorno de 2. */
}

int verifyTelephone(Telephone ph){
  if(ph.DDD <= 11 || ph.DDD >= 92) return 1;
  else if(ph.number>=10000000 && ph.number<=99999999) return 0;
  else if(ph.number>=900000000 && ph.number<=999999999) return 0;
  else return 2;

  /* A função funciona de modo análogo à verifyDate(). O retorno será 0 caso
     o número esteja correto. O primeiro if verifica se o DDD está correto. Os
     outros dois ifs verificam se o número é correto. O primeiro verifica para 
     casos de números com 8 dígitos numéricos e o segundo para números com 9 
     dígitos caso o primeiro seja um 9. Caso o número esteja incorreto, o re-
     torno é de 2. */
}

void showCustumer(Customer sCustomer[], int registred){
    Customer aux;

    for(int i = 0; i < registred - 1; i++){
        for(int j = i + 1; j < registred; j++){
            if(strcmp(sCustomer[i].name, sCustomer[j].name) > 0){
                aux = sCustomer[i];
                sCustomer[i] = sCustomer[j];
                sCustomer[j] = aux;
            }
        }
    }

    printf("\n--------------------------------------------------------------\n");

    for(int i = 0; i < registred; i++){
        printf("Nome: %s \n", sCustomer[i].name);
        printf("Telefone: (%d) %ld\n\n", sCustomer[i].phone.DDD, sCustomer[i].phone.number);
    }
    
    printf("--------------------------------------------------------------\n\n");

    /* O parâmetro registred serve para previnir que o algoritmo de ordenação acesse posições
       vazias do vetor de clientes. */
}

int verifyCPF(char cpf[12]){
    int score = 0, //Guarda o número de erros no CPF
        value = 0; //Valor da multiplicação dos números do CPF
    
    if(strlen(cpf)!=11) return 12; // Tamanho inválido
    else{
        for(int i = 0; i<11; i++){ // Verifica se o CPF contém apenas números
            if(cpf[i]>=48 && cpf[i]<=57){}
            else score++;
        }

        if(score==0){
            for(int i = 0; i<9; i++){
                value += (cpf[i] - 48) * (10 - i);
            }

            if(value%11 < 2){
                if((cpf[9] - 48) != 0) return 13; // Penúltimo número inválido
            }
            else if((11 - value%11) != (cpf[9] - 48)) return 13; // Penúltimo número inválido

            value = 0;
            for(int i = 0; i<10; i++){
                value += (cpf[i] - 48) * (11 - i);
            }

            if(value%11 < 2){
                if((cpf[10] - 48) != 0) return 14; // Último número inválido
            }
            else if((11 - value%11) != (cpf[10] - 48)) return 14; // Último número inválido
            else return 0; // CPF válido
        }
        else return score;
    }
}   

int difDate(Date finalDate, Date startDate){
    int deltaYear = 0,
        deltaDay = 0,
        deltaMonth = 0;  //Estas variáveis guardam a diferença de ano, mês e dia entre as datas

    deltaDay = finalDate.day - startDate.day;
    deltaMonth = finalDate.month - startDate.month;
    deltaYear = finalDate.year - startDate.year;

    if(deltaMonth < 0){
        deltaYear -= 1;
        deltaMonth = 12 + deltaMonth;
    }

    if(deltaDay < 0){
        deltaMonth -= 1;
        deltaDay = 30 + deltaDay;
    }
    
    return deltaDay + 30 * deltaMonth + 365 * deltaYear;
}

float calcInvest(Investment cInvest){ //Função que calcula valores relacionados a um investimento
    float profit = 0,
          taxes = 0,
          withdraw = 0, //Valor a ser resgatado
          interestRate = 0; //Taxas que não são impostos

    switch (cInvest.applicationType){
        case 1: //1 : LCI/LCA
        withdraw = 3;

        break;
        case 2: //2: CDB
        withdraw = 2;

        break;
        case 3: //3: Fundos
        withdraw = 1;

        break;
    }

    return withdraw;
}

Investment registerInvestiment(Investment rInvestiment){
    char option = '\0';

    do{
        printf("\n--------------------------------------------------------------\n");
        printf("Tipo de investimento:\n");
        printf("1) LCI/LCA;\n");
        printf("2) CDB\n");
        printf("3) Fundos\n");

        option = getch();

        if(option < '1' || option > '3'){
            printf("Opção inválida.\n");
        }
    } while(option < '1' || option > '3');

    switch (option){
    case '1': //Tipo 1: LCI/LCA
        rInvestiment.applicationType = 1; //Tipo 1: LCI/LCA

        break;
    case '2':
        rInvestiment.applicationType = 2; //Tipo 2: CDB
        
        break;
    case '3':
        rInvestiment.applicationType = 3; //Tipo 3: Fundos

        break;
    }
    
    printf("Órgão emissor: ");
    fgets(rInvestiment.emitter, 50, stdin);
    printf("Taxa de rendimento: ");
    scanf("%f", &rInvestiment.interestRate);
    getchar();

    rInvestiment.isActive = 'S';

    return rInvestiment;
}