#ifndef DATABASE_H
#define DATABASE_H

#include <sqlite3.h>

#include "./constants.h"
#include "./account.h"
#include "./card.h"

class Database
{
public:
    Database() = default;

    void SaveAccount(Account &account);
    void SaveCard(Card &card);
    void LoadAccount(Account &account);
    void LoadCard(Card &card);

    bool DBExists();
    bool CreateDB();

private:
    sqlite3 *db;
};

#endif