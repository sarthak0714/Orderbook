#include "Trade.h"
#include <stdexcept>

Trade::Trade(std::string buyOrderId, std::string sellOrderId, double price, int quantity)
    : buyOrderId(buyOrderId), sellOrderId(sellOrderId), price(price), quantity(quantity) {
    if (price < 0) {
        throw std::invalid_argument("Trade price cannot be negative");
    }
    if (quantity <= 0) {
        throw std::invalid_argument("Trade quantity must be positive");
    }
}