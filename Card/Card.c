#include "Card.h"
#include <stdio.h>

typedef unsigned char uint8_t;
typedef unsigned int  uint16_t;
EN_cardError_t getCardHolderName(ST_cardData_t* cardData)
{
	uint8_t Name[25]; 
	uint16_t counter = 0; 
	uint16_t i = 0;
	printf("Enter card holder name [20-24]:\n");
	scanf("%[^\n]%*c", &Name);

	/* Check name Size*/
	while (Name[i] != '\0')
	{
		if (Name[i] != ' ')
		{
			if ((Name[i] >= 'a' && Name[i] <= 'z') || (Name[i] >= 'A' && Name[i] <= 'Z'))
			{
					counter++;
			}
		}
		i++;
	};

	//printf("counter is  %d \n", counter);

	/* Check Range */
	if (counter > 24 || counter < 20)
	{
		//printf("Wrong Name  %d \n" ,counter);
		return WRONG_NAME;
	}
	else
	{
		//printf("Card Ok \n");

		for (i = 0; i < counter; i++)
		{
			cardData->cardHolderName[i] = Name[i];
		}

		return CARD_OK;
	}
}
EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData)
{
	uint8_t Date[5];
	uint16_t counter = 0;
	uint16_t i = 0;

	printf("Enter the Card Expiration Date MM/YY: \n");
	scanf("%s", &Date);


	while (Date[counter] != '\0')
	{
		if ((Date[counter] >= '0' && Date[counter] <= '9') || (Date[counter] == '/'))
		{
			counter++;
		}
		if (Date[2] != '/')
		{
			return WRONG_EXP_DATE;
		}
	};

	// MM/YY 
		
	//printf("counter is %d \n", counter); 
		// check M1
		if ((counter == 5) && (Date[0] <= '1' && Date[0] >= '0'))
		{	


			//check M2
			if (Date[0] == '1' && Date[1] > '2')
			{


				return WRONG_EXP_DATE;
			}
			else
			{
				for (i = 0; i < 6; i++)
				{
					cardData->cardExpirationDate[i] = Date[i];
				}
				return CARD_OK;
			}
		}
		else
		{
			return WRONG_EXP_DATE;
		}
}
EN_cardError_t getCardPAN(ST_cardData_t* cardData)
{
	uint8_t Number[20] = "0";
	uint16_t counter = 0;
	uint16_t i = 0;
	

	printf("Enter the Card PAN : \n");
	scanf("%[^\n]%*c", &Number);

	while (Number[counter] != '\0')
	{
		if (Number[counter] >= '0' && Number[counter] <= '9')
		{
			counter++;

		}
		else
		{
			return WRONG_PAN;
		}
	};

	
	if (counter > 19 || counter < 16)
	{
		return WRONG_PAN;
	}
	else
	{
		return CARD_OK;
	}
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////


/* 
	Test Functions 
*/

/*
Authour : Mohammed Hassan Elnomros
getCardHolderNametest 
*/
void getCardHolderNametest(void)
{
	
	ST_cardData_t cardData;

	/*
	Test case 1:
	test Date: Null
	Expected result: WRONG_EXP_DATE
	Actual Result: WRONG_EXP_DATE
	*/
	if (getCardHolderName(&cardData) == WRONG_NAME)
	{
		printf("WRONG_NAME \n");
	}
	else
	{
		printf("CARD_OK \n");
	}

	/*
	Test case 2:
	test Date: Mohammed
	Expected result: WRONG_EXP_DATE
	Actual Result: WRONG_EXP_DATE
	*/
	if (getCardHolderName(&cardData) == WRONG_NAME)
	{
		printf("WRONG_NAME \n");
	}
	else
	{
		printf("CARD_OK \n");
	}

	/*
	Test case 3:
	test Date: Mohammed Hassan Osman Elnomrsi
	Expected result: WRONG_EXP_DATE
	Actual Result: WRONG_EXP_DATE
	*/
	if (getCardHolderName(&cardData) == WRONG_NAME)
	{
		printf("WRONG_NAME \n");
	}
	else
	{
		printf("CARD_OK \n");
	}

	/*
	Test case 4:
	test Date:	Mohammed Hassan Osman Eln
	Expected result: CARD_OK
	Actual Result: CARD_OK
	*/
	if (getCardHolderName(&cardData) == WRONG_NAME)
	{
		printf("WRONG_NAME \n");
	}
	else
	{
		printf("CARD_OK \n");
	}

}


/* 
Authour: Mohammed Hassan Osman 
Functiom: getCardExpiryDatetest 
*/
void getCardExpiryDatetest(void)
{

	ST_cardData_t cardData;

	printf("\n	 getCardExpiryDatetest 		\n");

	/*
	Test case 1:
	test Date: null
	Expected result: WRONG_EXP_DATE
	Actual Result: WRONG_EXP_DATE
	*/
	if (getCardExpiryDate(&cardData) == WRONG_EXP_DATE)
	{
		printf("WRONG_EXP_DATE \n");
	}
	else
	{
		printf("CARD_OK \n");
	}

	/*
	Test case 2:
	test Date: 10/2022
	Expected result: WRONG_EXP_DATE
	Actual Result: WRONG_EXP_DATE
	*/
	if (getCardExpiryDate(&cardData) == WRONG_EXP_DATE)
	{
		printf("WRONG_EXP_DATE \n");
	}
	else
	{
		printf("CARD_OK \n");
	}

	/*
	Test case 4:
	test Date: 1/20
	Expected result: WRONG_EXP_DATE
	Actual Result: WRONG_EXP_DATE
	*/
	if (getCardExpiryDate(&cardData) == WRONG_EXP_DATE)
	{
		printf("WRONG_EXP_DATE \n");
	}
	else
	{
		printf("CARD_OK \n");
	}

		/*
	Test case 4:
	test Date: 10/2
	Expected result: WRONG_EXP_DATE
	Actual Result: WRONG_EXP_DATE
	*/
	if (getCardExpiryDate(&cardData) == WRONG_EXP_DATE)
	{
		printf("WRONG_EXP_DATE \n");
	}
	else
	{
		printf("CARD_OK \n");
	}
		/*
	Test case 5:
	test Date: 10/2
	Expected result: WRONG_EXP_DATE
	Actual Result: WRONG_EXP_DATE
	*/
	if (getCardExpiryDate(&cardData) == WRONG_EXP_DATE)
	{
		printf("WRONG_EXP_DATE \n");
	}
	else
	{
		printf("CARD_OK \n");
	}

	/*
	Test case 6:
	test Date: 40/25
	Expected result: WRONG_EXP_DATE
	Actual Result: WRONG_EXP_DATE
	*/
	if (getCardExpiryDate(&cardData) == WRONG_EXP_DATE)
	{
		printf("WRONG_EXP_DATE \n");
	}
	else
	{
		printf("CARD_OK \n");
	}

		/*
	Test case 7:
	test Date: 10/22
	Expected result: CARD_OK
	Actual Result: CARD_OK
	*/
	if (getCardExpiryDate(&cardData) == WRONG_EXP_DATE)
	{
		printf("WRONG_EXP_DATE \n");
	}
	else
	{
		printf("CARD_OK \n");
	}
	//////////////
	
}


/*
Authour: Mohammed Hassan Osman
Functiom: getCardPANtest
*/
void getCardPANtest(void)
{
	printf("\n	 getCardPANtest 	\n");

	ST_cardData_t cardData;

	/*
	Test case 1:
	test Date: Null
	Expected result: WRONG_EXP_DATE
	Actual Result: WRONG_EXP_DATE
	*/
	if (getCardPAN(&cardData) == WRONG_PAN)
	{
		printf("WRONG_PAN \n");
	}
	else
	{
		printf("CARD_OK \n");
	}

		/*
	Test case 2:
	test Date: 123
	Expected result: WRONG_EXP_DATE
	Actual Result: WRONG_EXP_DATE
	*/
	if (getCardPAN(&cardData) == WRONG_PAN)
	{
		printf("WRONG_PAN \n");
	}
	else
	{
		printf("CARD_OK \n");
	}

	/*
	Test case 3:
	test Date: abc123
	Expected result: WRONG_EXP_DATE
	Actual Result: WRONG_EXP_DATE
	*/
	if (getCardPAN(&cardData) == WRONG_PAN)
	{
		printf("WRONG_PAN \n");
	}
	else
	{
		printf("CARD_OK \n");
	}
	/*
	Test case 4:
	test Date: 1234567890123456788901
	Expected result: WRONG_EXP_DATE
	Actual Result: WRONG_EXP_DATE
	*/
	if (getCardPAN(&cardData) == WRONG_PAN)
	{
		printf("WRONG_PAN \n");
	}
	else
	{
		printf("CARD_OK \n");
	}
	/*
	Test case 5:
	test Date: 12345678901234567
	Expected result: CARD_OK
	Actual Result: CARD_OK
	*/
	if (getCardPAN(&cardData) == WRONG_PAN)
	{
		printf("WRONG_PAN \n");
	}
	else
	{
		printf("CARD_OK \n");
	}
}

