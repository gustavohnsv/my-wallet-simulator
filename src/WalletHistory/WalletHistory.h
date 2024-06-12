//
// Created by gustavo on 11/06/24.
//

#ifndef WALLET_WALLETHISTORY_H
#define WALLET_WALLETHISTORY_H

class Wallet;

class Customer;

class WithdrawDepositTemplate {
    public:
        Wallet* user;
        double value;
};

class TransferTemplate {
    public:
        Wallet* user;
        Wallet* target;
        double value;
};

class HistoryData {
    private:
        WithdrawDepositTemplate* wdTemplate;    // Devem ser vetores dinâmicos
        TransferTemplate* transferTemplate;     // ---------------------------
        int wdTemplateSize;
        int transferTemplateSize;
    public:
        HistoryData();
        int getWithdrawsDepositsSize();
        int getTransfersSize();
        WithdrawDepositTemplate* getWithdrawDeposit();
        TransferTemplate* getTransfer();
        void newWithdrawDepositOperation(Wallet*, double);
        void newTransferOperation(Wallet*, Wallet*, double);
        void syncNewWithdrawDeposit(WithdrawDepositTemplate*);
        void syncNewTransfer(TransferTemplate*);
};

class WalletHistory {
    private:
        HistoryData* historyData;
    public:
        HistoryData* getHistoryData();
        void showHistoryData();
};


#endif //WALLET_WALLETHISTORY_H
