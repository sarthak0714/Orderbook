#include "TradingEngine.h"
#include <iostream>
#include <iomanip>
#include <stdexcept>

TradingEngine::TradingEngine() : nextOrderId(1) {}

std::string TradingEngine::addOrder(OrderType type, OrderSide side, double price, int quantity) {
    try {
        if (quantity <= 0) {
            throw std::invalid_argument("Quantity must be positive");
        }
        if (type == OrderType::LIMIT && price <= 0) {
            throw std::invalid_argument("Price must be positive for limit orders");
        }

        std::string orderId = generateOrderId();
        Order order(orderId, type, side, price, quantity);
        std::vector<Trade> trades = orderbook.processOrder(order);
        processTrades(trades);
        return orderId;
    }
    catch (const std::exception& e) {
        std::cerr << "Error adding order: " << e.what() << std::endl;
        return "";
    }
}

bool TradingEngine::cancelOrder(const std::string& orderId) {
    return orderbook.cancelOrder(orderId);
}

void TradingEngine::displayOrderbook() const {
    orderbook.displayOrderbook();
}

double TradingEngine::getBestBid() const {
    return orderbook.getBestBid();
}

double TradingEngine::getBestAsk() const {
    return orderbook.getBestAsk();
}

void TradingEngine::displayTrades() const {
    std::cout << "Executed Trades:" << std::endl;
    for (const auto& trade : executedTrades) {
        std::cout << "Trade: " << trade.getBuyOrderId() << " bought from "
            << trade.getSellOrderId() << " at price " << std::fixed << std::setprecision(2)
            << trade.getPrice() << " for quantity " << trade.getQuantity() << std::endl;
    }
}


std::string TradingEngine::generateOrderId() {
    return "ZYZZ" + std::to_string(nextOrderId++);
}

void TradingEngine::processTrades(const std::vector<Trade>& trades) {
    for (const auto& trade : trades) {
        executedTrades.push_back(trade);
        std::cout << "Trade executed: " << trade.getBuyOrderId() << " bought from "
            << trade.getSellOrderId() << " at price " << std::fixed << std::setprecision(2)
            << trade.getPrice() << " for quantity " << trade.getQuantity() << std::endl;
    }
}