//
// Created by gustavo on 11/06/24.
//

#ifndef WALLET_WALLET_H
#define WALLET_WALLET_H

class WalletHistory;

class Customer;

class Wallet {
private:
    double cash;
    Customer* owner;
    WalletHistory* walletHistory;
public:
    Wallet(Customer*);
    void setCash(double);
    [[nodiscard]] double getCash() const;
    [[nodiscard]] Customer* getOwner() const;
    [[nodiscard]] WalletHistory* getWalletHistory() const;
    bool withdrawCash(double);
    bool depositCash(double);
    bool transferCash(Wallet*, double);
};


#endif //WALLET_WALLET_H
