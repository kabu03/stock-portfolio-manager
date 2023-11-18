#pragma once
#include <iostream>
#include "Stock.h"
#include <string>
#include <array>
#include "Portfolio.h"
#include <fstream>
using namespace std;

Portfolio::Portfolio(string portfolioName) :portfolioName(portfolioName), numberOfCurrentStocks(0), portfolioValue(0), stockArray(NULL) {}

Portfolio::Portfolio(const Portfolio &theOther) {
	portfolioName = theOther.portfolioName;
	numberOfCurrentStocks = theOther.numberOfCurrentStocks;
	portfolioValue = theOther.portfolioValue;
	stockArray = new Stock[numberOfCurrentStocks]; // We should write our own copy constructor since there is dynamic memory allocation.
	for (int i = 0; i < numberOfCurrentStocks; i++) {
		stockArray[i] = theOther.stockArray[i];
	}
}

Portfolio::~Portfolio()
{
	delete[] stockArray; // We should write our own destructor too, for the same reason above.
}

double Portfolio::getValue() const {
	return portfolioValue;
}

int Portfolio::getNumberOfCurrentStocks() const {
	return numberOfCurrentStocks;
}


void Portfolio::addStockToPortfolio(const Stock& stockToAdd) {
	for (int i = 0; i < numberOfCurrentStocks; i++) {
		if (stockArray[i].tickerSymbol == stockToAdd.tickerSymbol) { // Checking if the stock to be added is already in the stock array.
			cerr << "This stock is already in the portfolio. Please update the quantity instead." << endl;
			return;
		}
	}
		Stock* tempPointer = new Stock[numberOfCurrentStocks + 1]; // Allocating memory equal to the current elements + 1 for the new stock.
		if (tempPointer == nullptr) {
			cerr << "Process failed!" << endl;
			return;
		}
		for (int i = 0; i < numberOfCurrentStocks; i++) {
			tempPointer[i] = stockArray[i]; // Copy the data to the temporary pointer.
		}
		tempPointer[numberOfCurrentStocks] = stockToAdd; // Last element should be the stock we want to add.
		delete[]stockArray;
		stockArray = tempPointer;
		numberOfCurrentStocks++;
		portfolioValue += stockToAdd.stockTotalValue; // Adding the total value of the stock we just added to the portfolio itself.
		cout << "Stock " << stockToAdd.tickerSymbol << " has been successfully added to your portfolio." << endl;
	}


void Portfolio::removeStockFromPortfolio(const Stock& stockToRemove) {
	double formerStockTotalValue = stockToRemove.getStockTotalValue();
	string formerStockTickerSymbol = stockToRemove.getTickerSymbol();
	int match = -1; // If match remains -1, then the stock to remove was not in the portfolio anyway.
	for (int i = 0; i < numberOfCurrentStocks; i++) {
		if (stockArray[i].tickerSymbol == stockToRemove.tickerSymbol) {
			match = i; // If match does not remain -1, it is updated to the index of the stock the user wants to remove from the stock array.
			break;
		}
	}
	if (match != -1) {
		Stock* tempPointer = new Stock[numberOfCurrentStocks - 1]; // Allocating memory for current stocks - 1 element since we want to remove a stock.
		if (tempPointer == nullptr) {
			cout << "Process failed!" << endl;
			return;
		}
		for (int j = 0; j < match; j++) {
			tempPointer[j] = stockArray[j]; // Copying everything before the match in the array.
		}
		for (int k = match; k < numberOfCurrentStocks - 1; k++) {
			*(tempPointer+k) = stockArray[k+1]; // Copying everything after the match, but not the match itself.
		}
			delete[]stockArray;
			stockArray = tempPointer;
		portfolioValue -= formerStockTotalValue; // The value of the portfolio should decrease.
			numberOfCurrentStocks--;
			cout << "Stock " << formerStockTickerSymbol << " has been removed from your portfolio." << endl;
	}
	else cout << "This stock is not in the portfolio." << endl;
}


void Portfolio::displayPortfolio() const{ 
	if (numberOfCurrentStocks == 0) {
		cout << "Your portfolio is empty." << endl;
		return;
	}
	cout << "The following are the stocks currently saved in your portfolio:" << endl;
	for (int i = 0; i < numberOfCurrentStocks; i++) { // Using the print information method for each separate stock, in a loop traversing the entire array.
		cout << "Stock Number " << (i + 1) << ":" << " " << endl;
		stockArray[i].printInformation();
	}
	cout << "Your total portfolio value is " << portfolioValue << "." << endl;
}

void Portfolio::refreshTotalPortfolioValue() {
	double totalValue = 0.0;

	for (int i = 0; i < numberOfCurrentStocks; i++) {
		totalValue += stockArray[i].getStockTotalValue();
	}
	portfolioValue = totalValue; // Refreshes the total portfolio value, used when a certain stock feature has been updated by the user.
}

void Portfolio::clearPortfolio() { // Removing all the stocks from the portfolio, essentially reducing its value to 0.
	for (int i = 0; i < numberOfCurrentStocks; i++)
		removeStockFromPortfolio(stockArray[i]);
}


void Portfolio::writeToFile() {
	ofstream outputFile("Portfolio.txt"); // Portfolio.txt is the name of the file that contains the data to read from/write to.
	if (outputFile.is_open()) {
		for (int i = 0; i < numberOfCurrentStocks; i++) {
			const Stock& stock = stockArray[i];
			outputFile << stock.getTickerSymbol() << endl;
			outputFile << stock.getCompanyName() << endl;
			outputFile << stock.getPrice() << endl;
			outputFile << stock.getQuantityHeld() << endl;
		}

		outputFile.close();
		cout << "Portfolio data saved." << endl;
	}
	else {
		cout << "Unable to open file." << endl;
	}
}


void Portfolio::readFromFile() {
	ifstream inputFile("Portfolio.txt");

	if (inputFile.is_open()) {
		clearPortfolio(); // Removes all stocks currently in the portfolio, to load the data from the external file.

		string tickerSymbol;
		string companyName;
		double price;
		int quantity;

		while (getline(inputFile, tickerSymbol) && inputFile >> companyName >> price >> quantity) {
			inputFile.ignore(numeric_limits<streamsize>::max(), '\n');  // Ignore the remaining newline character.

			Stock stock(tickerSymbol, companyName, price, quantity);
			addStockToPortfolio(stock); // Creates a new stock from scratch, using the constructor.
		}

		inputFile.close();
		cout << "Portfolio data loaded from file: " << "Portfolio.txt" << endl;
	}
	else {
		cout << "Unable to open file: " << "Portfolio.txt" << endl;
	}
}