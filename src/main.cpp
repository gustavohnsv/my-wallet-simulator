#include <vector>
#include <cstdio>
#include <cstdlib>
#include <iostream>

#include "Wallet/Wallet.h"
#include "Customer/Customer.h"
#include "WalletHistory/WalletHistory.h"

#define RESET_COLOR "\033[0m"
#define RED_COLOR "\033[1;31m"
#define GREEN_COLOR "\033[1;32m"
#define BLUE_COLOR "\033[1;34m"
#define LIGHTBLUE_COLOR "\033[1;36m"
#define YELLOW_COLOR "\033[1;93m"

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void printHelp() {
    printf(LIGHTBLUE_COLOR);
    std::cout << "Available commands:\n";
    std::cout << "  create      <first-name> <last-name>                                                            - Create a new customer.\n";
    std::cout << "  delete      <first-name> <last-name>                                                            - Delete a customer.\n";
    std::cout << "  history     <first-name> <last-name>                                                            - Show the transaction history of a customer.\n";
    std::cout << "  deposit     <first-name> <last-name> <amount>                                                   - Deposit cash into a customer's wallet.\n";
    std::cout << "  withdraw    <first-name> <last-name> <amount>                                                   - Withdraw cash from a customer's wallet.\n";
    std::cout << "  transfer    <your-first-name> <your-last-name> <target-first-name> <target-last-name> <amount>  - Transfer cash from a customer's wallet to another wallet.\n";
    std::cout << "  exit                                                                                            - Exit the program.\n";
    std::cout << "  help                                                                                            - Show this help message.\n";
    std::cout << "  clear                                                                                           - Clean the terminal screen.\n";
    std::cout << "  list                                                                                            - Show customer list.\n";
    printf(RESET_COLOR);
}

void printCustomers(const std::vector<Customer*> &customerList) {
    if (customerList.empty() != 0) {
        printf(RED_COLOR);
        std::cout << "ERROR: Empty list.\n";
        printf(RESET_COLOR);
        return;
    } for (Customer* customer: customerList) {
        std::cout << "Name: "<< customer->getFirstName() << " " << customer->getLastName() << " Cash: " << customer->getWallet()->getCash() << "\n";
    }
}

Customer* searchCustomer(const std::string &firstName, const std::string &lastName, const std::vector<Customer*> &customerList) {
    if (customerList.empty()) {
        return nullptr;
    }
    for (Customer* customer: customerList) {
        if (customer->getFirstName() == firstName && customer->getLastName() == lastName) {
            return customer;
        }
    }
    return nullptr;
}

int searchCustomerIndex(const std::string &firstName, const std::string &lastName, const std::vector<Customer*> &customerList) {
    if (customerList.empty()) {
        return -1;
    } else {
        int i = 0;
        for (Customer* customer: customerList) {
            if (customer->getFirstName() == firstName && customer->getLastName() == lastName) {
                return i;
            }
            i++;
        }
    }
    return -1;
}

