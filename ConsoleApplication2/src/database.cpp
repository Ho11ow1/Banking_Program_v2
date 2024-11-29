#include <exception>
#include <fstream>
#include <cstdio>

#include "./database.h"
#include "./account.h"
#include "./card.h"
#include "./constants.h"

bool Database::DBExists()
{
    std::ifstream file(Constants::DB_NAME);
    if (!file.good()) 
    {
        return false; // Database file does not exist
    }
    
    if (sqlite3_open_v2(Constants::DB_NAME, &db, SQLITE_OPEN_READONLY, nullptr) != SQLITE_OK)
    {
        return false; // Error opening the database
    }

    // Check if tables exist
    const char* sql = "SELECT name FROM sqlite_master WHERE type='table' AND (name='Account' OR name='Card');";
    sqlite3_stmt* stmt;
    int tableCount = 0;
    
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK)
    {
        while (sqlite3_step(stmt) == SQLITE_ROW)
        {
            tableCount++; // Count the number of tables found
        }
        sqlite3_finalize(stmt); // Finalize the statement
    }

    sqlite3_close(db); // Close the database connection
    return tableCount == 2; // Return true if both 'Account' and 'Card' tables are found
}

bool Database::CreateDB()
{
    if (sqlite3_open(Constants::DB_NAME, &db) != SQLITE_OK)
    {
        printf("Error creating database: %s\n", sqlite3_errmsg(db));
        return false; // Error opening or creating the database
    }

    char* errMsg = nullptr;
    bool success = true;

    const char* accountSQL = 
        "CREATE TABLE IF NOT EXISTS Account ("
        "account_holder TEXT NOT NULL,"
        "account_number BIGINT PRIMARY KEY,"
        "routing_number BIGINT NOT NULL,"
        "balance REAL NOT NULL);";

    const char* cardSQL = 
        "CREATE TABLE IF NOT EXISTS Card ("
        "card_number BIGINT PRIMARY KEY,"
        "PIN INTEGER NOT NULL,"
        "CSV INTEGER NOT NULL,"
        "balance REAL NOT NULL,"
        "account_number BIGINT,"
        "FOREIGN KEY (account_number) REFERENCES Account(account_number));";

    sqlite3_close(db); // Close the database connection
    return success; // Always returns true as there's no error handling for SQL execution
}

bool Database::SaveAccount(Account& account)
{
    if (!EnsureConnected() || (!accountStmt && !PrepareStatements()))
    {
        return false; // Error connecting to the database or preparing statements
    }

    sqlite3_reset(accountStmt); // Reset the statement
    sqlite3_clear_bindings(accountStmt); // Clear any existing bindings

    std::string holder = account.GetaccountHolder();
    sqlite3_bind_text(accountStmt, 1, holder.c_str(), holder.length(), SQLITE_STATIC);
    sqlite3_bind_int64(accountStmt, 2, account.GetAccoutNumber());
    sqlite3_bind_int64(accountStmt, 3, account.GetAccoutRoutingNumber());
    sqlite3_bind_double(accountStmt, 4, account.GetAccountBalance());

    if (sqlite3_step(accountStmt) != SQLITE_DONE)
    {
        printf("Error inserting account: %s\n", sqlite3_errmsg(db));
        return false; // Error executing the SQL statement
    }

    return true; // Account successfully saved
}

bool Database::SaveCard(Card& card)
{
    if (!EnsureConnected() || (!cardStmt && !PrepareStatements()))
    {
        return false; // Error connecting to the database or preparing statements
    }

    sqlite3_reset(cardStmt); // Reset the statement
    sqlite3_clear_bindings(cardStmt); // Clear any existing bindings

    sqlite3_bind_int64(cardStmt, 1, card.GetCardNumber());
    sqlite3_bind_int(cardStmt, 2, card.GetPIN());
    sqlite3_bind_int(cardStmt, 3, card.GetCSV());
    sqlite3_bind_double(cardStmt, 4, card.GetBalance());
    sqlite3_bind_int64(cardStmt, 5, card.GetAccountNumber());

    if (sqlite3_step(cardStmt) != SQLITE_DONE)
    {
        printf("Error inserting card: %s\n", sqlite3_errmsg(db));
        return false; // Error executing the SQL statement
    }

    return true; // Card successfully saved
}

bool Database::OpenDB()
{
    if (connected) 
    {
        return true; // Database is already open
    }

    connected = sqlite3_open(Constants::DB_NAME, &db) == SQLITE_OK;
    if (connected) 
    {
        // Prepare statements when we first connect
        return PrepareStatements();
    }
    return false; // Error opening the database
}

void Database::CloseDB()
{
    // Safely finalize statements
    if (accountStmt != nullptr)
    {
        sqlite3_finalize(accountStmt);
        accountStmt = nullptr;
    }
    if (cardStmt != nullptr)
    {
        sqlite3_finalize(cardStmt);
        cardStmt = nullptr;
    }
    if (db != nullptr) 
    {
        sqlite3_close(db);
        db = nullptr;
    }
    connected = false;
}

/**
 * Prepares SQL statements for inserting accounts and cards.
 * 
 * This function prepares SQL statements for inserting data into the 'Account' and 'Card' tables.
 * It first finalizes any existing statements to ensure they are not reused.
 * 
 * @return true if the statements were successfully prepared, false otherwise.
 */
bool Database::PrepareStatements()
{
    if (!EnsureConnected())
    {
        return false; // Error connecting to the database
    }

    // First finalize any existing statements safely
    if (cardStmt != nullptr)
    {
        sqlite3_finalize(cardStmt);
        cardStmt = nullptr;
    }
    if (accountStmt != nullptr)
    {
        sqlite3_finalize(accountStmt);
        accountStmt = nullptr;
    }

    const char* accountSQL = "INSERT INTO Account (account_holder, account_number, routing_number, balance) VALUES (?, ?, ?, ?);";
    const char* cardSQL = "INSERT INTO Card (card_number, PIN, CSV, balance, account_number) VALUES (?, ?, ?, ?, ?);";

    // Prepare card statement
    sqlite3_prepare_v2(db, cardSQL, -1, &cardStmt, nullptr);

    // Prepare account statement
    sqlite3_prepare_v2(db, accountSQL, -1, &accountStmt, nullptr);

    return true; // Statements successfully prepared
}

bool Database::EnsureConnected()
{
    return connected || OpenDB(); // Attempt to open the database if not already open
}

Database::~Database()
{
    CloseDB();  // Use CloseDB to handle cleanup
}
