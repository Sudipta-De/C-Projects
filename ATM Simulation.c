#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define DATA_FILE "atm_data.dat"
#define MAX_TRANSACTIONS 50

typedef struct {
    char date[30];
    char type[30];
    double amount;
    double balanceAfter;
} Transaction;

typedef struct {
    char accountNumber[20];
    char name[50];
    int pin;
    double balance;
    Transaction transactions[MAX_TRANSACTIONS];
    int transactionCount;
} Account;

/* Function declarations */
void initializeAccount();
int login(Account *account);
void atmMenu(Account *account);

void checkBalance(Account *account);
void depositMoney(Account *account);
void withdrawMoney(Account *account);
void transferMoney(Account *account);
void changePin(Account *account);
void miniStatement(Account *account);

void saveAccount(Account *account);
void addTransaction(Account *account, const char *type, double amount);
void getCurrentDateTime(char *buffer, int size);
void clearInputBuffer();
void pauseScreen();

/* Clear input buffer */
void clearInputBuffer() {
    int c;

    while ((c = getchar()) != '\n' && c != EOF);
}

/* Pause screen */
void pauseScreen() {
    printf("\nPress Enter to continue...");
    getchar();
}

/* Get current date and time */
void getCurrentDateTime(char *buffer, int size) {
    time_t now;
    struct tm *currentTime;

    time(&now);
    currentTime = localtime(&now);

    strftime(buffer, size, "%d-%m-%Y %H:%M:%S", currentTime);
}

/* Add transaction */
void addTransaction(Account *account, const char *type, double amount) {

    if (account->transactionCount >= MAX_TRANSACTIONS) {

        /* Remove the oldest transaction */
        for (int i = 1; i < MAX_TRANSACTIONS; i++) {
            account->transactions[i - 1] =
                account->transactions[i];
        }

        account->transactionCount = MAX_TRANSACTIONS - 1;
    }

    Transaction *transaction =
        &account->transactions[account->transactionCount];

    getCurrentDateTime(transaction->date,
                       sizeof(transaction->date));

    strcpy(transaction->type, type);

    transaction->amount = amount;
    transaction->balanceAfter = account->balance;

    account->transactionCount++;
}

/* Save account */
void saveAccount(Account *account) {

    FILE *file;

    file = fopen(DATA_FILE, "wb");

    if (file == NULL) {
        printf("\nUnable to save account data.\n");
        return;
    }

    fwrite(account, sizeof(Account), 1, file);

    fclose(file);
}

/* Initialize account */
void initializeAccount() {

    FILE *file;
    Account account;

    file = fopen(DATA_FILE, "rb");

    /* Account already exists */
    if (file != NULL) {
        fclose(file);
        return;
    }

    printf("\n========================================\n");
    printf("          ATM FIRST TIME SETUP\n");
    printf("========================================\n");

    strcpy(account.accountNumber, "1002003001");

    strcpy(account.name, "Demo User");

    account.pin = 1234;

    account.balance = 10000.00;

    account.transactionCount = 0;

    saveAccount(&account);

    printf("\nATM account created successfully!\n");
    printf("Demo Account Number: %s\n",
           account.accountNumber);

    printf("Default PIN: 1234\n");

    printf("\nYou can change the PIN after logging in.\n");

    pauseScreen();
}

/* Login */
int login(Account *account) {

    FILE *file;
    int enteredPin;
    int attempts = 0;

    file = fopen(DATA_FILE, "rb");

    if (file == NULL) {
        printf("\nUnable to access ATM account data.\n");
        return 0;
    }

    fread(account, sizeof(Account), 1, file);

    fclose(file);

    while (attempts < 3) {

        printf("\n========================================\n");
        printf("               ATM LOGIN\n");
        printf("========================================\n");

        printf("Account Number: %s\n",
               account->accountNumber);

        printf("Enter PIN: ");
        scanf("%d", &enteredPin);
        clearInputBuffer();

        if (enteredPin == account->pin) {

            printf("\nLogin successful!\n");
            printf("Welcome, %s!\n", account->name);

            pauseScreen();

            return 1;
        }

        attempts++;

        printf("\nIncorrect PIN!\n");
        printf("Attempts remaining: %d\n",
               3 - attempts);
    }

    printf("\nToo many incorrect attempts.\n");
    printf("Access blocked for this session.\n");

    return 0;
}

