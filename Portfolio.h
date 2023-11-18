#pragma once
#include <iostream>
#include "Stock.h"
#include <string>
#include <array>
using namespace std;
// A portfolio is capable of holding a collection of stocks.
class Portfolio {
	friend class Menu; // To allow the Menu class to be able to access methods from the Portfolio class.
	string portfolioName; // The main identifier of any portfolio.
	int numberOfCurrentStocks;
	double portfolioValue; // The sum of the total values of each stock in the portfolio.
	Stock *stockArray; // The data structure used to store the stocks themselves.
public:
	Portfolio(string portfolioName); // Constructor.

	Portfolio(const Portfolio &theOther); // Copy constructor.

	~Portfolio(); // Destructor, as there will be dynamic memory allocation in the implementation.

	double getValue() const;

	int getNumberOfCurrentStocks () const;

	void addStockToPortfolio(const Stock& stock); // Method that allows the user to add a stock to their portfolio.

	void removeStockFromPortfolio(const Stock& stock); // Method that allows the user to remove a stock from their portfolio.

	void displayPortfolio() const; // Displays the general data of the portfolio, including its total value.

	void refreshTotalPortfolioValue();

	void readFromFile(); // Reads portfolio data from a file.

	void writeToFile(); // Writes portfolio data to a file, overwriting anything that was previously stored.

	void clearPortfolio();

};