#include "Orderbook.h"
#include <iostream>
#include <algorithm>

void Orderbook::addOrder(const Order& order) {
	if (order.getOrderSide() == OrderSide::BUY) {
		buyOrders.insert(std::make_pair(order.getOrderPrice(), order));
	}
	else {
		sellOrders.insert(std::make_pair(order.getOrderPrice(), order));
	}
}

void Orderbook::cancelOrder(const std::string &orderId) {
	auto cancelOrderFromBook = [&orderId](auto& book) {
		for (auto i = book.begin(); i != book.end(); i++) {
			if (i->second.getId() == orderId) {
				book.erase(i);
				return true;
			}
		}
		return false;
	};
	if (!cancelOrderFromBook(buyOrders)) {
		cancelOrderFromBook(sellOrders);
	}
}




std::vector<Trade> Orderbook::matchOrders() {
	std::vector<Trade> trades;

	while (!buyOrders.empty() && !sellOrders.empty()) {
		auto buy = buyOrders.begin();
		auto sell = sellOrders.begin();

		if (buy->first >= sell->first) {
			int matchedQty = std::min(buy->second.getQuantity(), sell->second.getQuantity());
			trades.emplace_back(buy->second.getId(), sell->second.getId(), sell->first, matchedQty);

			buy->second.reduceQuantity(matchedQty);
			sell->second.reduceQuantity(matchedQty);
			if (!buy->second.getQuantity()) buyOrders.erase(buy);
			if (!sell->second.getQuantity()) sellOrders.erase(sell);
		}
		else {
			break;
		}
	}
	return trades;
}

void Orderbook::displayOrderBook() const {
	std::cout << "Sell Orders\n";
	for (const auto& order : sellOrders) {
		std::cout << "Price: " << order.first << " Qty: " << order.second.getQuantity() << " Price: " << order.second.getOrderPrice() << " Type: " << (order.second.getOrderType() == OrderType::LIMIT ? "LIMIT" : "MARKET")<<"\n";

	}
	std::cout << "\nBuy Orders\n";
	for (const auto& order : buyOrders) {
		std::cout << "Price: " << order.first << " Qty: " << order.second.getQuantity() << " Price: " << order.second.getOrderPrice() << " Type: " << (order.second.getOrderType() == OrderType::LIMIT ? "LIMIT" : "MARKET") << "\n";

	}
	
}