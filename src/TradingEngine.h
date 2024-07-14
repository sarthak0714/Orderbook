#pragma once
#include "Orderbook.h"
#include "Trade.h"
#include <vector>
#include <string>

class TradingEngine {
public:
    TradingEngine();
    std::string addOrder(OrderType type, OrderSide side, double price, int quantity);
    bool cancelOrder(const std::string& orderId);
    void displayOrderbook() const;
    double getBestBid() const;
    double getBestAsk() const;
    void displayTrades() const;

private:
    Orderbook orderbook;
    std::vector<Trade> executedTrades;
    int nextOrderId;

    std::string generateOrderId();
    void processTrades(const std::vector<Trade>& trades);
};