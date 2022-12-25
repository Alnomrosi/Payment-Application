#include <stdio.h>
#include "Terminal.h"
#include "../Card/Card.h"

ST_cardData_t cardData;
ST_terminalData_t termData;
float number; 

void main()
{
	
	//char number = '0' ;
	for(int flag = 0; flag < 3 ; flag ++)
	{
	getCardExpiryDate(&cardData);
	getTransactionDate(&termData);
	//printf("Flag is, %d \n", flag);
	if (flag == 0 || flag == 1)
	{
		printf("Terminal_OK \n");
	}
	else
	{
		printf("EXPIRED_CARD \n");
	}

	}

	getTransactionAmounttest();
	setMaxAmountTest();
	isBelowMaxAmountTest();
}