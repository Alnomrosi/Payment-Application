#pragma once
#ifndef Card
#define Card

typedef unsigned char uint8_t;

/*  The Card code  */

/* Typedefs */
typedef struct ST_cardData_t
{

    uint8_t cardHolderName[25];
    uint8_t primaryAccountNumber[20];
    uint8_t cardExpirationDate[6];
}ST_cardData_t;


typedef enum EN_cardError_t
{
    CARD_OK, WRONG_NAME, WRONG_EXP_DATE, WRONG_PAN
}EN_cardError_t;


/*  prototypes  */
EN_cardError_t getCardHolderName(ST_cardData_t* cardData);
EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData);
EN_cardError_t getCardPAN(ST_cardData_t* cardData);


void getCardHolderNametest(void);
void getCardPANtest(void);
void getCardExpiryDatetest(void);

#endif 