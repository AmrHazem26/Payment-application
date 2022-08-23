#include "card.h"
#include<stdio.h>
#define CED  cardData->cardExpirationDate 

EN_cardError_t getCardHolderName(ST_cardData_t* cardData)
{
    EN_cardError_t x=OK;
	printf("Enter user name ");
	gets(cardData->cardHolderName);
	
	uint8_t i=0;
	uint8_t size_of_name=0;
	while (cardData->cardHolderName[i])
	{
		
		size_of_name ++;
		i++;
	}

	if (size_of_name > 24 && size_of_name < 20 && cardData->cardHolderName ==NULL)
	{  
		x = WRONG_NAME;
	}
	return x;
}


EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData)
{   
	EN_cardError_t x = OK;
	printf("Enter the expiry date ");
	gets(cardData->cardExpirationDate);

	uint8_t i = 0;
	uint8_t size_of_format = 0;
	if(cardData->cardExpirationDate==NULL)
	{
		x = WRONG_EXP_DATE;
		goto label;
	}
	while (cardData->cardExpirationDate[i])
	{
		size_of_format++;
		i++;
	}
	if(size_of_format!=5)
	{
		x = WRONG_EXP_DATE;
		goto label;
	}
	if(cardData->cardExpirationDate[2]!= '/' )
	{
		x = WRONG_EXP_DATE;
		goto label;
	}
	if(cardData->cardExpirationDate[0]>'1' && cardData->cardExpirationDate[1]>'2')
	{
		x = WRONG_EXP_DATE;
		goto label;
	}
	for(uint8_t j=0 ; j<=4 ; j++)
	{
		if(CED[j]>='0' || CED[j]<='9' || CED[j] == '/')  
		{
			continue;
		}
		else
		{
				x = WRONG_EXP_DATE;
				break;
		}
	}
label:
	return x;
}
EN_cardError_t getCardPAN(ST_cardData_t* cardData)
{
	EN_cardError_t x = OK;
	printf("Enter user PAN ");
	gets(cardData->primaryAccountNumber);

	uint8_t i = 0;
	uint8_t size_of_number = 0;
	while (cardData->primaryAccountNumber[i])
	{

		size_of_number++;
		i++;
	}

	if (size_of_number > 19 || size_of_number < 16 || cardData->primaryAccountNumber == NULL)
	{
		x = WRONG_PAN;
	}
	return x;
}
