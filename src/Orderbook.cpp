#include "Orderbook.h"
#include <iostream>
#include <iomanip>
#include <algorithm>

void Orderbook::addOrder(const Order& order) {
    addToOrderbook(order);
}

bool Orderbook::cancelOrder(const std::string& orderId) {
    auto cancelFromMap = [&orderId](auto& map) {
        for (auto it = map.begin(); it != map.end(); ++it) {
            if (it->second.getId() == orderId) {
                map.erase(it);
                return true;
            }
        }
        return false;
        };

    return cancelFromMap(bids) || cancelFromMap(asks);
}

std::vector<Trade> Orderbook::processOrder(const Order& order) {
    if (order.getType() == OrderType::MARKET) {
        return processMarketOrder(order);
    }
    else {
        return processLimitOrder(order);
    }
}

std::vector<Trade> Orderbook::processMarketOrder(const Order& order) {
    std::vector<Trade> trades;
    int remainingQuantity = order.getQuantity();

    if (order.getSide() == OrderSide::BUY) {
        while (!asks.empty() && remainingQuantity > 0) {
            auto it = asks.begin();
            int tradeQuantity = std::min(remainingQuantity, it->second.getQuantity());
            trades.emplace_back(order.getId(), it->second.getId(), it->first, tradeQuantity);
            remainingQuantity -= tradeQuantity;
            if (tradeQuantity == it->second.getQuantity()) {
                asks.erase(it);
            }
            else {
                it->second.reduceQuantity(tradeQuantity);
            }
        }

    }
    else {
        while (!bids.empty() && remainingQuantity > 0) {
            auto it = bids.begin();
            int tradeQuantity = std::min(remainingQuantity, it->second.getQuantity());
            trades.emplace_back(it->second.getId(), order.getId(), it->first, tradeQuantity);
            remainingQuantity -= tradeQuantity;
            if (tradeQuantity == it->second.getQuantity()) {
                bids.erase(it);
            }
            else {
                it->second.reduceQuantity(tradeQuantity);
            }
        }
    }
    
    return trades;
}

std::vector<Trade> Orderbook::processLimitOrder(const Order& order) {
    std::vector<Trade> trades;
    int remainingQuantity = order.getQuantity();
    if(order.getSide() == OrderSide::BUY) {
        while (!asks.empty() && remainingQuantity > 0) {
            auto it = asks.begin();
            if ( order.getPrice() < it->first) {
                break;
            }

            int tradeQuantity = std::min(remainingQuantity, it->second.getQuantity());

            trades.emplace_back(
                order.getId(),
                it->second.getId(),
                it->first,
                tradeQuantity
            );

            remainingQuantity -= tradeQuantity;
            if (tradeQuantity == it->second.getQuantity()) {
                asks.erase(it);
            }
            else {
                it->second.reduceQuantity(tradeQuantity);
            }
        }
    }
    else {
        while (!bids.empty() && remainingQuantity > 0) {
            auto it = bids.begin();
            if (order.getPrice() < it->first) {
                break;
            }

            int tradeQuantity = std::min(remainingQuantity, it->second.getQuantity());

            trades.emplace_back(
                order.getId(),
                it->second.getId(),
                it->first,
                tradeQuantity
            );

            remainingQuantity -= tradeQuantity;
            if (tradeQuantity == it->second.getQuantity()) {
                bids.erase(it);
            }
            else {
                it->second.reduceQuantity(tradeQuantity);
            }
        }
    }

    if (remainingQuantity > 0) {
        addToOrderbook(Order(order.getId(), order.getType(), order.getSide(), order.getPrice(), remainingQuantity));
    }

    return trades;
}

void Orderbook::addToOrderbook(const Order& order) {
    if (order.getSide() == OrderSide::BUY) {
        bids.insert({ order.getPrice(), order });
    }
    else {
        asks.insert({ order.getPrice(), order });
    }
}

void Orderbook::displayOrderbook() const {
    std::cout << std::setw(15) << std::left << "Sell Orders:";
    std::cout << std::setw(15) << std::left << "Buy Orders:" << std::endl;

    auto askIt = asks.begin();
    auto bidIt = bids.begin();

    while (askIt != asks.end() || bidIt != bids.end()) {
        if (askIt != asks.end()) {
            std::cout << std::setw(7) << std::fixed << std::setprecision(2) << askIt->first
                << " " << std::setw(7) << askIt->second.getQuantity();
            ++askIt;
        }
        else {
            std::cout << std::setw(15) << "";
        }

        if (bidIt != bids.end()) {
            std::cout << std::setw(7) << std::fixed << std::setprecision(2) << bidIt->first
                << " " << std::setw(7) << bidIt->second.getQuantity();
            ++bidIt;
        }

        std::cout << std::endl;
    }
}

double Orderbook::getBestBid() const {
    return bids.empty() ? 0.0 : bids.begin()->first;
}

double Orderbook::getBestAsk() const {
    return asks.empty() ? 0.0 : asks.begin()->first;
}