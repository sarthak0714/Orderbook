#include "TradingEngine.h"
#include <iostream>
#include <stdexcept>

int main() {
    TradingEngine engine;
    try {
        // Add limit orders
        engine.addOrder(OrderType::LIMIT, OrderSide::BUY, 100.0, 10);
        engine.addOrder(OrderType::LIMIT, OrderSide::SELL, 101.0, 5);
        engine.addOrder(OrderType::LIMIT, OrderSide::BUY, 99.5, 7);
        engine.addOrder(OrderType::LIMIT, OrderSide::SELL, 102.0, 3);
        std::cout << "Initial Orderbook:\n";
        engine.displayOrderbook();

        // Add a market order
        engine.addOrder(OrderType::MARKET, OrderSide::BUY, 0.0, 4);
        std::cout << "\nOrderbook after market order:\n";
        engine.displayOrderbook();

        // Add more limit orders
        std::string orderId = engine.addOrder(OrderType::LIMIT, OrderSide::BUY, 101.5, 4);
        engine.addOrder(OrderType::LIMIT, OrderSide::SELL, 101.0, 2);
        std::cout << "\nOrderbook after adding more orders:\n";
        engine.displayOrderbook();

        // Cancel an order
        if (engine.cancelOrder(orderId)) {
            std::cout << "Order " << orderId << " cancelled successfully.\n";
        }
        else {
            std::cout << "Failed to cancel order " << orderId << ".\n";
        }
        std::cout << "\nOrderbook after cancelling an order:\n";
        engine.displayOrderbook();

        // Display best bid and ask
        std::cout << "\nBest Bid: " << engine.getBestBid() << std::endl;
        std::cout << "Best Ask: " << engine.getBestAsk() << std::endl;

        // Display all trades
        std::cout << "\nAll executed trades:\n";
        engine.displayTrades();


        // err 
        std::cout << "\nAttempting to add an invalid order:\n";
        engine.addOrder(OrderType::LIMIT, OrderSide::BUY, -10.0, 5);

    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}