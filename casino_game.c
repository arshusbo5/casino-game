#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_ROUNDS 5 
#define REDEEM_CODE "ROYAL2025"
#define MAX_PLAYERS 100
#define MAX_NAME_LENGTH 50

typedef struct {
    char name[MAX_NAME_LENGTH];
    int finalAmount;
    char timestamp[26];
} PlayerRecord;

void playGame(int *money);
void saveToLeaderboard(const char *playerName, int finalAmount);
void displayLeaderboard();
void getCurrentTimestamp(char *timestamp);

int main() {
    char enteredCode[20];
    int money;
    int choice;
    char playerName[MAX_NAME_LENGTH];

    while(1) {
        printf("\n=== Casino Royal Game ===\n");
        printf("1. Play Game\n");
        printf("2. View Leaderboard\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();

        switch(choice) {
            case 1:
                printf("\nEnter your name: ");
                fgets(playerName, MAX_NAME_LENGTH, stdin);
                playerName[strcspn(playerName, "\n")] = 0;

                printf("\n your balance :$0.00\n\n");
                printf("Available redeem code 'ROYAL2025'\n\n");
                printf("Enter the redeem code to start: ");
                scanf("%s", enteredCode);

                if (strcmp(enteredCode, REDEEM_CODE) != 0) {
                    printf("Invalid redeem code! Access denied.\n\n");
                    continue;
                }

                money = 500;
                printf("Redeem code accepted! Welcome to the Casino Game.\n\n");
                printf("You start with $%d.\n", money);

                for (int round = 1; round <= MAX_ROUNDS; round++) {
                    printf("\n--- Round %d ---\n", round);
                    playGame(&money);

                    if (money <= 0) {
                        printf("You're out of money  ! Game Over.\n\n");
                        break;
                    }
                }

                printf("\nGame over! You leave with $%d.\n\n", money);
                saveToLeaderboard(playerName, money);
                break;

            case 2:
                displayLeaderboard();
                break;

            case 3:
                printf("Thanks for playing! Goodbye!\n");
                return 0;

            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
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

void getCurrentTimestamp(char *timestamp) {
    time_t now = time(NULL);
    strftime(timestamp, 26, "%Y-%m-%d %H:%M:%S", localtime(&now));
}

void saveToLeaderboard(const char *playerName, int finalAmount) {
    FILE *file = fopen("data.dat", "ab");
    if (file == NULL) {
        printf("Error saving to leaderboard!\n");
        return;
    }

    PlayerRecord record;
    strncpy(record.name, playerName, MAX_NAME_LENGTH - 1);
    record.name[MAX_NAME_LENGTH - 1] = '\0';
    record.finalAmount = finalAmount;
    getCurrentTimestamp(record.timestamp);

    fwrite(&record, sizeof(PlayerRecord), 1, file);
    fclose(file);
}

void displayLeaderboard() {
    FILE *file = fopen("data.dat", "rb");
    if (file == NULL) {
        printf("No leaderboard data available!\n");
        return;
    }

    PlayerRecord record;
    printf("\n=== Leaderboard ===\n");
    printf("Name\t\tAmount\t\tTimestamp\n");
    printf("----------------------------------------\n");

    while (fread(&record, sizeof(PlayerRecord), 1, file) == 1) {
        printf("%-15s $%-10d %s\n", 
               record.name, 
               record.finalAmount, 
               record.timestamp);
    }

    printf("----------------------------------------\n");
    fclose(file);
}
