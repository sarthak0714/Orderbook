#include "Order.h"

Order::Order(std::string id, OrderType type, OrderSide side, double price, int quantity)
    : id(id), type(type), side(side), price(price), quantity(quantity) {
    if (price < 0) {
        throw std::invalid_argument("Price cannot be negative");
    }
    if (quantity <= 0) {
        throw std::invalid_argument("Quantity must be positive");
    }
}

void Order::reduceQuantity(int amount) {
    if (amount > quantity) {
        throw std::invalid_argument("Reduction amount cannot be greater than current quantity");
    }
    quantity -= amount;
}