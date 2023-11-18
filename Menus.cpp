#pragma once
#include "Menus.h"

Menu::Menu(Portfolio& p) :p(p) {}

void Menu::startMenu() {
	int userInput = 0;

	while (userInput != 7) {
		this_thread::sleep_for(chrono::milliseconds(1000));
		system("cls");
		cout << "Greetings, user! Welcome to your Stock Portfolio Manager. What would you like to do?" << endl;
		cout << "1. View your Portfolio data." << endl;
		cout << "2. Add a new stock to your portfolio." << endl;
		cout << "3. Remove a stock from your portfolio." << endl;
		cout << "4. Update a stock's quantity or price." << endl;
		cout << "5. Save your portfolio data to an external file (IMPORTANT)!" << endl;
		cout << "6. Fetch portfolio data from the external file." << endl;
		cout << "7. Quit." << endl;

		userInput = getUserInput();
		processUserInput(userInput);
	}
}

double Menu::getUserInput() {
	double userInput;
	cin >> userInput;

	while (cin.fail()) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Invalid input. Please enter a valid option: ";
		cin >> userInput;
	}

	return userInput;
}

void Menu::processUserInput(int userInput) {
	switch (userInput) {
	case 1:
		p.displayPortfolio();
		cout << "Press 1 when you have finished viewing your portfolio, to go back to the main menu." << endl;
		while (getUserInput() != 1)
			cout << "Invalid input." << endl;
		break;
	case 2:
		addStockMenu();
		break;
	case 3:
		removeStockMenu();
		break;
	case 4:
		updateStockMenu();
		break;
	case 5:
		savePortfolioMenu();
		break;
	case 6:
		fetchPortfolioMenu();
		break;
	case 7:
		break;
	default:
		// cout << "Invalid input. Please try again." << endl;
		break;
	}
}

void Menu::addStockMenu() {
	string tickerSymbol;
	string companyName;
	double price;
	double quantityHeld;
	int confirmation;
	cout << "You've chosen to add a new stock to your portfolio. What is the stock's ticker symbol?" << endl;
	cin >> tickerSymbol;
	cout << "Which company's stock is this?" << endl;
	cin >> companyName;
	cout << "What is the current price of a single share of this stock?" << endl;
	price = getUserInput();
	cout << "How many shares of this stock are you holding?" << endl;
	quantityHeld = getUserInput();
	cout << "Confirmation: The stock's ticker symbol is " << tickerSymbol << ", by the company "
		<< companyName << ". Its price is currently " << price << ", and you're holding "
		<< quantityHeld << " shares of it. If the information is correct, press 1." << endl;
	confirmation = getUserInput();
	if (confirmation == 1) {
		Stock stockToAdd(tickerSymbol, companyName, price, quantityHeld);
		p.addStockToPortfolio(stockToAdd);
		this_thread::sleep_for(chrono::milliseconds(2000));
	}
	else {
		system("cls");
		cout << "Invalid input, please try again." << endl;
	}
}

void Menu::removeStockMenu() {
	int numberOfStock;
	cout << "You've chosen to remove a stock from your portfolio. These are the stocks you currently have:" << endl;
	p.displayPortfolio();
	cout << "Enter the number of the stock you'd like to remove." << endl;
	numberOfStock = getUserInput();
	if (numberOfStock >= 1 && numberOfStock <= p.numberOfCurrentStocks) {
		p.removeStockFromPortfolio((p.stockArray)[(numberOfStock - 1)]);
	}
	else {
		cout << "Invalid stock number. Please enter a valid stock number." << endl;
	}
}

void Menu::updateStockMenu() {
	int numberOfStock;
	double newPrice;
	int userInput;
	cout << "You've chosen to update a stock in your portfolio. These are the stocks you currently have:" << endl;
	p.displayPortfolio();
	cout << "Enter the number of the stock you'd like to update." << endl;
	cin >> numberOfStock;
	cout << "Enter 1 if you'd like to modify the quantity of the stock, and 2 if you'd like to update its price." << endl;
	cin >> userInput;
	if (userInput == 1) {
		p.stockArray[numberOfStock - 1].modifyQuantity();
		p.refreshTotalPortfolioValue();
		this_thread::sleep_for(chrono::milliseconds(2000));
	}
	else if (userInput == 2) {
		p.stockArray[numberOfStock - 1].updatePrice();
		p.refreshTotalPortfolioValue();
		this_thread::sleep_for(chrono::milliseconds(2000));
	}
	else {
		system("cls");
		cout << "Invalid input, please try again." << endl;
	}
}

void Menu::savePortfolioMenu() {
	p.writeToFile();
}

void Menu::fetchPortfolioMenu() {
	p.readFromFile();
}