int main() {

    clearScreen();
    printHelp();

    std::vector<Customer*> customerList; // Now customerList is a vector of Customer*, using vector standard library header

    std::string Operation;

    do {
        printf(BLUE_COLOR);
        std::cout << ">>> ";
        printf(RESET_COLOR);
        printf(YELLOW_COLOR);
        std::cin >> Operation;
        printf(RESET_COLOR);
        if (Operation == "create") {
            std::string FirstName;
            std::string LastName;
            std::cin >> FirstName;
            std::cin >> LastName;
            customerList.push_back(new Customer(FirstName, LastName));
            printf(GREEN_COLOR);
            std::cout << "Customer created with success!\n";
            printf(RESET_COLOR);
        } else if (Operation == "delete") {
            std::string FirstName;
            std::string LastName;
            std::cin >> FirstName;
            std::cin >> LastName;
            int tempCustomerIndex = searchCustomerIndex(FirstName, LastName, customerList);
            if (tempCustomerIndex != -1){
                customerList.erase(customerList.begin() + tempCustomerIndex);
                printf(GREEN_COLOR);
                std::cout << "Customer deleted with success!\n";
                printf(RESET_COLOR);
            } else {
                printf(RED_COLOR);
                std::cout << "Customer not found.\n";
                printf(RESET_COLOR);
            }
        } else if (Operation == "history") {
            std::string FirstName;
            std::string LastName;
            std::cin >> FirstName;
            std::cin >> LastName;
            Customer* tempCustomer = searchCustomer(FirstName, LastName, customerList);
            if (tempCustomer != nullptr) {
                if (tempCustomer->getWallet()->getCash() == 0) {
                    printf(RED_COLOR);
                    std::cout << "No balance history." << "\n";
                    printf(RESET_COLOR);
                } else {
                    printf(GREEN_COLOR);
                    std::cout<< "Actual cash: " << tempCustomer->getWallet()->getCash() << "\n";
                    printf(RESET_COLOR);
                }
                tempCustomer->getWallet()->getWalletHistory()->showHistoryData();
            } else {
                printf(RED_COLOR);
                std::cout << "Customer not found.\n";
                printf(RESET_COLOR);
            }
        } else if (Operation == "deposit") {
            std::string FirstName;
            std::string LastName;
            double amount;
            std::cin >> FirstName;
            std::cin >> LastName;
            std::cin >> amount;
            Customer* tempCustomer = searchCustomer(FirstName, LastName, customerList);
            if (tempCustomer != nullptr) {
                tempCustomer->getWallet()->depositCash(amount);
                printf(GREEN_COLOR);
                std::cout<< "Success! Actual cash: " << tempCustomer->getWallet()->getCash() << "\n";
                printf(RESET_COLOR);
            } else {
                printf(RED_COLOR);
                std::cout << "Customer not found.\n";
                printf(RESET_COLOR);
            }
        } else if (Operation == "withdraw") {
            std::string FirstName;
            std::string LastName;
            double amount;
            std::cin >> FirstName;
            std::cin >> LastName;
            std::cin >> amount;
            Customer* tempCustomer = searchCustomer(FirstName, LastName, customerList);
            if (tempCustomer != nullptr) {
                if (tempCustomer->getWallet()->withdrawCash(amount) == 0) {
                    std::cout << "ERROR: no cash available to withdraw actual amount!\n";
                } else {
                    printf(GREEN_COLOR);
                    std::cout<< "Success! Actual cash: " << tempCustomer->getWallet()->getCash() << "\n";
                    printf(RESET_COLOR);
                }
            } else {
                printf(RED_COLOR);
                std::cout << "Customer not found.\n";
                printf(RESET_COLOR);
            }
        } else if (Operation == "transfer") {
            std::string FirstName, LastName;
            std::string TargetFirstName, TargetLastName;
            double amount;
            std::cin >> FirstName;
            std::cin >> LastName;
            std::cin >> TargetFirstName;
            std::cin >> TargetLastName;
            std::cin >> amount;
            Customer* tempCustomer = searchCustomer(FirstName, LastName, customerList);
            Customer* tempTargetCustomer = searchCustomer(TargetFirstName, TargetLastName, customerList);
            if (tempCustomer != nullptr && tempTargetCustomer != nullptr) {
                Wallet* tempTargetWallet = tempTargetCustomer->getWallet();
                if (tempCustomer->getWallet()->transferCash(tempTargetWallet, amount) == 0) {
                    std::cout << "ERROR: no cash available to transfer actual cash!\n";
                } else {
                    printf(GREEN_COLOR);
                    std::cout<< "Success! Actual cash: " << tempCustomer->getWallet()->getCash() << "\n";
                    printf(RESET_COLOR);
                }
            } else {
                printf(RED_COLOR);
                std::cout << "Customer not found.\n";
                printf(RESET_COLOR);
            }
        } else if (Operation == "help") {
            printHelp();
        }   else if (Operation == "list") {
            printCustomers(customerList);
        } else if (Operation == "clear") {
            clearScreen();
        } else if (Operation == "exit") {
            for (Customer* customer: customerList) { // "Garbage collector" of customerList
                delete customer;
            }
            std::cout << "Exiting...\n";
            exit(0);
        } else {
            std::cout << "Unknown command...\n";
        }
    }
    while (Operation != "exit");
    return 0;
}