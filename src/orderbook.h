#pragma once 
#include <map>
#include <vector>
#include <functional>
#include "Trade.h"
#include "Order.h"

class Orderbook {
private:
	void addOrder(const Order& order);
	void cancelOrder(const std::string& orderId);
	std::vector<Trade> matchOrders();
	void displayOrderBook() const;

private:
	std::multimap<double, Order, std::greater<double>> buyOrders;
	std::multimap<double, Order, std::greater<double>> sellOrders;


};