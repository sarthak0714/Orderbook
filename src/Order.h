#pragma once
#include <string>

enum class OrderType {
	LIMIT,
	MARKET
};

enum class OrderSide {
	BUY,
	SELL
};

class Order {
public:
	Order(std::string id, OrderType type, OrderSide side, double price, int qty);

	std::string getId() const { return id; }
	OrderType getOrderType() const { return type; }
	OrderSide getOrderSide() const { return side; }
	double getOrderPrice() const { return price; }
	int getQuantity() const { return qty; }
	void reduceQuantity(int amt) { qty -= amt; }

private:
	std::string id;
	OrderType type;
	OrderSide side;
	double price;
	int qty;
};