cmake_minimum_required(VERSION 3.28)
project(Wallet)

set(CMAKE_CXX_STANDARD 17)

add_executable(Wallet src/main.cpp
        src/Wallet/Wallet.cpp
        src/Wallet/Wallet.h
        src/Customer/Customer.cpp
        src/Customer/Customer.h
        src/WalletHistory/WalletHistory.cpp
        src/WalletHistory/WalletHistory.h)
