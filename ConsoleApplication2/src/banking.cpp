#include <cstdio>
#include <exception>

#include "./banking.h"

void Banking::Run() noexcept
{
    if (!DB.DBExists())
    {
        printf("Database doesn't exists, Creating Database");
        try
        {
            DB.CreateDB();
        }
        catch (const std::exception& e)
        {
            printf("%s\n", e.what());
        }
    }
    try
    {
        while (isRunning)
        {
            if (!isLoggedIn)
            {
                printf("Welcome to our Banking app\n");

                printf("Would you like to login or create a new account?\n");
                printf("1. Login\n");
                printf("2. Create Account\n");
                printf("3. Exit Program\n");

                printf("Choose option: ");
                if (scanf_s("%hhd", &choice) != 1)
                {
                    system("cls");
                    printf("Invalid input\n");
                    while (getchar() != '\n');
                    return;
                }
                while (getchar() != '\n');

                switch (choice)
                {
                    case 1:
                        system("cls");
                        if (account.Login()) {isLoggedIn = true;}
                    break;

                    case 2:
                        system("cls");
                        if (account.Register()) {isLoggedIn = true;}
                    break;

                    case 3:
                        printf("Thank you for using our app...\n");
                        isRunning = false;
                    break;

                    default:
                        system("cls");
                        printf("Invalid input\n");
                    continue;
                }
                continue;
            }
            while (isRunning && isLoggedIn)
            {
                printf("\n=== Banking Menu ===\n");
                printf("1. Show Card Details\n");
                printf("2. Deposit\n");
                printf("3. Withdraw\n");
                printf("4. Check Balance\n");
                printf("5. Exit\n");
                printf("==================\n");
                printf("Choose option: ");

                if (scanf_s("%hhd", &choice) != 1)
                {
                    system("cls");
                    printf("Invalid input\n");
                    while (getchar() != '\n');
                    continue;
                }
                while (getchar() != '\n');

                switch (choice)
                {
                    case 1:
                        system("cls");
                        account.ShowDetails(account, card);
                    break;
                    case 2:
                        system("cls");
                        // TODO: Implement Deposit
                    break;
                    case 3:
                        system("cls");
                        // TODO: Implement Withdraw
                    break;
                    case 4:
                        system("cls");
                        // TODO: Implement Check Balance
                    break;
                    case 5:
                        printf("Thank you for using this app...\n");
                        isRunning = false;
                    break;
                    default:
                        printf("Invalid option\n");
                    break;
                }
            }
        }
    }
    catch(const std::exception& e)
    {
        printf("%s\n", e.what());
    }

}