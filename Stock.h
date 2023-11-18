#pragma once
#include <iostream>

using namespace std;
// The main building block of the program.
class Stock {
	friend class Portfolio; // To allow the Portfolio class to access methods from the Stock class.
	string tickerSymbol;
	string companyName;
	double price;
	double quantityHeld; // These will be the four main features of any stock in the program.
	double stockTotalValue = (price * quantityHeld);
public:

	Stock(); // Parameter-less constructor.

	Stock(const Stock& other); // Copy constructor.

	Stock(string a, string b, double c, double d); // Constructor that allows initialisation.

	void printInformation() const; // Prints the general information about any stock.

	string getTickerSymbol() const;

	string getCompanyName() const; // These methods are constant as they are not designed to alter the state of the class.

	double getPrice() const;

	double getQuantityHeld() const;

	double getStockTotalValue() const; // The total value of any stock is the quantity held multiplied by the price.

	void updatePrice(); // A method that allows the user to change the price according to the current market.

	void modifyQuantity(); // A method that allows the user to notify the program if they had bought/sold shares.
};