/*#include <stdio.h>

int main() {

	printf("HelloAalaa");
}
*/


#include "terminal.h"
#include <stdio.h>



EN_terminalError_t getTransactionDate(ST_terminalData_t* termData) {

    printf("Enter transaction date (DD/MM/YYYY): ");
    if (scanf("%10s", termData->transactionDate) != 1) {
        printf("Error reading input\n");
        return INTERNAL_SERVER_ERROR;
    }
    if (strlen(termData->transactionDate) != 10) {
        return WRONG_DATE;
    }
    return TERMINAL_OK;
}

EN_terminalError_t isCardExpired(ST_cardData_t* cardData, ST_terminalData_t* termData) {
    // Extracting MM/YY from the card expiration date
    int cardMonth, cardYear, transMonth, transYear;
    sscanf(cardData->cardExpirationDate, "%d/%d", &cardMonth, &cardYear);
    sscanf(termData->transactionDate, "%d/%d", &transMonth, &transYear);

    // Checking if card is expired
    if (cardYear < transYear || (cardYear == transYear && cardMonth < transMonth)) {
        return EXPIRED_CARD;
    }
    return TERMINAL_OK;
}

EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData) {
    printf("Enter transaction amount: ");
    scanf("%f", &termData->transAmount);
    getchar(); // Consume newline character from input buffer

    if (termData->transAmount <= 0) {
        return INVALID_AMOUNT;
    }
    return TERMINAL_OK;
}

EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData) {
    if (termData->transAmount > termData->maxTransAmount) {
        return EXCEED_MAX_AMOUNT;
    }
    return TERMINAL_OK;
}
EN_terminalError_t setMaxAmount(ST_terminalData_t* termData, float maxAmount) {
    if (maxAmount <= 0) {
        return INVALID_MAX_AMOUNT;
    }
    termData->maxTransAmount = maxAmount;
    return TERMINAL_OK;
}
