#include "app.h"

void appStart(void) {
    printf("===== Payment Application =====\n");

    // Initialize card data structure
    ST_cardData_t cardData;

    // Get card details
    printf("\n--- Enter Card Details ---\n");
    if (getCardHolderName(&cardData) != CARD_OK) {
        printf("Invalid cardholder name.\n");
        return;
    }
    if (getCardExpiryDate(&cardData) != CARD_OK) {
        printf("Invalid card expiration date.\n");
        return;
    }
    if (getCardPAN(&cardData) != CARD_OK) {
        printf("Invalid card PAN.\n");
        return;
    }

    // Display entered card details
    printf("\n--- Entered Card Details ---\n");
    printf("Card Holder Name: %s\n", cardData.cardHolderName);
    printf("Card Expiry Date: %s\n", cardData.cardExpirationDate);
    printf("Card PAN: %s\n", cardData.primaryAccountNumber);

    // Additional processing or transaction handling can be added here
}