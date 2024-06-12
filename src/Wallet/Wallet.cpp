//
// Created by gustavo on 11/06/24.
//

#include "Wallet.h"
#include "../Customer/Customer.h"
#include "../WalletHistory/WalletHistory.h"

/**
 * Constructor of Wallet class
 * @param owner
 */
Wallet::Wallet(Customer* owner) : walletHistory(new WalletHistory()),
owner(owner){}

/**
 * Method that returns wallet cash
 * @return double
 */
double Wallet::getCash() const {
    return this->cash;
}

/**
 * Method that returns wallet owner Class
 * @return Customer*
 */
Customer *Wallet::getOwner() const {
    return this->owner;
}

/**
 * Method that returns wallet history Class
 * @return WalletHistory*
 */
WalletHistory* Wallet::getWalletHistory() const {
    return this->walletHistory;
}

/**
 * Method to set a cash value
 * @param newCash
 */
void Wallet::setCash(double newCash) {
    // Verficica se o valor definido é menor que zero
    this->cash = newCash;
}

/**
 * Method that withdraws an amount if possible
 * @param amount
 * @return bool
 */
bool Wallet::withdrawCash(double amount) {
    if (this->getCash() < amount) {
        // std::cout << "ERROR: insufficient funds\n";
        return false;
    } else {
        this->setCash(this->getCash() - amount);
        this->getWalletHistory()->getHistoryData()->newWithdrawDepositOperation(this, -amount);
        return true;
    }
}

/**
 * Method that deposits an amount if possible
 * @param amount
 * @return bool
 */
bool Wallet::depositCash(double amount) {
    if (amount < 0) {
        // std::cout << "ERROR: no operation\n";
        return false;
    } else {
        this->setCash(this->getCash() + amount);
        this->getWalletHistory()->getHistoryData()->newWithdrawDepositOperation(this, amount);
        return true;
    }
}

/**
 * Method that transfers an amount, if possible, to another wallet
 * @param targetWallet
 * @param amount
 * @return bool
 */
bool Wallet::transferCash(Wallet * targetWallet, double amount) {
    if (this->getCash() < amount) {
        // std::cout << "ERROR: insufficient funds\n";
        return false;
    } else {
        targetWallet->setCash(targetWallet->getCash() + amount);
        this->setCash(this->getCash() - amount);
        this->getWalletHistory()->getHistoryData()->newTransferOperation(this, targetWallet, -amount);
        return true;
    }
}