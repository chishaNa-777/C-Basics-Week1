#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DB_FILE "bank_database.db"
#define TX_FILE "transactions.db"

#define MAX_NAME 50
#define MAX_PASS 20

struct Account {
    char name[MAX_NAME];
    int accountNumber;
    char password [MAX_PASS];
    float balance;
};

// ================= SIMPLE DATABASE SYSTEM =================
// Database Format (bank_database.db):
// [Record][Record][Record]...
// Each Record = struct Account (binary)

// Append Account to DB
void db_addAccount(struct Account a) {
    FILE *fp = fopen(DB_FILE, "ab");
    if (!fp) return;
    fwrite(&a, sizeof(a), 1, fp);
    fclose(fp);
}

// Update Account in DB
void db_updateAccount(struct Account a) {
    FILE *fp = fopen(DB_FILE, "rb+");
    if (!fp) return;

    struct Account temp;

    while (fread(&temp, sizeof(temp), 1, fp)) {
        if (temp.accountNumber == a.accountNumber) {
            fseek(fp, -sizeof(temp), SEEK_CUR);
            fwrite(&a, sizeof(a), 1, fp);
            fclose(fp);
            return;
        }
    }

    fclose(fp);
}

// Get account from DB by account number
int db_getAccount(int acc, struct Account *out) {
    FILE *fp = fopen(DB_FILE, "rb");
    if (!fp) return 0;

    while (fread(out, sizeof(*out), 1, fp)) {
        if (out->accountNumber == acc) {
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);
    return 0;
}

// Append a transaction line into database file
void db_logTransaction(int acc, const char *type, float amount) {
    FILE *fp = fopen(TX_FILE, "a");
    if (!fp) return;

    fprintf(fp, "ACC:%d | %s | %.2f\n", acc, type, amount);
    fclose(fp);
}

// ================= FEATURES =================
void registerAccount() {
    struct Account a;

    printf("Enter full name: ");
    scanf(" %[^\n]", a.name);

    printf("Enter account number: ");
    scanf("%d", &a.accountNumber);

    printf("Create password: ");
    scanf("%sxxxx", a.password);

    printf("Initial deposit: ");
    scanf("%f", &a.balance);

    db_addAccount(a);

    printf("\nAccount successfully registered and saved to database!\n");
}

int login(struct Account *logged) {
    int acc;
    char pass[MAX_PASS];

    printf("Enter account number: ");
    scanf("%d", &acc);

    printf("Enter password: ");
    scanf("%s", pass);

    if (!db_getAccount(acc, logged)) {
        printf("Account not found.\n");
        return 0;
    }

    if (strcmp(pass, logged->password) != 0) {
        printf("Incorrect password.\n");
        return 0;
    }

    return 1;
}

void deposit(struct Account *a) {
    float amount;
    printf("Enter amount to deposit: ");
    scanf("%f", &amount);

    a->balance += amount;
    db_updateAccount(*a);
    db_logTransaction(a->accountNumber, "Deposit", amount);

    printf("Deposit successful! New balance: %.2f\n", a->balance);
}

void withdraw(struct Account *a) {
    float amount;
    printf("Enter amount to withdraw: ");
    scanf("%f", &amount);

    if (amount > a->balance) {
        printf("Insufficient balance.\n");
        return;
    }

    a->balance -= amount;
    db_updateAccount(*a);
    db_logTransaction(a->accountNumber, "Withdraw", amount);

    printf("Withdraw successful! New balance: %.2f\n", a->balance);
}

void viewTransactions(int acc) {
    FILE *fp = fopen(TX_FILE, "r");
    if (!fp) {
        printf("No transactions found.\n");
        return;
    }

    char line[200];
    printf("\n==== TRANSACTION HISTORY ====\n");

    while (fgets(line, sizeof(line), fp)) {
        int fileAcc;
        sscanf(line, "ACC:%d", &fileAcc);

        if (fileAcc == acc)
            printf("%s", line);
    }

    fclose(fp);
}

void menu(struct Account a) {
    int ch;

    do {
        printf("\n===== BANK MENU =====\n");
        printf("1. Deposit\n2. Withdraw\n3. View Account\n4. Transaction History\n5. Logout\n");
        printf("Enter choice: ");
        scanf("%d", &ch);

        switch (ch) {
            case 1: deposit(&a); break;
            case 2: withdraw(&a); break;
            case 3:
                printf("\nName: %s\nAccount: %d\nBalance: %.2f\n",
                       a.name, a.accountNumber, a.balance);
                break;
            case 4: viewTransactions(a.accountNumber); break;
            case 5: printf("Logged out.\n"); break;
            default: printf("Invalid option.\n");
        }

        // Refresh account from DB
        db_getAccount(a.accountNumber, &a);

    } while (ch != 5);
}

// ================= MAIN =================
int main() {
    int ch;
    struct Account user;

    while (1) {
        printf("\n===== MAIN MENU =====\n");
        printf("1. Register\n2. Login\n3. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &ch);

        switch (ch) {
            case 1: registerAccount(); break;
            case 2:
                if (login(&user)) {
                    printf("Login successful!\n");
                    menu(user);
                } else {
                    printf("Login failed.\n");
                }
                break;
            case 3:
                printf("Goodbye!\n");
                exit(0);
            default:
                printf("Invalid choice.\n");
        }
    }
}
