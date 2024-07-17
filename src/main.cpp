#include "TradingEngine.h"
#include <iostream>
#include <stdexcept>

int main() {
    TradingEngine engine;
    try {
        // Add initial limit orders
        engine.addOrder(OrderType::LIMIT, OrderSide::BUY, 100.0, 10);
        engine.addOrder(OrderType::LIMIT, OrderSide::SELL, 101.0, 5);
        engine.addOrder(OrderType::LIMIT, OrderSide::BUY, 99.5, 7);
        engine.addOrder(OrderType::LIMIT, OrderSide::SELL, 102.0, 3);
        std::cout << "Initial Orderbook:\n";
        engine.displayOrderbook();

        // Add a market order
        engine.addOrder(OrderType::MARKET, OrderSide::BUY, 0.0, 4);
        std::cout << "\nAfter Market Order:\n";
        engine.displayOrderbook();

        // Add more limit orders
        std::string orderId = engine.addOrder(OrderType::LIMIT, OrderSide::BUY, 101.5, 4);
        engine.addOrder(OrderType::LIMIT, OrderSide::SELL, 101.0, 2);
        std::cout << "\nAfter More Orders:\n";
        engine.displayOrderbook();

        // Cancel an order
        if (engine.cancelOrder(orderId)) {
            std::cout << "Order " << orderId << " cancelled.\n";
        }
        else {
            std::cout << "Failed to cancel order " << orderId << ".\n";
        }
        std::cout << "\nAfter Cancelling Order:\n";
        engine.displayOrderbook();

        // Add more trades
        engine.addOrder(OrderType::LIMIT, OrderSide::SELL, 99.0, 6);
        engine.addOrder(OrderType::MARKET, OrderSide::SELL, 0.0, 8);
        engine.addOrder(OrderType::LIMIT, OrderSide::BUY, 102.0, 3);
        std::cout << "\nAfter More Trades:\n";
        engine.displayOrderbook();

        // Display best bid and ask
        std::cout << "\nBest Bid: " << engine.getBestBid() << std::endl;
        std::cout << "Best Ask: " << engine.getBestAsk() << std::endl;

        // Display all trades
        engine.displayTrades();

        // Attempt to add an invalid order
        std::cout << "\nAdding Invalid Order:\n";
        engine.addOrder(OrderType::LIMIT, OrderSide::BUY, -10.0, 5);
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
