#include "card.h"


EN_cardError_t getCardHolderName(ST_cardData_t* cardData) {
    EN_cardError_t ThisFunction_ErrorState = CARD_OK;

    uint8_t CardHolderName[25] = { 0 };

    printf("\nEnter the card holder name: ");
    gets(CardHolderName);

    uint8_t NameLength = strlen(CardHolderName);

    if ((NULL == CardHolderName) || (NameLength < 20) || (NameLength > 24)) {
        ThisFunction_ErrorState = WRONG_NAME;
        strcpy(cardData->cardHolderName, CardHolderName);
        //printf("wrong name length.");
    }
    else {
        for (int i = 0; i < NameLength; i++) {
            if (' ' == CardHolderName[i] || (CardHolderName[i] >= 65 && CardHolderName[i] <= 90) || (CardHolderName[i] >= 97 && CardHolderName[i] <= 122)) {
                strcpy(cardData->cardHolderName, CardHolderName);
            }
            else {
                ThisFunction_ErrorState = WRONG_NAME;
                strcpy(cardData->cardHolderName, CardHolderName);
                //printf("wrong name formate.");
                break;
            }
        }
    }
    return ThisFunction_ErrorState;
}

/*----------------------------------------------------------------------------------*/

EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData) {
    EN_cardError_t ThisFunction_ErrorState = CARD_OK;

    uint8_t cardExpirationDate[6] = { 0 };

    printf("\nEnter the card expiration date (MM/YY): ");
    gets(cardExpirationDate);

    uint8_t DateLength = strlen(cardExpirationDate);

    if ((NULL == cardExpirationDate) || (DateLength != 5) || (cardExpirationDate[2] != '/')) {
        ThisFunction_ErrorState = WRONG_EXP_DATE;
        strcpy(cardData->cardExpirationDate, cardExpirationDate);
        //printf("wrong date formate.");
    }
    else {
        for (int i = 0; i < DateLength; i++) {
            if (((cardExpirationDate[0] == 0 && (cardExpirationDate[1] >= 1 && cardExpirationDate[1] <= 9))
                || ((cardExpirationDate[0] == 1) && (cardExpirationDate[1] >= 0 && cardExpirationDate[1] <= 2))) &&
                ((cardExpirationDate[3] >= 0 && cardExpirationDate[3] <= 9) && (cardExpirationDate[4] >= 0 && cardExpirationDate[4] <= 9)) &&
                cardExpirationDate[2] == '/') {
                strcpy(cardData->cardExpirationDate, cardExpirationDate);
            }
            else {
                ThisFunction_ErrorState = WRONG_EXP_DATE;
                strcpy(cardData->cardExpirationDate, cardExpirationDate);
                //printf("wrong date data.");
            }
        }
    }

    return ThisFunction_ErrorState;
}

/*----------------------------------------------------------------------------------*/

EN_cardError_t getCardPAN(ST_cardData_t* cardData) {
    EN_cardError_t ThisFunction_ErrorState = CARD_OK;

    uint8_t cardPAN[20] = { 0 };

    printf("\nEnter the card primary account number: ");
    gets(cardPAN);

    uint8_t PANLength = strlen(cardPAN);

    if ((NULL == cardPAN) || (PANLength < 16) || (PANLength > 19)) {
        ThisFunction_ErrorState = WRONG_PAN;
        strcpy(cardData->primaryAccountNumber, cardPAN);
        //printf("wrong PAN length.");
    }
    else if (PANLength == 16) {
        for (int i = 0; i < PANLength; i++) {
            if (cardPAN[PANLength] >= 0 && cardPAN[PANLength] <= 9) {
                strcpy(cardData->primaryAccountNumber, cardPAN);
            }
            else {
                ThisFunction_ErrorState = WRONG_PAN;
                strcpy(cardData->primaryAccountNumber, cardPAN);
                //printf("wrong PAN formate.");
            }
        }
    }
    else if (PANLength == 19) {
        for (int i = 0; i < PANLength; i++) {
            if (cardPAN[PANLength] >= 0 && cardPAN[PANLength] <= 9) {

                if (cardPAN[4] == ' ' && cardPAN[9] == ' ' && cardPAN[14] == ' ') {
                    strcpy(cardData->primaryAccountNumber, cardPAN);
                }
                else {
                    ThisFunction_ErrorState = WRONG_PAN;
                    strcpy(cardData->primaryAccountNumber, cardPAN);
                }

            }
            else {
                ThisFunction_ErrorState = WRONG_PAN;
                strcpy(cardData->primaryAccountNumber, cardPAN);
                //printf("wrong PAN formate.");
            }
        }

    }
    else {
        ThisFunction_ErrorState = WRONG_PAN;
        strcpy(cardData->primaryAccountNumber, cardPAN);
    }

    return ThisFunction_ErrorState;
}

