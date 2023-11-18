#pragma once
#include <iostream>
#include "Stock.h"
using namespace std;

Stock::Stock() :tickerSymbol(""), companyName(""), price(0), quantityHeld(0) {}

Stock::Stock (const Stock& other) {
	tickerSymbol = other.tickerSymbol;
	companyName = other.companyName;
	price = other.price;
	quantityHeld = other.quantityHeld;
}

Stock::Stock(string a, string b, double c, double d)
	:tickerSymbol(a), companyName(b), price(c), quantityHeld(d) {}

void Stock::printInformation() const {
	cout << "You are currently holding " << quantityHeld << " shares of stock " << tickerSymbol <<
		" which is made by the company " << companyName << ", with each share being worth " << price
		<< " thus making the total value " << stockTotalValue << "." << endl;
}

string Stock::getTickerSymbol() const {
	return tickerSymbol;
}

string Stock::getCompanyName() const {
	return companyName;
}

double Stock::getPrice() const {
	return price;
}

double Stock::getQuantityHeld() const {
	return quantityHeld;
}

double Stock::getStockTotalValue() const {
	return stockTotalValue;
}

void Stock::updatePrice() {
	double newPrice;
	cout << "You are about to modify the price of this stock: " << tickerSymbol << "." << endl;
	cout << "What is the new price of this stock? It is currently " << price << "." << endl;
	cin >> newPrice;
	if (newPrice > 0) {
		price = newPrice;
		cout << "Done! The new price of stock " << tickerSymbol << " is " << price << "." << endl;
		stockTotalValue = quantityHeld * price; // Refreshing the stock's total value, since the price has changed.
	}
	else cout << "Invalid input.";
}

void Stock::modifyQuantity() {
	double newQuantity;
	cout << "You are about to modify the quantity of this stock: " << tickerSymbol << "." << endl;
	cout << "What do you want the new quantity to be? You currently have " << quantityHeld << " shares." << endl;
	cin >> newQuantity;
	if (newQuantity > 0) {
		quantityHeld = newQuantity;
		cout << "Done! Your total quantity of stock " << tickerSymbol << " is now " << quantityHeld << " shares." << endl;
		stockTotalValue = quantityHeld * price; // Refreshing the stock's total value, since the quantity has changed.
	}
	else cout << "Invalid input.";
}