/* Check balance */
void checkBalance(Account *account) {

    printf("\n========================================\n");
    printf("             ACCOUNT BALANCE\n");
    printf("========================================\n");

    printf("Account Number : %s\n",
           account->accountNumber);

    printf("Account Holder : %s\n",
           account->name);

    printf("----------------------------------------\n");

    printf("Available Balance: %.2f\n",
           account->balance);

    pauseScreen();
}

/* Deposit money */
void depositMoney(Account *account) {

    double amount;

    printf("\n========================================\n");
    printf("              DEPOSIT MONEY\n");
    printf("========================================\n");

    printf("Current Balance: %.2f\n",
           account->balance);

    printf("\nEnter amount to deposit: ");
    scanf("%lf", &amount);
    clearInputBuffer();

    if (amount <= 0) {

        printf("\nInvalid amount!\n");
        pauseScreen();

        return;
    }

    account->balance += amount;

    addTransaction(account,
                   "Deposit",
                   amount);

    saveAccount(account);

    printf("\nDeposit successful!\n");
    printf("Amount Deposited: %.2f\n",
           amount);

    printf("New Balance: %.2f\n",
           account->balance);

    pauseScreen();
}

/* Withdraw money */
void withdrawMoney(Account *account) {

    double amount;

    printf("\n========================================\n");
    printf("             WITHDRAW MONEY\n");
    printf("========================================\n");

    printf("Available Balance: %.2f\n",
           account->balance);

    printf("\nEnter amount to withdraw: ");
    scanf("%lf", &amount);
    clearInputBuffer();

    if (amount <= 0) {

        printf("\nInvalid amount!\n");
        pauseScreen();

        return;
    }

    if (amount > account->balance) {

        printf("\nInsufficient balance!\n");

        pauseScreen();

        return;
    }

    account->balance -= amount;

    addTransaction(account,
                   "Withdrawal",
                   amount);

    saveAccount(account);

    printf("\nWithdrawal successful!\n");

    printf("Amount Withdrawn: %.2f\n",
           amount);

    printf("Remaining Balance: %.2f\n",
           account->balance);

    pauseScreen();
}

/* Transfer money */
void transferMoney(Account *account) {

    char recipient[30];
    double amount;

    printf("\n========================================\n");
    printf("              MONEY TRANSFER\n");
    printf("========================================\n");

    printf("Available Balance: %.2f\n",
           account->balance);

    printf("\nEnter recipient account number: ");

    fgets(recipient,
          sizeof(recipient),
          stdin);

    recipient[strcspn(recipient, "\n")] = '\0';

    if (strlen(recipient) == 0) {

        printf("\nInvalid account number!\n");

        pauseScreen();

        return;
    }

    printf("Enter amount to transfer: ");

    scanf("%lf", &amount);
    clearInputBuffer();

    if (amount <= 0) {

        printf("\nInvalid amount!\n");

        pauseScreen();

        return;
    }

    if (amount > account->balance) {

        printf("\nInsufficient balance!\n");

        pauseScreen();

        return;
    }

    account->balance -= amount;

    addTransaction(account,
                   "Transfer",
                   amount);

    saveAccount(account);

    printf("\nTransfer successful!\n");

    printf("Recipient Account: %s\n",
           recipient);

    printf("Amount Transferred: %.2f\n",
           amount);

    printf("Remaining Balance: %.2f\n",
           account->balance);

    pauseScreen();
}

