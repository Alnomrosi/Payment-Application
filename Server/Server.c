
#include<stdio.h>
#include "Server.h"
#include "../Card/Card.h"
#include "../Terminal/Terminal.h"


ST_accountsDB_t accountsDB[255] = { {1000, RUNNING, "789456123123456798"},
                                {5000, RUNNING, "456123789456123789"},
                                {3000, BLOCKED, "123798456123465987"},
                                {2000, RUNNING, "321654987456132798"},
                                {9000, BLOCKED, "654789123654987321"},
                                {7000, RUNNING, "648971248962468452"},
                                {6000, BLOCKED, "654987123456798732"},
                                {1000, BLOCKED, "321546789513654897"},
                                {4000, RUNNING, "136871323216548751"},
                                {8000, RUNNING, "645854132168787654"} };

ST_accountsDB_t* refrance;
ST_transaction Trans_DB[] = {0};
EN_transStat_t result;
uint32_t num = 1;

EN_transStat_t recieveTransactionData(ST_transaction* transData)
{  
        if (isValidAccount(transData->cardHolderData.primaryAccountNumber, &refrance)) {
            printf("FRAUD_CARD\n");
            result = FRAUD_CARD;
            return FRAUD_CARD;
        }   

        if (isBlockedAccount(refrance)) {
            printf("DECLINED_STOLEN_CARD\n");
            result = DECLINED_STOLEN_CARD;
            return DECLINED_STOLEN_CARD;
        }
        if (isAmountAvailable(&transData->terminalData, &refrance)) {
            printf("DECLINED_INSUFFECIENT_FUND\n");
            result = DECLINED_INSUFFECIENT_FUND;
            return DECLINED_INSUFFECIENT_FUND;
        }
        refrance->balance -= transData->terminalData.transAmount;
        printf("Transaction is successful!\n");
        result = APPROVED;
        return APPROVED;
    
}

EN_serverError_t isValidAccount(ST_cardData_t* cardData, ST_accountsDB_t * accountRefrence)
{
    uint8_t Counter;

    for (int i = 0; i < 10; i++) {
        if (strcmp(cardData->primaryAccountNumber, accountsDB[i].primaryAccountNumber) == 0)
        {
            accountRefrence = &accountsDB[i];
            Counter = 1;
        }
    }

    if (Counter) {
        return SERVER_OK;
    }
    else {
       // printf("ACCOUNT_NOT_FOUND\n");
        return ACCOUNT_NOT_FOUND;
    }
}

EN_serverError_t isBlockedAccount(ST_accountsDB_t* accountRefrence)
{
    if (refrance->state == BLOCKED) {
        printf("BLOCKED_ACCOUNT\n");
        return BLOCKED_ACCOUNT;
    }
    else {
        return SERVER_OK;
    }
}

EN_serverError_t isAmountAvailable(ST_terminalData_t* termData, ST_accountsDB_t* accountRefrence)
{
    if (termData->transAmount > refrance->balance) {
        printf("LOW_BALANCE\n");
        return LOW_BALANCE;
    }
    else {
        return SERVER_OK;
    }

}

EN_serverError_t saveTransaction(ST_transaction* transData)
{
    transData->transState = result;
    transData->transactionSequenceNumber = num;

    Trans_DB[num] = *transData;
    num++;

    listSavedTransactions();
}

void listSavedTransactions(void)
{
    ST_terminalData_t termData;
    ST_accountsDB_t transdata;
    ST_cardData_t cardData;

    printf("################################################################### \n");
    printf("Transaction Sequence Number: %c \n", Trans_DB[num]);

    printf("Transaction Date:");
    for (int i = 0; i <= 10; i++)
    {
        printf("%c", termData.transactionDate[i]);
    }
    printf("\n Transaction State : %c \n", result);
    printf(" Terminal Max Amount: %f \n", termData.maxTransAmount);
    printf(" Cardholder Name:");
    for (int i = 0; i < 25; i++)
    {
       printf("%s", cardData.cardHolderName[i] );
    }

    printf("\n PAN: " );
    for (int i = 0; i < 20; i++)
    {
        printf("%c", cardData.primaryAccountNumber[i]);
    }

    printf("\nCard Expiration Date: ");
    for (int i = 0; i < 20; i++)
    {
        printf("%c", cardData.cardExpirationDate[i]);
    }
    printf("###################################################################");

}

                    /*      TEST FUNCTIONS       */



/* isVaildAccount */
void isValidAccounttest()
{
    ST_cardData_t cardData;
    printf("isValidAccounttest \n"); 

    /*
    Case 1:
    Input Data: Exisits PAN 
    Expected Output: Server ok
     Actual Output: server ok 
    */
    getCardPAN(& cardData);
    if (isValidAccount(&cardData, &refrance) == ACCOUNT_NOT_FOUND)
    {
        printf("ACCOUNT_NOT_FOUND  \n");
    }
    else
    {
        printf("SERVER_OK  \n");
    }
        /*
    Case 1:
    Input Data: NOT Exisits PAN 
    Expected Output: ACCOUNT_NOT_FOUND
    Actual Output: ACCOUNT_NOT_FOUND
    */
    getCardPAN(& cardData);
    if (isValidAccount(&cardData, &refrance) == ACCOUNT_NOT_FOUND)
    {
        printf("ACCOUNT_NOT_FOUND  \n");
    }
    else
    {
        printf("SERVER_OK  \n");
    }

}

