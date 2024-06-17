#include <vector>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <unordered_map>
#include <string>

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
    if (customerList.empty()) {
        printf(RED_COLOR);
        std::cout << "ERROR: Empty list.\n";
        printf(RESET_COLOR);
        return;
    }
    for (Customer* customer : customerList) {
        std::cout << "Name: " << customer->getFirstName() << " " << customer->getLastName() << " Cash: " << customer->getWallet()->getCash() << "\n";
    }
}

Customer* searchCustomer(const std::string &firstName, const std::string &lastName, const std::vector<Customer*> &customerList) {
    for (Customer* customer : customerList) {
        if (customer->getFirstName() == firstName && customer->getLastName() == lastName) {
            return customer;
        }
    }
    return nullptr;
}

int searchCustomerIndex(const std::string &firstName, const std::string &lastName, const std::vector<Customer*> &customerList) {
    for (int i = 0; i < ((int) customerList.size()); ++i) {
        if (customerList[i]->getFirstName() == firstName && customerList[i]->getLastName() == lastName) {
            return i;
        }
    }
    return -1;
}

enum Command {
    CREATE,
    DELETE,
    HISTORY,
    DEPOSIT,
    WITHDRAW,
    TRANSFER,
    HELP,
    CLEAR,
    LIST,
    EXIT,
    UNKNOWN
};

Command getCommand(const std::string& operation) {
    static const std::unordered_map<std::string, Command> commandMap = {
            {"create", CREATE},
            {"delete", DELETE},
            {"history", HISTORY},
            {"deposit", DEPOSIT},
            {"withdraw", WITHDRAW},
            {"transfer", TRANSFER},
            {"help", HELP},
            {"clear", CLEAR},
            {"list", LIST},
            {"exit", EXIT}
    };

    auto it = commandMap.find(operation);
    if (it != commandMap.end()) {
        return it->second;
    }
    return UNKNOWN;
}

int main() {
    clearScreen();
    printHelp();

    std::vector<Customer*> customerList;

    std::string operation;

    do {
        printf(BLUE_COLOR);
        std::cout << ">>> ";
        printf(RESET_COLOR);
        printf(YELLOW_COLOR);
        std::cin >> operation;
        printf(RESET_COLOR);

        Command cmd = getCommand(operation);

        switch (cmd) {
            case CREATE: {
                std::string firstName, lastName;
                std::cin >> firstName >> lastName;
                if (searchCustomer(firstName, lastName, customerList)) {
                    printf(RED_COLOR);
                    std::cout << "Customer name unavailable, try another!\n";
                    printf(RESET_COLOR);
                } else {
                    customerList.push_back(new Customer(firstName, lastName));
                    printf(GREEN_COLOR);
                    std::cout << "Customer created with success!\n";
                    printf(RESET_COLOR);
                }
                break;
            }
            case DELETE: {
                std::string firstName, lastName;
                std::cin >> firstName >> lastName;
                int index = searchCustomerIndex(firstName, lastName, customerList);
                if (index != -1) {
                    delete customerList[index];
                    customerList.erase(customerList.begin() + index);
                    printf(GREEN_COLOR);
                    std::cout << "Customer deleted with success!\n";
                    printf(RESET_COLOR);
                } else {
                    printf(RED_COLOR);
                    std::cout << "Customer not found.\n";
                    printf(RESET_COLOR);
                }
                break;
            }
            case HISTORY: {
                std::string firstName, lastName;
                std::cin >> firstName >> lastName;
                Customer* customer = searchCustomer(firstName, lastName, customerList);
                if (customer) {
                    printf(GREEN_COLOR);
                    std::cout << "Actual cash: " << customer->getWallet()->getCash() << "\n";
                    printf(RESET_COLOR);
                    customer->getWallet()->getWalletHistory()->showHistoryData();
                } else {
                    printf(RED_COLOR);
                    std::cout << "Customer not found.\n";
                    printf(RESET_COLOR);
                }
                break;
            }
            case DEPOSIT: {
                std::string firstName, lastName;
                double amount;
                std::cin >> firstName >> lastName >> amount;
                Customer* customer = searchCustomer(firstName, lastName, customerList);
                if (customer) {
                    customer->getWallet()->depositCash(amount);
                    printf(GREEN_COLOR);
                    std::cout << "Success! Actual cash: " << customer->getWallet()->getCash() << "\n";
                    printf(RESET_COLOR);
                } else {
                    printf(RED_COLOR);
                    std::cout << "Customer not found.\n";
                    printf(RESET_COLOR);
                }
                break;
            }
            case WITHDRAW: {
                std::string firstName, lastName;
                double amount;
                std::cin >> firstName >> lastName >> amount;
                Customer* customer = searchCustomer(firstName, lastName, customerList);
                if (customer) {
                    if (customer->getWallet()->withdrawCash(amount)) {
                        printf(GREEN_COLOR);
                        std::cout << "Success! Actual cash: " << customer->getWallet()->getCash() << "\n";
                        printf(RESET_COLOR);
                    } else {
                        std::cout << "ERROR: no cash available to withdraw actual amount!\n";
                    }
                } else {
                    printf(RED_COLOR);
                    std::cout << "Customer not found.\n";
                    printf(RESET_COLOR);
                }
                break;
            }
            case TRANSFER: {
                std::string firstName, lastName, targetFirstName, targetLastName;
                double amount;
                std::cin >> firstName >> lastName >> targetFirstName >> targetLastName >> amount;
                Customer* customer = searchCustomer(firstName, lastName, customerList);
                Customer* targetCustomer = searchCustomer(targetFirstName, targetLastName, customerList);
                if (customer && targetCustomer) {
                    if (customer->getWallet()->transferCash(targetCustomer->getWallet(), amount)) {
                        printf(GREEN_COLOR);
                        std::cout << "Success! Actual cash: " << customer->getWallet()->getCash() << "\n";
                        printf(RESET_COLOR);
                    } else {
                        std::cout << "ERROR: no cash available to transfer actual cash!\n";
                    }
                } else {
                    printf(RED_COLOR);
                    std::cout << "Customer not found.\n";
                    printf(RESET_COLOR);
                }
                break;
            }
            case HELP:
                printHelp();
                break;
            case CLEAR:
                clearScreen();
                break;
            case LIST:
                printCustomers(customerList);
                break;
            case EXIT:
                for (Customer* customer : customerList) {
                    delete customer;
                }
                std::cout << "Exiting...\n";
                exit(0);
            case UNKNOWN:
            default:
                std::cout << "Unknown command...\n";
                break;
        }
    } while (operation != "exit");

    return 0;
}
