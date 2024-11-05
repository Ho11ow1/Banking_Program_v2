#include <cstdio>
#include <exception>

#include "banking.h"

void Banking::Run() noexcept 
{
    try 
    {
        acc.Run();

        while (running)
        {
            printf("\n1. Show Card Details\n");
            printf("2. Deposit\n");
            printf("3. Withdraw\n");
            printf("4. Check Balance\n");
            printf("5. Exit\n");
            printf("Choose option: ");

            if (scanf_s("%d", &choice) != 1)
            {
                while (getchar() != '\n');
                printf("Invalid input\n");
                continue;
            }
            while (getchar() != '\n');

            switch (choice)
            {
                case 1: 
                    acc.fn_Show_Card_Details(); 
                break;

                case 2: 
                    printf("Enter amount to deposit: ");
                    if (scanf_s("%lf", &amount) == 1)
                    {
                        acc.Deposit(amount);
                        while (getchar() != '\n');
                    }
                    else
                    {
                        printf("Invalid amount\n");
                        while (getchar() != '\n');
                    }
                break;

                case 3:
                    printf("Enter amount to withdraw: ");
                    if (scanf_s("%lf", &amount) == 1)
                    {
                        acc.Withdraw(amount);
                        while (getchar() != '\n');
                    }
                    else
                    {
                        printf("Invalid amount\n");
                        while (getchar() != '\n');
                    }
                break;

                case 4:
                    acc.Get_Balance();
                break;

                case 5: 
                    printf("Thank you for using this app...\n");
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