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
float calcInvest(Trade cTrade);
Investment registerInvestiment(Investment rInvestiment);
Customer registerCustomer(Customer rCustomer);
Trade registerTrade(Trade rTrade, int Id, Investment allInvestment[], int registered);
void showInvestment(Investment sInvestment[], int registered);

int main(){  
    int validDate=0, 
        validTelephone=0,
        i = 0, //Número de clientes cadastrados.
        j = 0, //Número de investimentos cadastrados.
        k = 0, //Número de aplicações cadastradas.
        match = -1;
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
        system("cls");

        switch(ask){
            case '1':
                do{
                    if(j >= 30){
                        printf("Número máximo de investimentos cadastrados já foi atingido.\n");
                        printf("Pressione ENTER para continuar");
                        getchar();
                        system("cls");
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
                        system("cls");
                    }
                    else break;
                    
                } while(ask != 'n');
                
                break;

            case '2':
                showCustumer(Customer, i);
                
                printf("Pressione ENTER para continuar");
                getchar();
                
                system("cls");
                
                break;
                
            case '3':
            
                break;
            
            case '4':
                do{
                    if(i >= MAXCUST){ //Verifica se o número máximo de cadastros já não foi atingido.
                        printf("Número máximo de clientes cadastrados já foi atingido.\n\n");
                        printf("Pressione ENTER para voltar ao menu");
                        getchar();
                        system("cls");
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
                    system("cls");
               
                } while(ask != 'n');

                break;
                
            case '5':
                do{
                    if(j==0){ //Verifica se há investimentos disponíveis
                            printf("Nenhuma opção de investimento disponível\n\n");
                            printf("Pressione ENTER para voltar ao menu");
                            getchar();
                            system("cls");
                            break;
                    }
                    else if(k >= 101){ //Verifica se o número máximo de cadastros foi atingido.
                        printf("Número máximo de aplicações cadastradas já foi atingido.\n");
                        printf("Pressione ENTER para continuar");
                        getchar();
                        system("cls");
                        break;
                    }
                
                    printf("********Cadastrar aplicação********\n\n");
                    printf("CPF: ");
                    fgets(Trade[k].customer.cpf, 13, stdin);
                    Trade[k].customer.cpf[strlen(Trade[k].customer.cpf)-1] = '\0';
                    
                    match = -1;
                    for(int x=0; x<i; x++){
                        if(strcmp(Trade[k].customer.cpf, Customer[x].cpf)==0){
                            match = x;
                            break;
                        }
                    } // Verifica se o CPF está cadastrado. se match != - 1, o nome está cadastrado.
                    
                    if(match == -1){
                        printf("\nCPF não cadastrado");
                        printf("\n\nDeseja voltar ao menu? (y/n): ");
                        scanf("%c", &ask);

                        while(ask != 'y' && ask != 'n'){
                            printf("(Inválido) Digite novamente: ");
                            scanf(" %c", &ask);
                        }
                        getchar();
                        if(ask=='y'){
                            system("cls");
                            break;
                        }
                        else{
                            ask = 'y';
                        }
                    }
                    else{
                        Trade[k].customer = Customer[match];
                        Trade[k] = registerTrade(Trade[k], k+1, Investment, j);
                        k++; //Inteirando k para indicar nova aplicação.
    
                        if(k < 101){ //Verifica se o número máximo de cadastros foi atingido (de novo).
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
                    }
                    
                    system("cls");
               
                } while(ask != 'n');
                break;
                
            case '6':
                printf("Encerrando programa...\n");
                
                break;

            default:
                printf("(Inválido) - Pressione ENTER para continuar");
                getchar();
                system("cls");
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

Trade registerTrade(Trade rTrade, int Id, Investment allInvestment[], int registered){
    int tInvestment; // armazena o número do investimento escolhido.
    
    rTrade.tradeId = Id;
    printf("\nEscolha um tipo de investimento:\n\n");
    showInvestment(allInvestment, registered);
    
    printf("\nInvestimento número: ");
    scanf("%d", &tInvestment);
    while(tInvestment<1 || tInvestment>registered){
        printf("Investimento inválido, digite outro: ");
        scanf("%d", &tInvestment);
    }
    
    rTrade.investment = allInvestment[tInvestment-1];
    
    printf("\n--Data de aplicação--\nDia: ");
    scanf("%d", &rTrade.applicationDate.day);
    printf("Mês: ");
    scanf("%d", &rTrade.applicationDate.month);
    printf("Ano: ");
    scanf("%d", &rTrade.applicationDate.year);
    
    while(verifyDate(rTrade.applicationDate)!=0){
        printf("(Inválido)");
        printf("\n--Data de aplicação--\nDia (1-30): ");
        scanf("%d", &rTrade.applicationDate.day);
        printf("Mês (1-12): ");
        scanf("%d", &rTrade.applicationDate.month);
        printf("Ano (1900-2023): ");
        scanf("%d", &rTrade.applicationDate.year);
    }
    
    printf("\nValor da aplicação: R$ ");
    scanf("%f", &rTrade.applicationValue);
    
    printf("\n--Data de retirada--\nDia: ");
    scanf("%d", &rTrade.withdrawDate.day);
    printf("Mês: ");
    scanf("%d", &rTrade.withdrawDate.month);
    printf("Ano: ");
    scanf("%d", &rTrade.withdrawDate.year);
    
    while(verifyDate(rTrade.withdrawDate)!=0 && difDate(rTrade.withdrawDate, rTrade.applicationDate)<0){
        printf("(Inválido)");
        printf("\n--Data de aplicação--\nDia (1-30): ");
        scanf("%d", &rTrade.withdrawDate.day);
        printf("Mês (1-12): ");
        scanf("%d", &rTrade.withdrawDate.month);
        printf("Ano (1900-2023): ");
        scanf("%d", &rTrade.withdrawDate.year);
    }
    getchar();
    
    // falta calcular o valor de retirada.
    
    return rTrade;
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

float calcInvest(Trade cTrade){ //Função que calcula valores relacionados a um investimento. Funciona em sistema de juros simples.
    int time = difDate(cTrade.withdrawDate, cTrade.applicationDate); //Variável que guarda diferença de dias entre aplicação e resgate.
    float profit = (time / 30) * (cTrade.investment.interestRate / 100) * cTrade.applicationValue, //Lucro sem reduções
          taxes = 0,
          adm = 0; //Taxa de administração
    
    if(cTrade.investment.applicationType != 1){
      if(time <= 180){
        taxes = 0.225 * profit;
      } else if(time >= 181 && time <= 360){
        taxes = 0.2 * profit;
      } else if(time >= 361 && time <= 720){
        taxes = 0.175 * profit;
      } else {
        taxes = 0.15 * profit;
      }
      
      if(cTrade.investment.applicationType == 3){
        adm = 0.01 * time / 360 * cTrade.applicationValue;
      }
    }

    cTrade.withdrawValue = profit + cTrade.applicationValue - (taxes + adm);

    printf("****************\n");
    printf("Lucro (sem redução de impostos): %.2f\n", profit);
    printf("Impostos: %.2f\n", taxes);
    printf("Taxas adicionais: %.2f\n", adm);
    printf("Valor a ser resgatado: %.2f\n", cTrade.withdrawValue);
    printf("Lucro (com reduções): %.2f\n", cTrade.withdrawValue - cTrade.applicationValue);
    printf("****************\n\n");
    printf("Pressione qualquer tecla para continuar");
    getchar();
    system("cls");;

    return cTrade.withdrawValue;
}

void showInvestment(Investment sInvestment[], int registered){
    printf("--------------------------------------------------------------\n");
    
    for(int i=0; i<registered; i++){
        printf("Investimento %d", i+1);
        printf("\n\nTipo de investimento: ");
        if(sInvestment[i].applicationType==1) printf("LCI/LCA.");
        else if(sInvestment[i].applicationType==2) printf("CDB.");
        else if(sInvestment[i].applicationType==3) printf("Fundos.");
        printf("\nTaxa de rendimento: %.2f", sInvestment[i].interestRate);
        printf("\nOrgão emissor: ");
        puts(sInvestment[i].emitter);
        
        printf("--------------------------------------------------------------\n");
    }
}
