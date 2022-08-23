#include "server.h"
#include "string.h"
#include <stdio.h>

ST_accountsDB_t SSA[255] = {{100000,"11112222333344444"},{20000,"44443333222211111"},{3000000,"99998888777766665"}};

ST_accountsDB_t SSA_stolen[255] = { {3000000,"99998888777766665"} };

ST_transaction_t SST[255] = {0}; /*transection*/

uint8_t seq = 0;


EN_transState_t recieveTransactionData(ST_transaction_t* transData)
{
	EN_transState_t x = APPROVED;
	if (isValidAccount(&(transData->cardHolderData)) == ACCOUNT_NOT_FOUND)
	{
		x = DECLINED_STOLEN_CARD;
	}
	else if (isAmountAvailable(&(transData->terminalData), &(transData->acountDataBase), &(transData->cardHolderData)) == LOW_BALANCE)
	{
		x = DECLINED_INSUFFECIENT_FUND;
	}
	else if (saveTransaction(transData) == SAVING_FAILED)
	{
		x = INTERNAL_SERVER_ERROR;
	}
	else
	{
		for (uint8_t i = 0; i < 255; i++)
		{
			if (strcmp(SSA[i].primaryAccountNumber, transData->cardHolderData.primaryAccountNumber) == 0)
			{
				SSA[i].balance = SSA[i].balance - transData->terminalData.transAmount;
				transData->acountDataBase.balance = SSA[i].balance;
				printf("the new balance is %f \n", transData->acountDataBase.balance);
				break;
			}
			else
				continue;
		}

	}
	return x;
}

EN_serverError_t isValidAccount(ST_cardData_t* cardData)
{
	EN_serverError_t  x = ACCOUNT_NOT_FOUND;
	for(uint8_t i=0;i<255;i++)
	{
		if (strcmp(SSA_stolen[i].primaryAccountNumber, cardData->primaryAccountNumber) == 0)
		{
			break;
		}

		if(strcmp(SSA[i].primaryAccountNumber,cardData->primaryAccountNumber) ==0)
		{
			x = _OK;
			break;
		}
	}
	return x;
}

EN_serverError_t isAmountAvailable(ST_terminalData_t* termData, ST_accountsDB_t* accountDB, ST_cardData_t* cardData)
{
	EN_serverError_t  x = _OK;
	/*get the balance*/
	for (uint8_t i = 0; i < 255; i++)
	{
		if (strcmp(SSA[i].primaryAccountNumber, cardData->primaryAccountNumber) == 0)
		{
			accountDB->balance = SSA[i].balance;
			printf("the old balance is %f \n", accountDB->balance);
			break;
		}
		else
			continue;
	}
	if (termData->transAmount > accountDB->balance)
	{
			x = LOW_BALANCE;
	}

	return x;
}

	

EN_serverError_t saveTransaction(ST_transaction_t* transData)
{
	EN_serverError_t x = _OK;
	if(seq>255)
	{
		x = SAVING_FAILED;
	}
	strcpy_s(SST[seq].cardHolderData.cardHolderName,sizeof(SST[seq].cardHolderData.cardHolderName), transData->cardHolderData.cardHolderName);
	strcpy_s(SST[seq].cardHolderData.primaryAccountNumber,sizeof(SST[seq].cardHolderData.primaryAccountNumber), transData->cardHolderData.primaryAccountNumber);
	strcpy_s(SST[seq].cardHolderData.cardExpirationDate,sizeof(SST[seq].cardHolderData.cardExpirationDate), transData->cardHolderData.cardExpirationDate);
	SST[seq].terminalData.transAmount = transData->terminalData.transAmount;
	SST[seq].terminalData.maxTransAmount = transData->terminalData.maxTransAmount;
	strcpy_s(SST[seq].terminalData.transactionDate,sizeof(SST[seq].terminalData.transactionDate), transData->terminalData.transactionDate);
	SST[seq].transactionSequenceNumber = seq;
	seq++;
	return x;
}