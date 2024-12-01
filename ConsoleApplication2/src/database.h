#ifndef DATABASE_H
#define DATABASE_H

#include "../sqlite/sqlite3.h"
#include <memory>

class Account;
class Card;
// ALL POINTER USE CASES USE .get() FROM std::unique_ptr 
// ALL PREVIOUS NULLPTR USE .reset() FROM std::unique_ptr 
// FOR SAFETY sqlite3* raw_db = nullptr; then transfer ownership to smart pointer with .reset(raw_db) 
// Since sqlite uses raw pointers .get() is used to access instead of just using db->?

// Automatically provided through documentation:
struct SQLiteDBDeleter 
{
    void operator()(sqlite3* db) const {

        if (db) 
        {
            sqlite3_close(db);
        }
    }
};

struct SQLiteStmtDeleter
{
    void operator()(sqlite3_stmt* stmt) const 
    {
        if (stmt) 
        {
            sqlite3_finalize(stmt);
        }
    }
};

class Database
{
public:
    Database() = default;
    ~Database() = default;

    bool DBExists();
    bool CreateDB();

    bool OpenDB();
    sqlite3* GetDB() const { return db.get(); }
    void CloseDB();

    bool SaveAccount(Account& account);
    bool SaveCard(Card& card);

    bool UpdateBalances(uint_fast64_t accountNum, double newBalance);

private:
    bool EnsureConnected();
    bool PrepareStatements();
    bool connected = false;

    std::unique_ptr<sqlite3, SQLiteDBDeleter> db;
    std::unique_ptr<sqlite3_stmt, SQLiteStmtDeleter> accountStmt;
    std::unique_ptr<sqlite3_stmt, SQLiteStmtDeleter> cardStmt;
};

#endif