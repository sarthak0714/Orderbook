#pragma once
#include <string>
#include <stdexcept>

enum class OrderType {
    LIMIT,
    MARKET
};

enum class OrderSide {
    BUY,
    SELL
};

class Order {
public:
    Order(std::string id, OrderType type, OrderSide side, double price, int quantity);

    std::string getId() const { return id; }
    OrderType getType() const { return type; }
    OrderSide getSide() const { return side; }
    double getPrice() const { return price; }
    int getQuantity() const { return quantity; }
    void reduceQuantity(int amount);

private:
    std::string id;
    OrderType type;
    OrderSide side;
    double price;
    int quantity;
};