#ifndef DATABASE_H
#define DATABASE_H

#include "../sqlite/sqlite3.h"

class Account;
class Card;

class Database
{
public:
    Database() = default;
    ~Database();

    bool OpenDB();
    void CloseDB();

    bool DBExists();
    bool CreateDB();

    bool SaveAccount(Account& account);
    bool SaveCard(Card& card);

private:
    bool EnsureConnected();
    bool PrepareStatements();

    sqlite3* db = nullptr;
    bool connected = false;
    sqlite3_stmt* accountStmt = nullptr;
    sqlite3_stmt* cardStmt = nullptr;
};

#endif