/* Change PIN */
void changePin(Account *account) {

    int oldPin;
    int newPin;
    int confirmPin;

    printf("\n========================================\n");
    printf("               CHANGE PIN\n");
    printf("========================================\n");

    printf("Enter current PIN: ");
    scanf("%d", &oldPin);
    clearInputBuffer();

    if (oldPin != account->pin) {

        printf("\nIncorrect current PIN!\n");

        pauseScreen();

        return;
    }

    printf("Enter new 4-digit PIN: ");
    scanf("%d", &newPin);
    clearInputBuffer();

    if (newPin < 1000 || newPin > 9999) {

        printf("\nPIN must contain exactly 4 digits!\n");

        pauseScreen();

        return;
    }

    printf("Confirm new PIN: ");
    scanf("%d", &confirmPin);
    clearInputBuffer();

    if (newPin != confirmPin) {

        printf("\nPIN confirmation does not match!\n");

        pauseScreen();

        return;
    }

    if (newPin == oldPin) {

        printf("\nNew PIN must be different from old PIN!\n");

        pauseScreen();

        return;
    }

    account->pin = newPin;

    saveAccount(account);

    printf("\nPIN changed successfully!\n");

    pauseScreen();
}

/* Mini statement */
void miniStatement(Account *account) {

    printf("\n");
    printf("====================================================================\n");
    printf("                         MINI STATEMENT\n");
    printf("====================================================================\n");

    printf("Account Number : %s\n",
           account->accountNumber);

    printf("Account Holder : %s\n",
           account->name);

    printf("--------------------------------------------------------------------\n");

    if (account->transactionCount == 0) {

        printf("\nNo transactions available.\n");

    } else {

        printf("%-22s %-15s %-12s %-15s\n",
               "Date",
               "Type",
               "Amount",
               "Balance");

        printf("--------------------------------------------------------------------\n");

        for (int i = 0;
             i < account->transactionCount;
             i++) {

            printf("%-22s %-15s %-12.2f %-15.2f\n",
                   account->transactions[i].date,
                   account->transactions[i].type,
                   account->transactions[i].amount,
                   account->transactions[i].balanceAfter);
        }
    }

    printf("====================================================================\n");

    printf("\nCurrent Balance: %.2f\n",
           account->balance);

    pauseScreen();
}

/* ATM menu */
void atmMenu(Account *account) {

    int choice;

    while (1) {

        printf("\n\n");
        printf("========================================\n");
        printf("              ATM MAIN MENU\n");
        printf("========================================\n");

        printf("Account: %s\n",
               account->accountNumber);

        printf("----------------------------------------\n");

        printf("1. Check Balance\n");
        printf("2. Deposit Money\n");
        printf("3. Withdraw Money\n");
        printf("4. Transfer Money\n");
        printf("5. Change PIN\n");
        printf("6. Mini Statement\n");
        printf("7. Logout\n");

        printf("----------------------------------------\n");

        printf("Enter your choice: ");

        scanf("%d", &choice);
        clearInputBuffer();

        switch (choice) {

            case 1:
                checkBalance(account);
                break;

            case 2:
                depositMoney(account);
                break;

            case 3:
                withdrawMoney(account);
                break;

            case 4:
                transferMoney(account);
                break;

            case 5:
                changePin(account);
                break;

            case 6:
                miniStatement(account);
                break;

            case 7:

                printf("\nLogging out...\n");
                printf("Thank you for using the ATM!\n");

                return;

            default:

                printf("\nInvalid choice!\n");

                pauseScreen();
        }
    }
}

/* Main function */
int main() {

    Account account;

    printf("\n");
    printf("========================================\n");
    printf("          WELCOME TO ATM SYSTEM\n");
    printf("========================================\n");

    initializeAccount();

    if (login(&account)) {

        atmMenu(&account);
    }

    printf("\nProgram closed.\n");

    return 0;
}