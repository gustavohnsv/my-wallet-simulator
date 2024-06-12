//
// Created by gustavo on 11/06/24.
//

#ifndef WALLET_CUSTOMER_H
#define WALLET_CUSTOMER_H

#include <string>

class Wallet;

class Customer {
private:
    const std::string Firstname;
    const std::string LastName;
    Wallet* wallet;
public:
    Customer(std::string, std::string);
    std::string getFirstName();
    std::string getLastName();
    Wallet* getWallet();
};


#endif //WALLET_CUSTOMER_H
