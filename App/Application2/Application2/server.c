#include "server.h"
#include <stddef.h>
#include <string.h>
#include <stdio.h>

ST_accountsDB_t accountsDB[10] = {
    {2000.0, RUNNING, "8989374615436851"},
    {100000.0, BLOCKED, "5807007076043875"},
    {2000.0, RUNNING, "8989374615436851"},
    {100000.0, BLOCKED, "5807007076043875"},
    {5000.0, RUNNING, "1234567890123456"},
    {75000.0, RUNNING, "9876543210987654"},
    {3000.0, BLOCKED, "2468135793579513"},
    {15000.0, RUNNING, "1111222233334444"},
    {20000.0, RUNNING, "7777888899990000"},
    {90000.0, BLOCKED, "3333444455556666"}
};

static ST_transaction_t transactionsDB[255] = { 0 };
static uint32_t lastTransactionSequenceNumber = 0;

EN_transState_t recieveTransactionData(ST_transaction_t* transData)
{
    if (isValidAccount(&(transData->cardHolderData), accountsDB) == ACCOUNT_NOT_FOUND)
        return FRAUD_CARD;
    else if (isAmountAvailable(&(transData->terminalData), accountsDB) == LOW_BALANCE)
        return DECLINED_INSUFFECIENT_FUND;
    else if (isBlockedAccount(accountsDB) == BLOCKED_ACCOUNT)
        return DECLINED_STOLEN_CARD;
    else if (saveTransaction(transData) == SAVING_FAILED)
        return INTERNAL_SERVER_ERROR;
    else
        return APPROVED;
}

EN_serverError_t isValidAccount(ST_cardData_t* cardData, ST_accountsDB_t* accountRefrence)
{
    if (cardData == NULL)
        return ACCOUNT_NOT_FOUND;

    for (int i = 0; i < 10; i++) {
        if (strcmp((char*)cardData->primaryAccountNumber, (char*)accountsDB[i].primaryAccountNumber) == 0) {
            *accountRefrence = accountsDB[i];
            return SERVER_OK;
        }
    }
    accountRefrence = NULL;
    return ACCOUNT_NOT_FOUND;
}

EN_serverError_t isBlockedAccount(ST_accountsDB_t* accountRefrence)
{
    if (accountRefrence == NULL)
        return ACCOUNT_NOT_FOUND;

    if (accountRefrence->state == BLOCKED)
        return BLOCKED_ACCOUNT;
    else
        return SERVER_OK;
}

EN_serverError_t isAmountAvailable(ST_terminalData_t* termData, ST_accountsDB_t* accountRefrence)
{
    if (termData == NULL || accountRefrence == NULL)
        return INTERNAL_SERVER_ERROR;
    if (termData->transAmount > accountRefrence->balance)
        return LOW_BALANCE;
    else
        return SERVER_OK;
}

EN_serverError_t saveTransaction(ST_transaction_t* transData) {

    if (transData == NULL)
        return SAVING_FAILED;

    if (lastTransactionSequenceNumber >= 255)
        return SAVING_FAILED;

    transData->transactionSequenceNumber = lastTransactionSequenceNumber++;

    transactionsDB[transData->transactionSequenceNumber] = *transData;

    return SERVER_OK;
}

void listSavedTransactions(void)
{
    printf("List of saved transactions:\n");
    for (int i = 0; i < 255; i++) {
        if (transactionsDB[i].transactionSequenceNumber != 0) {
            printf("#########################\n");
            printf("Transaction Sequence Number: %u\n", transactionsDB[i].transactionSequenceNumber);
            printf("Transaction Date: %s\n", transactionsDB[i].terminalData.transactionDate);
            printf("Transaction Amount: %.2f\n", transactionsDB[i].terminalData.transAmount);
            printf("Transaction State: %d\n", transactionsDB[i].transState);
            printf("Terminal Max Amount: %.2f\n", transactionsDB[i].terminalData.maxTransAmount);
            printf("Cardholder Name: %s\n", transactionsDB[i].cardHolderData.cardHolderName);
            printf("PAN: %s\n", transactionsDB[i].cardHolderData.primaryAccountNumber);
            printf("Card Expiration Date: %s\n", transactionsDB[i].cardHolderData.cardExpirationDate);
            printf("#########################\n");
        }
    }
}

void recieveTransactionDataTest(void) {
    printf("Tester Name: Bassant Samir\n");
    printf("Function Name: recieveTransactionData\n");

    //TestCase1: Happy scenario (Approved transaction)
    ST_transaction_t transData1;
    transData1.cardHolderData.cardHolderName = "John Doe";
    transData1.cardHolderData.primaryAccountNumber = "1234567890123456";
    transData1.cardHolderData.cardExpirationDate = "12/25";
    transData1.terminalData.transAmount = 500.0;
    transData1.terminalData.maxTransAmount = 1000.0;
    transData1.terminalData.transactionDate = "04/08/2024";
    EN_transState_t result1 = recieveTransactionData(&transData1);
    printf("Test Case 1:\n Input Data: Valid transaction data\n Expected Result: APPROVED\n Actual Result: %s\n", result1);
}

