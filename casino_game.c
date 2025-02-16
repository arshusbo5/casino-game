#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_ROUNDS 5 
#define REDEEM_CODE "ROYAL500"

void playGame(int *money);

int main() {
    char enteredCode[20];
    int money ; 


    printf("\n\nyour balance :$0.00\n\n\n");
    
    printf("Available radeem code 'ROYAL500'\n\n\n");
    printf("Enter the redeem code to start: ");
    scanf("%s", enteredCode);


    if (strcmp(enteredCode, REDEEM_CODE) != 0) {
        printf("Invalid redeem code! Access denied.\n\n\n");
        return 0;
    }

    printf("Redeem code accepted! Welcome to the Casino Game.\n\n\n");
    money=500;
    printf("You start with $%d.\n", money);
    

    
    for (int round = 1; round <= MAX_ROUNDS; round++) {
        printf("\n--- Round %d ---\n", round);
        playGame(&money);

        if (money <= 0) {
            printf("You're out of money! Game Over.\n\n");
            break;
        }
    }

    printf("\nGame over! You leave with $%d.\n\n\n", money);
    return 0;
}

void playGame(int *money) {
    int betAmount, chosenNumber, winningNumber;

    printf("\nYou have $%d. Enter your bet amount: ", *money);
    scanf("%d", &betAmount);

    if (betAmount > *money || betAmount <= 0) {
        printf("Invalid bet amount! Try again.\n");
        return;
    }

    printf("Choose a number between 1 and 10: ");
    scanf("%d", &chosenNumber);

    if (chosenNumber < 1 || chosenNumber > 10) {
        printf("Invalid choice! Pick a number between 1 and 10.\n");
        return;
    }

    srand(time(0));
    winningNumber = (rand() % 10) + 1;

    printf("The winning number is: %d\n", winningNumber);

    if (chosenNumber == winningNumber) {
        printf("Congratulations! You won $%d!\n", betAmount * 2);
        *money += betAmount;
    } else {
        printf("You lost $%d! Better luck next time.\n", betAmount);
        *money -= betAmount;
    }
}
