#include <exception>
#include <fstream>

#include "./database.h"

bool Database::DBExists()
{
    // Check if file exists first
    std::ifstream file(Constants::DB_NAME);
    if (!file.good()) 
    {
        return false;
    }
    
    // If file exists, verify it's a valid SQLite database
    if (sqlite3_open_v2(Constants::DB_NAME, &db, SQLITE_OPEN_READONLY, nullptr) != SQLITE_OK)
    {
        return false;
    }

    sqlite3_close(db);
    return true;
}

bool Database::CreateDB()
{
    if (sqlite3_open(Constants::DB_NAME, &db) != SQLITE_OK)
    {
        printf("Error creating database: %s\n", sqlite3_errmsg(db));
        return false;
    }

    char* errMsg = nullptr;
    bool success = true;

    // Create Account table
    const char* accountSQL = 
        "CREATE TABLE IF NOT EXISTS Account ("
        "account_holder TEXT NOT NULL,"
        "account_number BIGINT PRIMARY KEY,"
        "routing_number BIGINT NOT NULL,"
        "balance REAL NOT NULL);";

    if (sqlite3_exec(db, accountSQL, nullptr, nullptr, &errMsg) != SQLITE_OK)
    {
        printf("Error creating Account table: %s\n", errMsg);
        sqlite3_free(errMsg);
        success = false;
    }

    // Create Card table
    const char* cardSQL = 
        "CREATE TABLE IF NOT EXISTS Card ("
        "card_number BIGINT PRIMARY KEY,"
        "PIN INTEGER NOT NULL,"
        "SCV INTEGER NOT NULL,"
        "balance REAL NOT NULL,"
        "account_number BIGINT,"
        "FOREIGN KEY (account_number) REFERENCES Account(account_number));";

    if (sqlite3_exec(db, cardSQL, nullptr, nullptr, &errMsg) != SQLITE_OK)
    {
        printf("Error creating Card table: %s\n", errMsg);
        sqlite3_free(errMsg);
        success = false;
    }

    sqlite3_close(db);
    return success;
}

bool Database::SaveAccount(Account& account)
{
    if (sqlite3_open(Constants::DB_NAME, &db) != SQLITE_OK)
    {
        printf("Error opening database: %s\n", sqlite3_errmsg(db));
        return false;
    }

    const char* sql = 
        "INSERT INTO Account (account_holder, account_number, routing_number, balance) VALUES (?, ?, ?, ?);";
    
    sqlite3_stmt* stmt;
    bool success = false;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK)
    {
        std::string holder = account.GetaccountHolder();
        sqlite3_bind_text(stmt, 1, holder.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_int64(stmt, 2, account.GetAccoutNumber());
        sqlite3_bind_int64(stmt, 3, account.GetAccoutRoutingNumber());
        sqlite3_bind_double(stmt, 4, account.GetAccountBalance());

        success = (sqlite3_step(stmt) == SQLITE_DONE);
        if (!success) 
        {
            printf("Error inserting account: %s\n", sqlite3_errmsg(db));
        }
        
        sqlite3_finalize(stmt);
    }

    sqlite3_close(db);
    return success;
}

bool Database::SaveCard(Card& card)
{
    if (sqlite3_open(Constants::DB_NAME, &db) != SQLITE_OK)
    {
        printf("Error opening database: %s\n", sqlite3_errmsg(db));
        return false;
    }

    const char* sql = 
        "INSERT INTO Card (card_number, PIN, SCV, balance, account_number) VALUES (?, ?, ?, ?, ?);";
    
    sqlite3_stmt* stmt;
    bool success = false;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK)
    {
        sqlite3_bind_int64(stmt, 1, card.GetCardNumber());
        sqlite3_bind_int64(stmt, 2, card.GetPIN());
        sqlite3_bind_int64(stmt, 3, card.GetSCV());
        sqlite3_bind_double(stmt, 4, card.GetBalance());
        sqlite3_bind_int64(stmt, 5, card.GetAccountNumber());

        success = (sqlite3_step(stmt) == SQLITE_DONE);
        if (!success) 
        {
            printf("Error inserting card: %s\n", sqlite3_errmsg(db));
        }

        sqlite3_finalize(stmt);
    }

    sqlite3_close(db);
    return success;
}

