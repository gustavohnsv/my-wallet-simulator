//
// Created by gustavo on 11/06/24.
//

#include <cstdlib>
#include "Customer.h"
#include "../Wallet//Wallet.h"
/**
 * Constructor of Customer class
 * @param firstName
 * @param lastName
 */
Customer::Customer(std::string firstName, std::string lastName):
    Firstname(std::move(firstName)),
    LastName(std::move(lastName)){}

/**
 * Method that returns owner wallet Class
 * @return Wallet*
 */
Wallet* Customer::getWallet() {
    if (this->wallet == NULL) {
        this->wallet = new Wallet(this);
    }
    return this->wallet;
}

/**
 * Method that returns owner's first name
 * @return String
 */
std::string Customer::getFirstName() {
    return this->Firstname;
}

/**
 * Method that returns owner's last name
 * @return String
 */
std::string Customer::getLastName() {
    return this->LastName;
}