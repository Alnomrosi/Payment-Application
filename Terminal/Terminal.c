#include "Terminal.h"
#include<time.h>
#include <stdio.h>
#include <stdlib.h>
typedef unsigned char uint8_t;
typedef unsigned int  uint16_t;
typedef unsigned long int uint32_t;



/*EN_terminalError_t getTransactionDate(ST_terminalData_t* termData)
{
	uint8_t TR_DATE[11];
	uint16_t counter = 0;
	uint16_t i =0 ;

	printf("Please Enter the Trancsaction Date DD/MM/YYYY: \n");
	scanf("%s", &TR_DATE);

	while (TR_DATE[i] != '\0')
	{
		if ((TR_DATE[i] >= '0' && TR_DATE[i] <= '9') || (TR_DATE[i] == '/'))
		{
			counter++ ;
		}
		else
		{
			return WRONG_DATE;
		}
		i++;
	}
	if (counter != 10)
	{
		return WRONG_DATE;
	}
	else if ((TR_DATE[2] != '/') && (TR_DATE[5] != '/'))
	{
		return WRONG_DATE;
	}
	else
	{
		for (i = 0 ; i <= counter ; i++)
		{
			termData->transactionDate[i] = TR_DATE[i];
			printf("%c", termData->transactionDate[i]);
		}
		return TERMINAL_OK;
	}

}
*/

EN_terminalError_t getTransactionDate(ST_terminalData_t* termData)
{

	time_t t;
	t = time(NULL);
	struct tm tm = *localtime(&t);
	uint32_t dy, mn, yy;
	dy = tm.tm_mday;
	mn = tm.tm_mon + 1;
	yy = tm.tm_year + 1900;

	//putting every digit in the number in a certain index in the array.
	termData->transactionDate[0] = dy / 10 + 48;
	termData->transactionDate[1] = dy % 10 + 48;

	// 47 represents the '/' in ascii.
	termData->transactionDate[2] = 47;

	termData->transactionDate[3] = mn / 10 + 48;
	termData->transactionDate[4] = mn % 10 + 48;

	termData->transactionDate[5] = 47;

	termData->transactionDate[6] = yy / 1000 + 48;
	termData->transactionDate[7] = (yy / 100) % 10 + 48;
	termData->transactionDate[8] = (yy / 10) % 10 + 48;
	termData->transactionDate[9] = yy % 10 + 48;

	termData->transactionDate[10] = '\0';

	printf(" The transaction Date is : ");
	for (int i = 0; i <= 10; i++)
	{
		printf("%c", termData->transactionDate[i]);
	}
	printf("\n");

	return TERMINAL_OK;
}

EN_terminalError_t isCardExpired(ST_cardData_t* cardData, ST_terminalData_t* termData)
{

	/* 
	
	Expire Date			MM/YY
	Transaction Date	DD/MM/YYYY
	
	*/

	uint8_t Exp_year = (cardData->cardExpirationDate[3] - '0') * 10 + (cardData->cardExpirationDate[4] - '0');
	uint8_t Term_year = (termData->transactionDate[8] - '0') * 10 + (termData->transactionDate[9] - '0');

	uint8_t Exp_month = (cardData->cardExpirationDate[0] - '0') * 10 + (cardData->cardExpirationDate[1] - '0');
	uint8_t Term_month = (termData->transactionDate[3] - '0') * 10 + (termData->transactionDate[4] - '0');

	if (Exp_year < Term_year) {
		printf("EXPIRED_CARD\n");
		return EXPIRED_CARD;
	}
	else if (Exp_year == Term_year) {
		if (Exp_month < Term_month) {
			printf("EXPIRED_CARD\n");
			return EXPIRED_CARD;
		}
		else {
			return TERMINAL_OK;
		}
	}
	else {
		return TERMINAL_OK;
	}
}

EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData)
{
	float amount = 0;
	printf("Please enter the Transaction Amount \n");
	scanf("%f", &amount);

	if (amount > 0.0000000)
	{
		termData->transAmount = amount;
		return TERMINAL_OK;
	}
	else
	{
		return INVALID_AMOUNT;
	}
}

EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData)
{
	//printf("Trans ammount %f \n", termData->transAmount);
	//printf("maxTransAmount %f \n", termData->maxTransAmount);


	if (termData->transAmount > termData->maxTransAmount )
	{
		return EXCEED_MAX_AMOUNT;
	}
	else
	{
		return TERMINAL_OK;
	}

}

EN_terminalError_t setMaxAmount(ST_terminalData_t* termData, float maxAmount)
{
	float in; 
	printf("Please Enter the Max Amount \n");
	scanf(" %f", &in);

	if (in <=  0)
	{
		return INVALID_MAX_AMOUNT;

	}
	else
	{
		termData->maxTransAmount = in;
		return TERMINAL_OK;
	}

}




/****************************************************************************************/


/* Test Functions */

void getTransactionDateTest(void)
{

	ST_terminalData_t termData;

	printf("function: getTransactionDateTest \n \n");

	if (getTransactionDate(&termData) == WRONG_DATE)
	{
		printf("WRONG_DATE \n");
	}
	else
	{
		printf("Terminal_OK \n");
	}
}

