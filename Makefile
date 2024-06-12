# Definição do compilador
CXX = gcc

# Flags de compilação
CXXFLAGS = -std=c++11 -Wall

# Diretórios
SRC_DIR = src
CUSTOMER_DIR = $(SRC_DIR)/Customer
WALLET_DIR = $(SRC_DIR)/Wallet
WALLETHISTORY_DIR = $(SRC_DIR)/WalletHistory

# Arquivos fonte
SOURCES = $(CUSTOMER_DIR)/Customer.cpp $(WALLET_DIR)/Wallet.cpp $(WALLETHISTORY_DIR)/WalletHistory.cpp main.cpp

# Arquivo objeto
OBJECTS = $(SOURCES:.cpp=.o)

# Nome do executável
EXEC = main

# Regras
all: $(EXEC)

$(EXEC): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Limpeza
clean:
	rm -f $(OBJECTS) $(EXEC)

# Phony targets
.PHONY: all clean