/* isBlockedAccountTest */
void isBlockedAccountTest()
{
    printf("isBlockedAccountTest \n");
    ST_cardData_t cardData;
    ST_accountsDB_t accountRefrence;
    /*
       Case 1:
       Input Data: Blocked user
       Expected Output: BLOCKED_ACCOUNT
        Actual Output: BLOCKED_ACCOUNT
       */

    getCardPAN(&cardData);
    isValidAccount(&cardData, &accountRefrence);

     if (isBlockedAccount(&accountRefrence) == "BLOCKED_ACCOUNT")
    {
        printf("BLOCKED_ACCOUNT  \n");
    }
    else
    {
        printf("SERVER_OK  \n");
    }

     /*
     Case 2:
     Input Data: running
     Expected Output: Server ok
      Actual Output: server ok
     */
     getCardPAN(&cardData);
     isValidAccount(&cardData, &accountRefrence);

     if (isBlockedAccount(&accountRefrence) == "BLOCKED_ACCOUNT")
     {
         printf("BLOCKED_ACCOUNT  \n");
     }
     else
     {
         printf("SERVER_OK  \n");
     }
}


/* isAmountAvailableTest */
void isAmountAvailableTest()
{
    printf("isAmountAvailableTest \n");
    ST_terminalData_t termData;
    ST_cardData_t cardData;
    ST_accountsDB_t accountRefrence;

    /*
    Case 1:
    Input:  Valid balance
    Expected Output: SERVER_OK
    Acutal Output:  SERVER_OK
    */
         getCardPAN(&cardData);
         isValidAccount(&cardData, &accountRefrence);
         getTransactionAmount(&termData);
        if (isAmountAvailable(&termData, &accountRefrence) == "LOW_BALANCE")
        {
            printf("LOW_BALANCE  \n");
        }
        else
        {
            printf("SERVER_OK  \n");
        }
        /*
      Case 2:
      Input:  Not Valid balance
      Expected Output: LOW_BALANCE
      Acutal Output:  LOW_BALANCE
      */
        
        isValidAccount(&cardData, &accountRefrence);
        getTransactionAmount(&termData);
        if (isAmountAvailable(&termData, &accountRefrence) == "LOW_BALANCE")
        {
            printf("LOW_BALANCE  \n");
        }
        else
        {
            printf("SERVER_OK  \n");
        }


}

/* Test Functions */
void recieveTransactionDataTest()
{
    printf("isAmountAvailableTest \n");
    ST_terminalData_t termData;
    ST_cardData_t cardData;
    ST_accountsDB_t accountRefrence;
    ST_transaction transData;

    /*
    case 1: 
    Input data:  Not Valid Account
    Expected Output:
    Actual Output: 
    */
    getCardPAN(&cardData);
    isValidAccount(&cardData, &accountRefrence);
    getTransactionAmount(&termData);
    isAmountAvailable(&termData, &accountRefrence);

    if (recieveTransactionData(&transData) == "FRAUD_CARD")
    {
        printf("FRAUD_CARD\n");

    }
    if (recieveTransactionData(&transData) == "DECLINED_STOLEN_CARD")
    {
        printf("DECLINED_STOLEN_CARD\n");

    }
    if (recieveTransactionData(&transData) == "DECLINED_INSUFFECIENT_FUND")
    {
        printf("DECLINED_INSUFFECIENT_FUND\n");

    }
    else 
    {
        printf("APPROVED\n");

    }
        /*
      Test case 2: 
      Input data:  Valid Account but blocked state
      Expected Output:DECLINED_STOLEN_CARD
      Actual Output:DECLINED_STOLEN_CARD
      */
    getCardPAN(&cardData);
    isValidAccount(&cardData, &accountRefrence);
    getTransactionAmount(&termData);
    isAmountAvailable(&termData, &accountRefrence);

    if (recieveTransactionData(&transData) == "FRAUD_CARD")
    {
        printf("FRAUD_CARD\n");

    }
    if (recieveTransactionData(&transData) == "DECLINED_STOLEN_CARD")
    {
        printf("DECLINED_STOLEN_CARD\n");

    }
    if (recieveTransactionData(&transData) == "DECLINED_INSUFFECIENT_FUND")
    {
        printf("DECLINED_INSUFFECIENT_FUND\n");

    }
    else
    {
        printf("APPROVED\n");

    }

    /*
    Test case 3:
    Input data:  Valid Account and running but Low_Balance
    Expected Output: DECLINED_INSUFFECIENT_FUND
    Actual Output: DECLINED_INSUFFECIENT_FUND
    */
    getCardPAN(&cardData);
    isValidAccount(&cardData, &accountRefrence);
    getTransactionAmount(&termData);
    isAmountAvailable(&termData, &accountRefrence);

    if (recieveTransactionData(&transData) == "FRAUD_CARD")
    {
        printf("FRAUD_CARD\n");

    }
    if (recieveTransactionData(&transData) == "DECLINED_STOLEN_CARD")
    {
        printf("DECLINED_STOLEN_CARD\n");

    }
    if (recieveTransactionData(&transData) == "DECLINED_INSUFFECIENT_FUND")
    {
        printf("DECLINED_INSUFFECIENT_FUND\n");

    }
    else
    {
        printf("APPROVED\n");

    }

     /*
    Test case 4:
    Input data:  Valid Account and running and avilable balance
    Expected Output: APPROVED
    Actual Output: APPROVED
    */
    getCardPAN(&cardData);
    isValidAccount(&cardData, &accountRefrence);
    getTransactionAmount(&termData);
    isAmountAvailable(&termData, &accountRefrence);

    if (recieveTransactionData(&transData) == "FRAUD_CARD")
    {
        printf("FRAUD_CARD\n");

    }
    if (recieveTransactionData(&transData) == "DECLINED_STOLEN_CARD")
    {
        printf("DECLINED_STOLEN_CARD\n");

    }
    if (recieveTransactionData(&transData) == "DECLINED_INSUFFECIENT_FUND")
    {
        printf("DECLINED_INSUFFECIENT_FUND\n");

    }
    else
    {
        printf("APPROVED\n");

    }
}