
#include <fstream>
#include "./database.h"

bool Database::DBExists()
{
    if (sqlite3_open(Constants::DB_NAME, &db) != SQLITE_OK)
    {
        sqlite3_close(db);
        return false;
    }

    sqlite3_close(db);
    return true;
}

 bool Database::CreateDB()
 {
     std::ofstream file(Constants::DB_NAME);
     if (!file.is_open())
     {
         printf("Error creating database\n");
         return false;
     }

     file.close();
     return true;
 }