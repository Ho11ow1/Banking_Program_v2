#include <cstdio>
#include <sqlite3.h>

#include "./src/banking.h"

int main()
{
    // Test SQLite version
    printf("SQLite version: %s\n", sqlite3_libversion());
    
    // Banking bank;
    // bank.Run();
    return 0;
}