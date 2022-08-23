#include<stdio.h>
#include "app.h"
#include "card.h"
#include "terminal.h"
#include "server.h"

void appStart(void)
{
	ST_transaction_t transData;
	
	if(getCardHolderName(&(transData.cardHolderData))==WRONG_NAME)
	{
		printf("WRONG NAME");
		return;
	}
	
	if (getCardExpiryDate(&(transData.cardHolderData)) == WRONG_EXP_DATE)
	{
		printf("WRONG_EXP_DATE");
		return;
	}
	
	if (getCardPAN(&(transData.cardHolderData))==WRONG_PAN)
	{
		printf("WRONG PAN");
		return;
	}
	
	if (getTransactionDate(&(transData.terminalData))== WRONG_DATE)
	{
		printf(" WRONG_DATE");
		return;
	}

	if (isCardExpired(&(transData.cardHolderData), &(transData.terminalData)) == EXPIRED_CARD)
	{
		printf("DECLINED EXPIRED CARD");
		return;
	}
	
	setMaxAmount(&(transData.terminalData));
	getTransactionAmount(&(transData.terminalData));
	

	if (isBelowMaxAmount(transData.terminalData )== EXCEED_MAX_AMOUNT)
	{
		printf("DECLINED AMOUNT EXCEEDING LIMIT");
		return;
	}

	EN_transState_t trans_state = recieveTransactionData(&transData);

	if (trans_state == DECLINED_STOLEN_CARD)
	{
		printf("DECLINED INVALID ACCOUNT");
		return;
	}
	if (trans_state == DECLINED_INSUFFECIENT_FUND)
	{
		printf("DECLINED INSUFFECIENT FUND");
		return;
	}
	else if (trans_state == INTERNAL_SERVER_ERROR)
	{
		printf("INTERNAL SERVER ERROR");
		return;
	}

	printf("Have a nice Day");
	return;
}

void main(void)
{
    appStart();
}