/*----------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------*/

void testGetCardHolderName(void) {

    printf("\nTester Name: Ahmed Seddik\n");
    printf("Function Name: getCardHolderName\n");
    ST_cardData_t testCardHolderName;

    enum EN_cardError_t cardStatus = getCardHolderName(&testCardHolderName);
    printf("Input Data: ");
    printf("%s\n", testCardHolderName.cardHolderName);

    // Test Case 1: Happy Case Scenario with a name in range of 20 to 24 characters
    printf("\nTest Case 1:\n");

    if (cardStatus == CARD_OK) {

        printf("Expected Result: CARD_OK");
        printf("\nActual Result: CARD_OK\n");

    }
    else {

        printf("Expected Result: CARD_OK");
        printf("\nActual Result: WRONG_NAME\n");
    }

    // Test Case 2: Invalid Name length (less than 20 characters or more than 24 characters) or formate (use values other than English alphabets)
    printf("\nTest Case 2:\n");

    if (cardStatus == WRONG_NAME) {

        printf("Expected Result: WRONG_NAME");
        printf("\nActual Result: WRONG_NAME\n");

    }
    else {

        printf("Expected Result: WRONG_NAME");
        printf("\nActual Result: CARD_OK\n");

    }
}

/*----------------------------------------------------------------------------------*/

void testGetCardExpiryDate(void)
{
    printf("\nTester Name: Ahmed Seddik\n");
    printf("Function Name: getCardExpiryDate\n");

    ST_cardData_t testCardExpiryDate;

    enum EN_cardError_t cardStatus = getCardExpiryDate(&testCardExpiryDate);
    printf("Input Data: ");
    printf("%s\n", testCardExpiryDate.cardExpirationDate);

    // Test Case 1: Happy Case Scenario with right date formate (length and data type)
    printf("\nTest Case 1:\n");

    if (cardStatus == CARD_OK) {

        printf("Expected Result: CARD_OK");
        printf("\nActual Result: CARD_OK\n");

    }
    else {
        printf("Expected Result: CARD_OK");
        printf("\nActual Result: WRONG_EXP_DATE\n");
    }

    // Test Case 2: Invalid Date Format
    printf("\nTest Case 2:\n");

    if (cardStatus == WRONG_EXP_DATE) {

        printf("Expected Result: WRONG_EXP_DATE");
        printf("\nActual Result: WRONG_EXP_DATE\n");

    }
    else {

        printf("Expected Result: WRONG_EXP_DATE");
        printf("\nActual Result: CARD_OK\n");

    }
}

/*----------------------------------------------------------------------------------*/

void testGetCardPAN(void)
{
    printf("\nTester Name: Ahmed Seddik\n");
    printf("Function Name: getCardPAN\n");

    ST_cardData_t testCardPAN;

    enum EN_cardError_t cardStatus = getCardPAN(&testCardPAN);
    printf("Input Data: ");
    printf("%s\n", testCardPAN.primaryAccountNumber);

    // Test Case 1: Happy Case Scenario with proper length and data type
    printf("\nTest Case 1:\n");

    if (cardStatus == CARD_OK) {

        printf("Expected Result: CARD_OK");
        printf("\nActual Result: CARD_OK\n");

    }
    else {

        printf("Expected Result: CARD_OK");
        printf("\nActual Result: WRONG_PAN\n");

    }

    // Test Case 2: Invalid PAN (less than 16 digits)
    printf("\nTest Case 2:\n");

    if (cardStatus == WRONG_PAN) {

        printf("Expected Result: WRONG_PAN");
        printf("\nActual Result: WRONG_PAN\n");

    }
    else {

        printf("Expected Result: WRONG_PAN");
        printf("\nActual Result: CARD_OK\n");

    }
}
