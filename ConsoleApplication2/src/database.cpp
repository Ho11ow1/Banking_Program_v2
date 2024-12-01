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
        return false;
    }
    
    sqlite3* raw_db = nullptr;
    if (sqlite3_open_v2(Constants::DB_NAME, &raw_db, SQLITE_OPEN_READONLY, nullptr) != SQLITE_OK)
    {
        return false;
    }

    // Check if tables exist
    const char* sql = "SELECT name FROM sqlite_master WHERE type='table' AND (name='Account' OR name='Card');";
    sqlite3_stmt* stmt;
    int tableCount = 0;
    
    if (sqlite3_prepare_v2(db.get(), sql, -1, &stmt, nullptr) == SQLITE_OK)
    {
        while (sqlite3_step(stmt) == SQLITE_ROW)
        {
            tableCount++; // Count the number of tables found
        }
        sqlite3_finalize(stmt); // Finalize the statement
    }

    sqlite3_close(db.get());
    return tableCount == 2; // Return true if both 'Account' and 'Card' tables are found
}

bool Database::CreateDB()
{
    sqlite3* raw_db = nullptr;
    if (sqlite3_open(Constants::DB_NAME, &raw_db) != SQLITE_OK)
    {
        printf("Error creating database: %s\n", sqlite3_errmsg(raw_db));
        return false;
    }
    db.reset(raw_db); // Transfer ownership to smart pointer

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

    // Execute the SQL statements
    if (sqlite3_exec(db.get(), accountSQL, nullptr, nullptr, &errMsg) != SQLITE_OK || sqlite3_exec(db.get(), cardSQL, nullptr, nullptr, &errMsg) != SQLITE_OK)
    {
        printf("Error creating tables: %s\n", errMsg);
        sqlite3_free(errMsg);
        success = false;
    }

    return success;
}

bool Database::SaveAccount(Account& account)
{
    if (!EnsureConnected() || (!accountStmt && !PrepareStatements()))
    {
        return false; // Error connecting to the database or preparing statements
    }

    sqlite3_reset(accountStmt.get()); // Reset the statement
    sqlite3_clear_bindings(accountStmt.get()); // Clear any existing bindings // Shouldn't ever happen

    std::string holder = account.GetaccountHolder();
    sqlite3_bind_text(accountStmt.get(), 1, holder.c_str(), holder.length(), SQLITE_STATIC);
    sqlite3_bind_int64(accountStmt.get(), 2, account.GetAccoutNumber());
    sqlite3_bind_int64(accountStmt.get(), 3, account.GetAccoutRoutingNumber());
    sqlite3_bind_double(accountStmt.get(), 4, account.GetAccountBalance());

    if (sqlite3_step(accountStmt.get()) != SQLITE_DONE)
    {
        printf("Error inserting account: %s\n", sqlite3_errmsg(db.get()));
        return false; // Error executing the SQL statement
    }

    return true;
}

bool Database::SaveCard(Card& card)
{
    if (!EnsureConnected() || (!cardStmt && !PrepareStatements()))
    {
        return false; // Error connecting to the database or preparing statements
    }

    sqlite3_reset(cardStmt.get()); // Reset the statement
    sqlite3_clear_bindings(cardStmt.get()); // Clear any existing bindings // Shouldn't ever happen

    sqlite3_bind_int64(cardStmt.get(), 1, card.GetCardNumber());
    sqlite3_bind_int(cardStmt.get(), 2, card.GetPIN());
    sqlite3_bind_int(cardStmt.get(), 3, card.GetCSV());
    sqlite3_bind_double(cardStmt.get(), 4, card.GetBalance());
    sqlite3_bind_int64(cardStmt.get(), 5, card.GetAccountNumber());

    if (sqlite3_step(cardStmt.get()) != SQLITE_DONE)
    {
        printf("Error inserting card: %s\n", sqlite3_errmsg(db.get()));
        return false; // Error executing the SQL statement
    }

    return true; //
}

bool Database::OpenDB()
{
    if (connected) 
    {
        return true; // Database is already open
    }

    sqlite3* raw_db = nullptr;
    if (sqlite3_open(Constants::DB_NAME, &raw_db) == SQLITE_OK) 
    {
        db.reset(raw_db); // Transfer ownership to smart pointer
        connected = true;
        return PrepareStatements();
    }
    return false; // Error opening the database
}

void Database::CloseDB()
{
    // All unique pointer resets
    accountStmt.reset();
    cardStmt.reset();
    db.reset();
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
        return false;
    }

    // All unique pointer resets
    accountStmt.reset();
    cardStmt.reset();

    const char* accountSQL = "INSERT INTO Account (account_holder, account_number, routing_number, balance) VALUES (?, ?, ?, ?);";
    const char* cardSQL = "INSERT INTO Card (card_number, PIN, CSV, balance, account_number) VALUES (?, ?, ?, ?, ?);";

    sqlite3_stmt* raw_stmt = nullptr;
    
    // Prepare card statement
    if (sqlite3_prepare_v2(db.get(), cardSQL, -1, &raw_stmt, nullptr) == SQLITE_OK)
    {
        cardStmt.reset(raw_stmt);
    }

    // Prepare account statement
    if (sqlite3_prepare_v2(db.get(), accountSQL, -1, &raw_stmt, nullptr) == SQLITE_OK)
    {
        accountStmt.reset(raw_stmt);
    }

    return true; // Statements successfully prepared
}

bool Database::EnsureConnected()
{
    return connected || OpenDB(); // Attempt to open the database if not already open
}

bool Database::UpdateBalances(uint_fast64_t accountNum, double newBalance)
{
    OpenDB();
    
    // First update Account table
    const char* sql1 = "UPDATE Account SET balance = ? WHERE account_number = ?;";
    sqlite3_stmt* stmt1;
    
    if (sqlite3_prepare_v2(db.get(), sql1, -1, &stmt1, nullptr) != SQLITE_OK) 
    {
        printf("Error preparing Account statement: %s\n", sqlite3_errmsg(db.get()));
        return false;
    }

    sqlite3_bind_double(stmt1, 1, newBalance);
    sqlite3_bind_int64(stmt1, 2, accountNum);
    
    bool success1 = sqlite3_step(stmt1) == SQLITE_DONE;
    sqlite3_finalize(stmt1);

    // Then update Card table
    const char* sql2 = "UPDATE Card SET balance = ? WHERE account_number = ?;";
    sqlite3_stmt* stmt2;
    
    if (sqlite3_prepare_v2(db.get(), sql2, -1, &stmt2, nullptr) != SQLITE_OK)
    {
        printf("Error preparing Card statement: %s\n", sqlite3_errmsg(db.get()));
        return false;
    }

    sqlite3_bind_double(stmt2, 1, newBalance);
    sqlite3_bind_int64(stmt2, 2, accountNum);
    
    bool success2 = sqlite3_step(stmt2) == SQLITE_DONE;
    sqlite3_finalize(stmt2);

    return success1 && success2;
}