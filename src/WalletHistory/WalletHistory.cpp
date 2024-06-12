//
// Created by gustavo on 11/06/24.
//

#include <cstdlib>
#include <cstdio>
#include <iostream>
#include "WalletHistory.h"
#include "../Customer/Customer.h"
#include "../Wallet/Wallet.h"

#define RESET_COLOR "\033[0m"
#define RED_COLOR "\033[1;31m"
#define BLUE_COLOR "\033[1;34m"
#define LIGHTBLUE_COLOR "\033[1;36m"
#define GREEN_COLOR "\033[1;32m"

/**
 * Constructor of HistoryData class
 */
HistoryData::HistoryData() : wdTemplate(new WithdrawDepositTemplate),
transferTemplate(new TransferTemplate),
wdTemplateSize(0),
transferTemplateSize(0){}

/**
 * Method that returns the number of withdrawals/deposits
 * @return int
 */
int HistoryData::getWithdrawsDepositsSize() {
    return this->wdTemplateSize;
}

/**
 * Method that returns the number of transfers
 * @return int
 */
int HistoryData::getTransfersSize() {
    return this->transferTemplateSize;
}

/**
 * Method that returns WithdrawDepositTemplate Class
 * @return WithdrawDepositTemplate*
 */
WithdrawDepositTemplate* HistoryData::getWithdrawDeposit() {
    return this->wdTemplate;
}

/**
 * Method that returns TransferTemplate Class
 * @return TransferTemplate*
 */
TransferTemplate* HistoryData::getTransfer() {
    return this->transferTemplate;
}

/**
 * Method that generates a block of withdrawal/deposit information
 * @param user
 * @param amount
 */
void HistoryData::newWithdrawDepositOperation(Wallet * user, double amount) {
    auto* newWithdrawDeposit = new WithdrawDepositTemplate();
    newWithdrawDeposit->user = user;
    newWithdrawDeposit->value = amount;
    syncNewWithdrawDeposit(newWithdrawDeposit);
    delete newWithdrawDeposit;
}

/**
 * Method that generates a block of transfer information
 * @param user
 * @param target
 * @param amount
 */
void HistoryData::newTransferOperation(Wallet * user, Wallet * target,
                                                   double amount) {
    auto* newTransfer = new TransferTemplate();
    newTransfer->user = user;
    newTransfer->target = target;
    newTransfer->value = amount;
    syncNewTransfer(newTransfer);
    delete newTransfer;
}

/**
 * Method that synchronizes a new operation with the deposit/withdrawal history
 * @param operation
 */
void HistoryData::syncNewWithdrawDeposit(WithdrawDepositTemplate * operation) {
    if (wdTemplate == NULL) {
        wdTemplate = (WithdrawDepositTemplate*) calloc(1, sizeof(WithdrawDepositTemplate));
        wdTemplate[0] = *operation;
        this->wdTemplateSize++;
    } else {
        wdTemplate = (WithdrawDepositTemplate*) realloc(wdTemplate,
                                                        (this->getWithdrawsDepositsSize() + 1) *
                                                        sizeof(WithdrawDepositTemplate));
        wdTemplate[this->getWithdrawsDepositsSize()] = *operation;
        this->wdTemplateSize++;
    }
}

/**
 * Method that synchronizes a new operation with the transfer history
 * @param operation
 */
void HistoryData::syncNewTransfer(TransferTemplate * operation) {
    if (transferTemplate == NULL) {
        transferTemplate = (TransferTemplate*) calloc(1, sizeof(TransferTemplate));
        transferTemplate[0] = *operation;
        this->transferTemplateSize++;
    } else {
        transferTemplate = (TransferTemplate*) realloc(transferTemplate,
                                                       (this->getTransfersSize() + 1) *
                                                       sizeof(TransferTemplate));
        transferTemplate[this->getTransfersSize()] = *operation;
        this->transferTemplateSize++;
    }
}

/**
 * Method that returns HistoryData Class
 * @return HistoryData*
 */
HistoryData* WalletHistory::getHistoryData() {
    if (this->historyData == NULL) {
        this->historyData = new HistoryData();
    }
    return this->historyData;
}

/**
 * Method that displays the user's entire wallet movement history
 */
void WalletHistory::showHistoryData() {
    int W = this->getHistoryData()->getWithdrawsDepositsSize();
    int T = this->getHistoryData()->getTransfersSize();
    for (int i = 0; i < W; i++) {
        printf(LIGHTBLUE_COLOR);
        printf("[\U0001F4B0] Depósito / Saque: \n\n");
        printf(RESET_COLOR);
        WithdrawDepositTemplate* wdTemplate = this->getHistoryData()->getWithdrawDeposit();
        Wallet* wallet = wdTemplate[i].user;
        if (wallet && wallet->getOwner()) {
            printf(BLUE_COLOR);
            std::cout << "Carteira: " << wallet->getOwner()->getFirstName() << " " << wallet->getOwner()->getLastName() << "\n";
            printf(RESET_COLOR);
        }
        if (wdTemplate[i].value > 0) {
            printf(GREEN_COLOR);
            printf("Balanço: +%.2f\n\n", wdTemplate[i].value);
        } else {
            printf(RED_COLOR);
            printf("Balanço: %.2f\n\n", wdTemplate[i].value);
        }
        printf(RESET_COLOR);
    }
    for (int j = 0; j < T; j++) {
        printf(LIGHTBLUE_COLOR);
        printf("[\U0001F4B9] Transferência: \n\n");
        printf(RESET_COLOR);
            TransferTemplate* tTemplate = this->getHistoryData()->getTransfer();
            Wallet* wallet = tTemplate[j].user;
            Wallet* target = tTemplate[j].target;
            if ((wallet && wallet->getOwner()) && (target && target->getOwner())) {
                printf(BLUE_COLOR);
                std::cout << "Carteira origem: " << wallet->getOwner()->getFirstName() << " " << wallet->getOwner()->getLastName() << "\n";
                std::cout << "Carteira destino: " << target->getOwner()->getFirstName() << " " << target->getOwner()->getLastName() << "\n";
                printf(RESET_COLOR);
            }
            printf(RED_COLOR);
            printf("Balanço de origem: %.2f\n\n", tTemplate[j].value);
            printf(RESET_COLOR);
    }
}