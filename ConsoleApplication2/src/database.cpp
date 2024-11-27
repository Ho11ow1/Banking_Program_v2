
#include <fstream>
#include "./database.h"

bool Database::DBExists()
{
    std::ifstream file(Constants::DB_NAME);
    return file.good();;
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