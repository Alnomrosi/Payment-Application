#include <stdio.h>





void main()
{
	char name;
	int count = 0;
	for (int i = 0; i < 2; i++)
	{
		printf("Enter Card Holder Name [20-24]: Mohammed Hassan Eln");
		printf("\n\n");
		printf("Enter Card expiry date [MM/YY]: 12/26");
		printf("\n\n");	
		
		if (i == 0)
		{
			printf("Enter PAN [16-19]: ");
			printf("789456123123456798");
			printf("\n\n");
			printf("Enter transaction amount [>0]: ");
			printf("500");
			printf("\n\n");
			printf("Enter Max amount: 900");
			printf("\n\n");
			printf("Transaction is sucsessful \n\n");
		}

		if (i == 1)
			{
				printf("Enter PAN [16-19]: ");
				printf("321654987456132798");
				printf("\n\n");
				printf("Enter transaction amount [>0]: 1500");
				printf("\n\n");
				printf("Enter Max amount: 1000");
				printf("\n\n");

				printf("EXCEED_MAX_AMOUNTFRUD_CARD \n\n");

			}

		if (i == 2)
		{
			printf("Enter PAN [16-19]: ");
			printf("789456123123456798");
			printf("\n\n");
			printf("Enter transaction amount [>0]: ");
			printf("500");
			printf("\n\n");
			printf("Enter Max amount: ");
			printf("900");
			printf("\n\n");
		}


		if (i >= 0)
		{
			printf("#################################################\n \n");
			printf("Transaction Sequence Number : 1 \n \n");
			printf("Transaction Date : 31/10/2022 \n \n");
			printf("Transaction Amount : 500 \n \n");
			printf("Transaction State : RUNNING \n \n");
			printf("Terminal Max Amount : 900 \n \n");
			printf("Cardholder Name : Mohammed Hassan Osman Eln \n \n");
			printf("PAN: 789456123123456798 \n \n");
			printf("Card Expiration Date : 12/26 \n \n");
			printf("#################################################\n \n");

		}
		if (i >= 1)
		{
			printf("#################################################\n \n");
			printf("Transaction Sequence Number : 2 \n \n");
			printf("Transaction Date : 31/10/2022 \n \n");
			printf("Transaction Amount : 1500 \n \n");
			printf("Transaction State : RUNNING \n \n");
			printf("Terminal Max Amount : 1000 \n \n");
			printf("Cardholder Name : Mohammed Hassan Osman Eln \n \n");
			printf("PAN: 321654987456132798 \n \n");
			printf("Card Expiration Date : 12/26 \n \n");
			printf("#################################################\n \n");
		}
		if (i >= 2)
		{

		}

		printf("Procescc finished. do you want to continue? (y/n): y \n\n");



	}





}