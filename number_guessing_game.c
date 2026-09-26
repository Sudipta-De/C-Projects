#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int secret, guess, choice;
    int attempts, maxAttempts;
    char playAgain;
    srand(time(0));
    printf("===== Number Guessing Game =====\n");
    do {
        printf("\n----- Select Difficulty Level -----\n");
        printf("1. Easy Level\n");
        printf("2. Medium Level\n");
        printf("3. Hard Level\n");
        printf("Choose your Level: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("\nI have chosen a number between 1 to 50.\n");
                printf("You have 10 attempts only.\n");
                secret = rand() % 50 + 1;
                maxAttempts = 10;
                break;
            case 2:
                printf("\nI have chosen a number between 1 to 100.\n");
                printf("You have 7 attempts only.\n");
                secret = rand() % 100 + 1;
                maxAttempts = 7;
                break;
            case 3:
                printf("\nI have chosen a number between 1 to 500.\n");
                printf("You have 5 attempts only.\n");
                secret = rand() % 500 + 1;
                maxAttempts = 5;
                break;
            default:
                printf("Invalid Level!\n");
                continue;
        }
        attempts = 0;
        while (attempts < maxAttempts) {
            printf("\nEnter your Guess: ");
            scanf("%d", &guess);
            attempts++;
            if (guess > secret) {
                printf("Too High! Try Again.\n");
            }
            else if (guess < secret) {
                printf("Too Low! Try Again.\n");
            }
            else {
                printf("\nCongratulations! You guessed the number!\n");
                printf("The number was %d.\n", secret);
                printf("You guessed it in %d attempt(s).\n", attempts);
                break;
            }
            printf("Attempts remaining: %d\n", maxAttempts - attempts);
        }
        if (guess != secret && attempts == maxAttempts) {
            printf("\nGame Over!\n");
            printf("You have used all your attempts.\n");
            printf("The correct number was %d.\n", secret);
        }
        printf("\nDo you want to play again? (y/n): ");
        scanf(" %c", &playAgain);
    }
    while (playAgain == 'y' || playAgain == 'Y');
    printf("\n===== Thanks for Playing! =====\n");
    return 0;
}