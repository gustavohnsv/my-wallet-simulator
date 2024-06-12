# Definição do compilador
CXX = g++

# Flags de compilação
CXXFLAGS = -std=c++11 -Wall

# Diretórios
SRC_DIR = src
CUSTOMER_DIR = $(SRC_DIR)/Customer
WALLET_DIR = $(SRC_DIR)/Wallet
WALLETHISTORY_DIR = $(SRC_DIR)/WalletHistory

# Arquivos fonte
SOURCES = $(CUSTOMER_DIR)/Customer.cpp $(WALLET_DIR)/Wallet.cpp $(WALLETHISTORY_DIR)/WalletHistory.cpp $(SRC_DIR)/main.cpp

# Arquivos objeto
OBJECTS = $(SOURCES:.cpp=.o)

# Nome do executável
EXEC = WalletApp

# Regras
all: $(EXEC)

$(EXEC): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(SRC_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(CUSTOMER_DIR)/%.o: $(CUSTOMER_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(WALLET_DIR)/%.o: $(WALLET_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(WALLETHISTORY_DIR)/%.o: $(WALLETHISTORY_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Limpeza
clean:
	rm -f $(OBJECTS) $(EXEC)

# Phony targets
.PHONY: all clean
