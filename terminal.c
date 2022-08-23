#include "terminal.h"
#include<stdio.h>
#define   CDE   cardData->cardExpirationDate 
#define   TD    termData->transactionDate


EN_terminalError_t getTransactionDate(ST_terminalData_t* termData)
{
	EN_terminalError_t x = ok;
	printf("Enter the transaction date ");
	gets(termData->transactionDate);
	uint8_t i = 0;
	uint8_t size_of_format = 0;
	if (termData->transactionDate == NULL)
	{
		x = WRONG_DATE;
		goto label;
	}
	while (TD[i])
	{
		size_of_format++;
		i++;
	}
	if (size_of_format != 10)
	{
		x = WRONG_DATE;
		goto label;
	}
	if (TD[2] != '/' && TD[5] != '/')
	{
		x = WRONG_DATE;
		goto label;
	}
	if (TD[3] > '1' && TD[4] > '2')
	{
		x = WRONG_DATE;
		goto label;
	}

	if (TD[0] > '3' && TD[2] > '1')
	{
		x = WRONG_DATE;
		goto label;
	}

	for (uint8_t j = 0; j <= 4; j++)
	{
		if (TD[j] >= '0' || TD[j] <= '9' || TD[j] == '/')
		{
			continue;
		}
		else
		{
			x = WRONG_DATE;
			break;
		}
	}
label:
	return x;
}


EN_terminalError_t isCardExpired(ST_cardData_t* cardData, ST_terminalData_t* termData)
{
	EN_terminalError_t x = ok;
	/*cardData->cardExpirationDate(06/25)*/
	/*termData->transactionDate(25/12/2022)*/
	if (CDE[3] < TD[8])
	{
		x = EXPIRED_CARD;
	}
	else if (CDE[4] < TD[9])
	{
		x = EXPIRED_CARD;
	}
	else if (CDE[4] > TD[9])
	{
		goto label;
	}
	else if (((CDE[1] < TD[4]) && (CDE[0] <= TD[3])) || (CDE[0] <= TD[3]))
	{
		x = EXPIRED_CARD;
	}

label:
	return(x);
}
EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData)
{
	EN_terminalError_t x = ok;
	printf("enter the transaction amount ");
	scanf_s("%f", &(termData->transAmount));
	if (termData->transAmount <= 0)
	{
		x = INVALID_AMOUNT;
	}
	return x;
}

EN_terminalError_t isBelowMaxAmount(ST_terminalData_t termData)
{
	EN_terminalError_t x = ok;
	if (termData.transAmount > termData.maxTransAmount)
	{
		x = EXCEED_MAX_AMOUNT;
	}
	return x;
}

EN_terminalError_t setMaxAmount(ST_terminalData_t* termData)
{
	EN_terminalError_t x = ok;
	termData->maxTransAmount = 50000;
	if (termData->maxTransAmount <= 0)
	{
		x = INVALID_MAX_AMOUNT;
	}
	return x;
}
