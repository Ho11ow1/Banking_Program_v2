#include <cstdio>
#include <exception>
#include <cstdlib>
#include <cctype>

#include "banking.h"

void Banking::Run() noexcept 
{
    try 
    {
        system("cls");
        printf("Welcome to our banking app\n\n");

        printf("Would you like to login or create a new account?\n");
        printf("1. Login\n");
        printf("2. Create Account\n");
        
        printf("Choose option: ");
        scanf_s("%d", &choice);

        switch (choice)
        {
            case 1:
                system("cls");
                if (acc.fn_Login()) { logged_in = true; }
            break;

            case 2:
                system("cls");
                acc.Run();
                logged_in = true;
            break;

            default:
                system("cls");
                printf("Invalid option\n");
                return;
            break;
        }

        while (running && logged_in)
        {
            printf("\n=== Banking Menu ===\n");
            printf("1. Show Card Details\n");
            printf("2. Deposit\n");
            printf("3. Withdraw\n");
            printf("4. Check Balance\n");
            printf("5. Exit\n");
            printf("==================\n");
            printf("Choose option: ");

            if (scanf_s("%d", &choice) != 1)
            {
                printf("Invalid input\n");
                while (getchar() != '\n');
                continue;
            }
            while (getchar() != '\n');
            system("cls");

            switch (choice)
            {
                case 1: 
                    acc.fn_Show_Card_Details(); 
                break;

                case 2: 
                    fn_Handle_Balance("deposit", [this](double amt) { return acc.Deposit(amt); });
                break;

                case 3:
                    fn_Handle_Balance("withdraw", [this](double amt) { return acc.Withdraw(amt); });
                break;

                case 4:
                    acc.Get_Balance();
                break;

                case 5: 
                    printf("Thank you for using our app...\n");
                    running = false; 
                break;

                default: 
                    printf("Invalid option\n");
                break;
            }
        }
    }
    catch (const std::exception& e) 
    {
        printf("Error: %s\n", e.what());
    }
} 

template<typename Func>
void Banking::fn_Handle_Balance(const char* prompt, Func&& operation) 
{
    printf("Enter amount to %s: ", prompt);

    if (scanf_s("%lf", &amount) == 1) 
    {
        operation(amount);
        while (getchar() != '\n');
    } 
    else 
    {
        printf("Invalid amount\n");
        while (getchar() != '\n');
    }
} 