/* 
	isCardExpiredtest
*/
void isCardExpiredtest(void)
{
	ST_cardData_t cardData;
	ST_terminalData_t termData;

	/*
		Test case 1:
		Input: Expiry Date 12/25	(Larger Date)
		Expected Outpu: Terminal Ok
		Actual Output: Terminal_ok
	*/

	if (isCardExpired(&cardData,&termData) == EXPIRED_CARD)
	{
		printf("EXPIRED_CARD \n");
	}
	else
	{
		printf("Terminal_OK \n");
	}

	/*
	Test case 2:
	Input: Expiry Date 10/22		(Same Date)
	Expected Outpu: Terminal Ok
	Actual Output: Terminal_ok
	*/

	if (isCardExpired(&cardData, &termData) == EXPIRED_CARD)
	{
		printf("EXPIRED_CARD \n");
	}
	else
	{
		printf("Terminal_OK \n");
	}

		/*
	Test case 2:
	Input: Expiry Date 12/20	
	Expected Outpu: EXPIRED_CARD
	Actual Output: EXPIRED_CARD
	*/

	if (isCardExpired(&cardData, &termData) == EXPIRED_CARD)
	{
		printf("EXPIRED_CARD \n");
	}
	else
	{
		printf("Terminal_OK \n");
	}

}

/*
	getTransactionAmount
*/
void getTransactionAmounttest()
{
	ST_terminalData_t termData;

	printf("getTransactionAmount  \n");

	/*
	Test Case 1:
	Input data:	5000	> 0
	expected output: TERMINAL_OK
	actual output: TERMINAL_OK
	*/
	if (getTransactionAmount(&termData) == INVALID_AMOUNT)
	{
		printf("INVALID_AMOUNT  \n");
	}
	else
	{
		printf("TERMINAL_OK \n");
	}
		/*
	Test Case 2:
	Input data:	0
	expected output: TERMINAL_OK
	actual output: TERMINAL_OK
	*/
	if (getTransactionAmount(&termData) == INVALID_AMOUNT)
	{
		printf("INVALID_AMOUNT  \n");
	}
	else
	{
		printf("TERMINAL_OK \n");
	}

	/*
	Test Case 3:
	Input data:	-5000
	expected output: TERMINAL_OK
	actual output: TERMINAL_OK
	*/
	if (getTransactionAmount(&termData) == INVALID_AMOUNT)
	{
		printf("INVALID_AMOUNT  \n");
	}
	else
	{
		printf("TERMINAL_OK \n");
	}
	
}


/*
	setMaxAmountTest
*/
void setMaxAmountTest()
{
	ST_terminalData_t termData;
	float maxAmount = 0;
	
	printf("setMaxAmountTest  \n");


	/*
	Test Case 1:
	Input data:	5000	> 0
	expected output: TERMINAL_OK
	actual output: TERMINAL_OK
	*/
	if (setMaxAmount(&termData, maxAmount) == INVALID_MAX_AMOUNT)
	{
		printf("INVALID_MAX_AMOUNT \n");
	}
	else
	{
		printf("Terminal OK \n");
	}
	/*
	Test Case 2:
	Input data:	0
	expected output: TERMINAL_OK
	actual output: TERMINAL_OK
	*/
	if (setMaxAmount(&termData, maxAmount) == INVALID_MAX_AMOUNT)
	{
		printf("INVALID_MAX_AMOUNT \n");
	}
	else
	{
		printf("Terminal OK \n");
	}

	/*
	Test Case 3:
	Input data:	-5000
	expected output: TERMINAL_OK
	actual output: TERMINAL_OK
	*/
	if (setMaxAmount(&termData, maxAmount) == INVALID_MAX_AMOUNT)
	{
		printf("INVALID_MAX_AMOUNT \n");
	}
	else
	{
		printf("Terminal OK \n");
	}
}


	/*
	isBelowMaxAmountTest
	*/
void isBelowMaxAmountTest()
{
	ST_terminalData_t termData;
	float maxAmount;

	printf("isBelowMaxAmountTest \n");
	/*
	Test Case 1:
	Input Data:		Transaction Amount < MaxAmount
	Expected Output:	Terminal OK
	Actual Output:	Terminal OK
	*/
	getTransactionAmount(&termData);
	setMaxAmount(&termData, maxAmount);
	if (isBelowMaxAmount(&termData) == EXCEED_MAX_AMOUNT)
	{
		printf("EXCEED_MAX_AMOUNT \n");
	}
	else
	{
		printf("Terminal OK \n");
	}

	/*
		Test Case 2:
		Input Data:		Transaction Amount = MaxAmount
		Expected Output:	Terminal OK
		Actual Output:	Terminal OK
		*/
	getTransactionAmount(&termData);
	setMaxAmount(&termData, maxAmount);
	if (isBelowMaxAmount(&termData) == EXCEED_MAX_AMOUNT)
	{
		printf("EXCEED_MAX_AMOUNT \n");
	}
	else
	{
		printf("Terminal OK \n");
	}

	/*
	Test Case 1:
	Input Data:		Transaction Amount > MaxAmount
	Expected Output:	EXCEED_MAX_AMOUNT
	Actual Output:	EXCEED_MAX_AMOUNT
	*/
	getTransactionAmount(&termData);
	setMaxAmount(&termData, maxAmount);
	if (isBelowMaxAmount(&termData) == EXCEED_MAX_AMOUNT)
	{
		printf("EXCEED_MAX_AMOUNT \n");
	}
	else
	{
		printf("Terminal OK \n");
	}
}