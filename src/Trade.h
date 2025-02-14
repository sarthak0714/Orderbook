#pragma once
#include <string>

class Trade {
public:
    Trade(std::string buyOrderId, std::string sellOrderId, double price, int quantity);

    std::string getBuyOrderId() const { return buyOrderId; }
    std::string getSellOrderId() const { return sellOrderId; }
    double getPrice() const { return price; }
    int getQuantity() const { return quantity; }

private:
    std::string buyOrderId;
    std::string sellOrderId;
    double price;
    int quantity;
};