#include <string>

#include "Wallet/Wallet.h"
#include "Customer/Customer.h"
#include "WalletHistory/WalletHistory.h"

int main() {
    auto* firstUser = new Customer("Gustavo", "Vieira");
    auto* secondUser = new Customer("João", "DaSkina");

    firstUser->getWallet()->setCash(100);
    secondUser->getWallet()->setCash(30);

    firstUser->getWallet()->transferCash(secondUser->getWallet(), 150); // FALSE return
    firstUser->getWallet()->transferCash(secondUser->getWallet(), 50); // TRUE return

    firstUser->getWallet()->depositCash(20);
    secondUser->getWallet()->withdrawCash(55);
    secondUser->getWallet()->depositCash(65);
    firstUser->getWallet()->withdrawCash(30);
    secondUser->getWallet()->transferCash(firstUser->getWallet(), 10);

    firstUser->getWallet()->getWalletHistory()->showHistoryData();
    secondUser->getWallet()->getWalletHistory()->showHistoryData();

    delete firstUser;
    delete secondUser;
    return 0;
}
