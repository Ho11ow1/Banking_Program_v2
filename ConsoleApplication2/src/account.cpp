#include <cstdio>

#include "./account.h"
#include "./database.h"
#include "./util/validation.h"
#include "./util/generation.h"
Validation validation;
static Database db;

bool Account::Register()
{
    try
    {
        
        accountHolder = validation.GetValidInput("Input Account Name + Surname");
        accountNumber = GenerateNumber(); // leave as a creative decision
        routingNumber = GenerateNumber(); // leave as a creative decision
        accountBalance = 0;

        db.SaveAccount(*this);

        card.SetBalance(accountBalance);
        card.SetDetails(accountNumber);

        return true;
    }
    catch (std::exception& e)
    {
        printf("%s", e.what());
        return false;
    }

    return true;
}

bool Account::Login()
{
    uint_fast64_t tempAccountNumber{};
    std::string tempAccountHolder{};
    uint_fast64_t tempAccountRouting{};

    printf("Input AccountNumber: ");
    tempAccountNumber = validation.GetValid64("Input Account Number");
    printf("Input AccountHolder: ");
    tempAccountHolder = validation.GetValidInput("Input Account Holder");
    printf("Input Account RoutingNumber: ");
    tempAccountRouting = validation.GetValid64("Input Account RoutingNumber");

    db.OpenDB();

    const char* sql = "SELECT a.account_holder, a.account_number, a.routing_number, a.balance, "
                     "c.card_number, c.PIN, c.CSV, c.balance as card_balance "
                     "FROM Account a "
                     "LEFT JOIN Card c ON a.account_number = c.account_number "
                     "WHERE a.account_number = ? AND a.account_holder = ? AND a.routing_number = ?;";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db.GetDB(), sql, -1, &stmt, nullptr) != SQLITE_OK)
    {
        printf("Error preparing statement: %s\n", sqlite3_errmsg(db.GetDB()));
        return false;
    }

    sqlite3_bind_int64(stmt, 1, tempAccountNumber);
    sqlite3_bind_text(stmt, 2, tempAccountHolder.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int64(stmt, 3, tempAccountRouting);

    bool success = false;
    if (sqlite3_step(stmt) == SQLITE_ROW)
    {
        accountHolder = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        accountNumber = sqlite3_column_int64(stmt, 1);
        routingNumber = sqlite3_column_int64(stmt, 2);
        accountBalance = sqlite3_column_double(stmt, 3);

        if (sqlite3_column_type(stmt, 4) != SQLITE_NULL)
        {
            card.SetCardNumber(sqlite3_column_int64(stmt, 4));
            card.SetPIN((uint16_t)(sqlite3_column_int(stmt, 5)));
            card.SetCSV((uint16_t)(sqlite3_column_int(stmt, 6)));
            card.SetBalance(sqlite3_column_double(stmt, 7));
        }
        
        success = true;
    }

    sqlite3_finalize(stmt);
    return success;
}

void Account::ShowDetails() noexcept
{
    printf("Account Holder: %s", accountHolder.c_str());
    printf("Account Number: %lld\n", accountNumber);
    printf("Routing Number: %lld\n", routingNumber);
    printf("Account Balance: $%.2f\n", accountBalance);
    
    if (&card != nullptr)
    {
        printf("Card Details:\n");
        printf("  Card Number: %lld\n", card.GetCardNumber());
        printf("  PIN: %hu\n", card.GetPIN());
        printf("  CSV: %u\n", card.GetCSV());
        printf("  Balance: $%.2f\n", card.GetBalance());
    }
}

void Account::ManageBalance() noexcept // Turn this into a helper function to handle both withdraw and deposit
{
    uint_fast8_t choice{};

    printf("Option 1. Deposit\n");
    printf("Option 2. Withdraw\n");
    printf("Option 3. Go back\n");
    printf("Input your choice: ");
    if (scanf_s("%hhu", &choice) != 1)
    {
        printf("Invalid input\n");
        while (getchar() != '\n');
        return;
    }
    while (getchar() != '\n');

    switch (choice)
    {
        case 1:
            HandleBalance(true);  // Deposit
            break;
        case 2:
            HandleBalance(false); // Withdraw
            break;
        case 3:
            return;
            break;
        default:
            printf("Invalid input\n\n");
            break;
    }
}

void Account::HandleBalance(bool Deposit) noexcept
{
    double temp{};

    printf("Input Amount to %s: ", Deposit ? "Deposit" : "Withdraw"); // Questionable to use ternary but it's fine
    if (scanf_s("%lf", &temp) != 1)
    {
        printf("Invalid input\n");
        while (getchar() != '\n');
        return;
    }
    while (getchar() != '\n');

    if (temp <= 0)
    {
        printf("Amount must be greater than 0\n");
        return;
    }
    // Also very questionable but it's fine
    UpdateBalance(Deposit ? temp : -temp);
    card.UpdateBalance(Deposit ? temp : -temp);
}

void Account::UpdateBalance(double amount)
{
    // For withdrawals (negative amounts), check if sufficient funds exist
    if (amount < 0 && std::abs(amount) > accountBalance)
    {
        printf("Insufficient funds. Current balance: $%.2f\n", accountBalance);
        return;
    }

    accountBalance += amount;

    printf("Transaction successful. New balance: $%.2f\n", accountBalance);
}

std::string Account::GetaccountHolder() const
{
    return accountHolder;
}

uint_fast64_t Account::GetAccoutNumber() const
{
    return accountNumber;
}

uint_fast64_t Account::GetAccoutRoutingNumber() const
{
    return routingNumber;
}

double Account::GetAccountBalance() const
{
    return accountBalance;
}

void Account::GetBalance() const
{
    printf("Account Balance: %.2lf", accountBalance);
}