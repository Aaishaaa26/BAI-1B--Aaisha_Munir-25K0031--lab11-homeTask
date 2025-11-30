#include <stdio.h>
#include <string.h>

struct accountType{
    float savings;
    float current;
    float deposit;
};

struct Transaction{
    char type;
    float amount;
    char date[20];
};

struct Account{
    struct accountType balance;
    struct Transaction transactions[100]; //assuming 100 ho skti
    int transCount;
    char creationDate[20];
    char lastTransactionDate[20];
};

struct accountType calcInterestRates(struct accountType account){
    struct accountType interests;
    interests.savings = account.savings * 0.04;
    interests.current = 0.0;
    interests.deposit = account.deposit * 0.07;
    return interests;
}

struct Account addTransaction(struct Account acc, char type, float amount, char date[], char accType){
    float newBal;
    if(type == 'd'){
        if(accType == 's') acc.balance.savings = acc.balance.savings + amount;
        else if(accType == 'c') acc.balance.current = acc.balance.current + amount;
        else if(accType == 'f') acc.balance.deposit =acc.balance.deposit+ amount;
    } else if(type == 'w'){
        if(accType == 's'){
            newBal = acc.balance.savings - amount;
            if(newBal < 1000){
                printf("Cannot withdraw. Minimum balance of $1000 required.\n");
                return acc;
            }
            acc.balance.savings = newBal;
        } else if(accType == 'c'){
            newBal = acc.balance.current - amount;
            if(newBal < 5000){
                printf("Cannot withdraw. Minimum balance of $5000 required.\n");
                return acc;
            }
            acc.balance.current = newBal;
        } else if(accType == 'f'){
            newBal = acc.balance.deposit - amount;
            if(newBal < 10000){
                printf("Cannot withdraw. Minimum balance of $10000 required.\n");
                return acc;
            }
            acc.balance.deposit = newBal;
        }
    }
    acc.transactions[acc.transCount].type = type;
    acc.transactions[acc.transCount].amount = amount;
    strcpy(acc.transactions[acc.transCount].date, date);
    strcpy(acc.lastTransactionDate, date);
    acc.transCount++;
    return acc;
}

void printTransactions(struct Account acc){
    printf("\nTransaction History:\n");
    printf("Type\tAmount\tDate\n");
    for(int i=0;i<acc.transCount;i++){
        printf("%c\t%.2f\t%s\n", acc.transactions[i].type, acc.transactions[i].amount, acc.transactions[i].date);
    }
}

int main(){
    struct Account acc;
    acc.transCount = 0;

    printf("Enter Account Creation Date (YYYY-MM-DD): ");
    scanf("%s", acc.creationDate);
    strcpy(acc.lastTransactionDate, acc.creationDate);

    do{
        printf("Enter Savings Balance (minimum 1000): ");
        scanf("%f", &acc.balance.savings);
    } while(acc.balance.savings < 1000);

    do{
        printf("Enter Current Balance (minimum 5000): ");
        scanf("%f", &acc.balance.current);
    } while(acc.balance.current < 5000);

    do{
        printf("Enter Fixed Deposit Balance (minimum 10000): ");
        scanf("%f", &acc.balance.deposit);
    } while(acc.balance.deposit < 10000);

    struct accountType interests = calcInterestRates(acc.balance);
    printf("\nInterest Amounts:\nSavings: %.2f\nCurrent: %.2f\nFixed Deposit: %.2f\n",
        interests.savings, interests.current, interests.deposit);

    char date[20];
    char ttype, accType;
    float amount;

    for(int i=0; i<2; i++){
        printf("\nEnter date of transaction (YYYY-MM-DD): ");
        scanf("%s", date);
        printf("Enter transaction type (d for deposit & w for withdrawal): ");
        scanf(" %c", &ttype);
        ttype = tolower(ttype);
        printf("Enter account type (s for savings, c for current, f for fixed deposit): ");
        scanf(" %c", &accType);
        accType = tolower(accType);
        printf("Enter amount: ");
        scanf("%f", &amount);
        acc = addTransaction(acc, ttype, amount, date, accType);
    }

    printTransactions(acc);

    printf("\nAccount Created: %s\nLast Transaction: %s\n", acc.creationDate, acc.lastTransactionDate);

    return 0;
}
