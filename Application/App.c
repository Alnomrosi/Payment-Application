#include "App.h"


ST_cardData_t cardData;
ST_terminalData_t termData;
ST_transaction transData;
float amount;

void appStart(void) {
    
    uint8_t flag;
    
    do {


        // card
        getCardHolderName(&cardData);
        getCardExpiryDate(&cardData);
        getCardPAN(&cardData);

        //terminal 
        getTransactionDate(&termData);
        isCardExpired(&cardData, &termData);
        getTransactionAmount(&termData);
        setMaxAmount(&termData, amount);
        isBelowMaxAmount(&termData);

        //server module
        transData.cardHolderData = cardData;
        transData.terminalData = termData;

        // server
        recieveTransactionData(&transData);
        saveTransaction(&transData);

        printf("Process finished. do you want to continue? (y/n): ");
        scanf(" %c", &flag);



    } while (flag != 'n');

   
}


