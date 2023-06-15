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
Customer registerCustomer(Customer rCustomer);
Trade registerTrade(Trade rTrade);

int main(){  
    int validDate=0, 
        validTelephone=0,
        i = 0, //Número de clientes cadastrados.
        j = 0, //Número de investimentos cadastrados.
        k = 0; //Número de aplicações cadastradas.
    Customer Customer[MAXCUST];
    char ask = 'x'; //Verifica se o usuário quer ou não continuar cadastrando clientes. Verifica, também, a opção escolhida no menu.
    Investment Investment[MAXINVEST];
    Trade Trade[101];

    do{
        printf("********Menu********\n");
        printf("1) Cadastrar investimento\n");
        printf("2) Mostrar todos os clientes cadastrados\n");
        printf("3) Apresentar extrato\n");
        printf("4) Cadastrar cliente\n");
        printf("5) Cadastrar aplicação\n");
        printf("6) Sair\n\n");
        printf("Escolha uma opção: ");
        scanf("%c", &ask);
        getchar();
        system("clear");

        switch(ask){
            case '1':
                do{
                    if(j >= 30){
                        printf("Número máximo de investimentos cadastrados já foi atingido.\n");
                        printf("Pressione ENTER para continuar");
                        getchar();
                        system("clear");
                        break;
                    }

                    Investment[j] = registerInvestiment(Investment[j]);
                    j++; //Incrementa o número de investimentos cadastrados

                    if(j < 30){ //Verifica se o número máximo não foi atingido
                        printf("\nDeseja continuar cadastrando? (y/n) ");
                        scanf(" %c", &ask);

                        while(ask != 'y' && ask != 'n'){
                            printf("Opção inválida. Digite novamente. ");
                            scanf(" %c", &ask);
                        }
                        getchar();
                        system("clear");
                    }
                    else break;
                    
                } while(ask != 'n');
                
                break;

            case '2':
                showCustumer(Customer, i);
                
                printf("Pressione ENTER para continuar");
                getchar();
                
                system("clear");
                
                break;
                
            case '3':
            
                break;
            
            case '4':
                do{
                    if(i >= MAXCUST){ //Verifica se o número máximo de cadastros já não foi atingido.
                        printf("Número máximo de clientes cadastrados já foi atingido.\n\n");
                        printf("Pressione ENTER para voltar ao menu");
                        getchar();
                        system("clear");
                        break;
                    }

                    Customer[i] = registerCustomer(Customer[i]);
                    i++; //Inteirando i para indicar novo cadastro.

                    if(i < MAXCUST){ //Verifica se o número máximo de cadastros não foi atingido (de novo).
                        printf("\nDeseja continuar cadastrando? (""y"" se sim, ""n"" se não): ");
                        scanf("%c", &ask);

                        while(ask != 'y' && ask != 'n'){
                            printf("(Inválido) Deseja continuar cadastrando? ");
                            scanf(" %c", &ask);
                        }
                        getchar();
                        
                    } else {
                        ask = 'n';
                    }
                    system("clear");
               
                } while(ask != 'n');

                break;
                
            case '5':
                do{
                if(j==0){
                        printf("Nenhuma opção de investimento disponível\n\n");
                        printf("Pressione ENTER para voltar ao menu");
                        getchar();
                        system("clear");
                        break;
                }
                
                    Trade[k] = registerTrade(Trade[k]);
                    k++; //Inteirando k para indicar nova aplicação.

                    if(k < 101){ //Verifica se o número máximo de cadastros não foi atingido (de novo).
                        printf("\nDeseja cadastrar outra aplicação? (""y"" se sim, ""n"" se não): ");
                        scanf("%c", &ask);

                        while(ask != 'y' && ask != 'n'){
                            printf("(Inválido) Deseja cadastrar outra aplicação? ");
                            scanf(" %c", &ask);
                        }
                        getchar();
                        
                    } else {
                        ask = 'n';
                    }
                    system("clear");
               
                } while(ask != 'n');
                
                
                break;
                
            case '6':
                printf("Encerrando programa...\n");
                
                break;

            default:
                printf("(Inválido) - Pressione ENTER para continuar");
                getchar();
                system("clear");
        }

    } while(ask != '6');

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
    
    printf("********Clientes cadastrados********\n\n");
    
    printf("--------------------------------------------------------------\n\n");
    
    for(int i = 0; i < registred; i++){
        printf("Nome: %s \n", sCustomer[i].name);
        printf("Telefone: (%d) %ld\n", sCustomer[i].phone.DDD, sCustomer[i].phone.number);
        printf("\n--------------------------------------------------------------\n\n");
    }

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

int difDate(Date finalDate, Date startDate){ //A função considera um mês com 30 dias, e, portanto, um ano com 360 dias
    return (finalDate.year - startDate.year)*360 + (finalDate.month - startDate.month)*30 + finalDate.day - startDate.day;
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
    
        printf("********Cadastrar investimento********\n\n");
        
        printf("Tipo de investimento:\n");
        printf("1) LCI/LCA;\n");
        printf("2) CDB\n");
        printf("3) Fundos\n");
        
        printf("\nEscolha uma opção: ");
        scanf(" %c", &option);

        while(option < '1' || option > '3'){
            printf("(Inválido) Escolha uma opção: ");
            scanf(" %c", &option);
        }
        

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
    getchar();
    printf("Órgão emissor: ");
    fgets(rInvestiment.emitter, 50, stdin);
    printf("Taxa de rendimento: ");
    scanf("%f", &rInvestiment.interestRate);
    getchar();
    rInvestiment.isActive = 'S';

    return rInvestiment;
}

Customer registerCustomer(Customer rCustomer){
    printf("********Cadastrar cliente********\n\n");
    printf("Informe o DDD: ");
    scanf("%d", &rCustomer.phone.DDD);

    while(verifyTelephone(rCustomer.phone)==1){
        printf("(Inválido) Informe o DDD: ");
        scanf("%d", &rCustomer.phone.DDD);
    }
    
    printf("Informe o número: ");
    scanf("%li", &rCustomer.phone.number);


    while(verifyTelephone(rCustomer.phone)==2){
        printf("(Inválido) Informe o número: ");
        scanf("%li", &rCustomer.phone.number);
    }
    
    printf("Dia de nascimento: ");
    scanf("%d", &rCustomer.birth.day);
    
    while(verifyDate(rCustomer.birth)==1){
        printf("(1 a 30) - Dia de nascimento: ");
        scanf("%d", &rCustomer.birth.day);
    }
    
    printf("Mês de nascimento: ");
    scanf("%d", &rCustomer.birth.month);
    
    while(verifyDate(rCustomer.birth)==2){
        printf("(1 a 12) - Mês de nascimento: ");
        scanf("%d", &rCustomer.birth.month);
    }
    
    printf("Ano de nascimento: ");
    scanf("%d", &rCustomer.birth.year);
    
    while(verifyDate(rCustomer.birth)==3){
        printf("(1900 a 2023) - Ano de nascimento: ");
        scanf("%d", &rCustomer.birth.year);
    }
    getchar();
    
    printf("Nome: ");
    fgets(rCustomer.name, 50, stdin);

    rCustomer.name[strlen(rCustomer.name)-1] = '\0';

    printf("(Apenas os 11 números, sem pontos e hífen) CPF: ");
    fgets(rCustomer.cpf, 13, stdin);
    
    rCustomer.cpf[strlen(rCustomer.cpf)-1] = '\0';

    while(verifyCPF(rCustomer.cpf) != 0){
        printf("(Apenas os 11 números, sem pontos e hífen) CPF: ");
        fgets(rCustomer.cpf, 13, stdin);
        rCustomer.cpf[strlen(rCustomer.cpf)-1] = '\0';
    }
    
    return rCustomer;
}

Trade registerTrade(Trade rTrade){
    
}

void resume(Investment investment, Customer customer, Trade trade){
    Date actualDate;

    printf("Dia atual: ");
    scanf("%d", &actualDate.day);

    while(verifyDate(actualDate)==1){
        printf("(1 a 30) - Dia atual: ");
        scanf("%d", &actualDate.day);
    }
    
    printf("Mês atual: ");
    scanf("%d", &actualDate.month);
    
    while(verifyDate(actualDate)==2){
        printf("(1 a 12) - Mês atual: ");
        scanf("%d", &actualDate.month);
    }
    
    printf("Ano atual: ");
    scanf("%d", &actualDate.year);
    
    while(verifyDate(actualDate)==3){
        printf("(1900 a 2023) - Ano atual: ");
        scanf("%d", &actualDate.year);
    }

    
}
