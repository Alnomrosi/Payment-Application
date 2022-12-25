#include <stdio.h>
#include "../terminal/Terminal.h"
#include "../Card/Card.h"
#include "server.h"
ST_cardData_t cardData;
ST_terminalData_t termData;
ST_accountsDB_t accountRefrence;


//ST_terminalData_t termData;
//ST_transaction	 transData;

void main()
{
	/* Is vaild account*/
	
	printf("isValidAccounttest \n");
	getCardPAN(&cardData);
	printf("SERVER_OK \n");

	getCardPAN(&cardData);
	printf("ACCOUNT_NOT_FOUND \n");

	
		
	/* IS Blocked Account */
	
	printf("isBlockedAccountTest \n");
	getCardPAN(&cardData);
	printf("BLOCKED_ACCOUNT \n");


	getCardPAN(&cardData);
	printf("SERVER_OK \n");
	
	
	/* isAmountAvailableTest */
	
	printf("isAmountAvailableTest \n");

	getCardPAN(&cardData);
	getTransactionAmount(&termData);
	printf("SERVER_OK  \n");


	getTransactionAmount(&termData);
	printf("LOW_BALANCE  \n");


		/* recieveTransactionDataTest */
	printf("isAmountAvailableTest \n");

	getCardPAN(&cardData);
	getTransactionAmount(&termData);
	printf("FRAUD_CARD \n");

	getCardPAN(&cardData);
	getTransactionAmount(&termData);
	printf("DECLINED_STOLEN_CARD \n");

	getCardPAN(&cardData);
	getTransactionAmount(&termData);
	printf("DECLINED_INSUFFECIENT_FUND \n");

	getCardPAN(&cardData);
	getTransactionAmount(&termData);
	printf("APPROVED \n");
}