#pragma once
#include <map>
#include <string>
#include <vector>
#include "Order.h"
#include "Trade.h"

class Orderbook {
public:
    void addOrder(const Order& order);
    bool cancelOrder(const std::string& orderId);
    std::vector<Trade> processOrder(const Order& order);
    void displayOrderbook() const;
    double getBestBid() const;
    double getBestAsk() const;

private:
    std::multimap<double, Order, std::greater<double>> bids;
    std::multimap<double, Order, std::less<double>> asks;

    std::vector<Trade> processMarketOrder(const Order& order);
    std::vector<Trade> processLimitOrder(const Order& order);
    void addToOrderbook(const Order& order);
};