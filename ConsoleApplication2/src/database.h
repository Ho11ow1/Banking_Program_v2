#ifndef DATABASE_H
#define DATABASE_H

#include "../sqlite/sqlite3.h"

#include "./constants.h"
#include "./account.h"
#include "./card.h"

class Database
{
public:
    Database() = default;

    bool DBExists();
    bool CreateDB();

    bool SaveAccount(Account& account);
    bool SaveCard(Card& card);

private:
    sqlite3* db = nullptr;
};

#endif