#pragma once
#include <iostream>
#include "Stock.h"
#include <string>
#include "Portfolio.h"
#include <thread> // For the sleep function I will use later here.

using namespace std;
// This class will handle the Menus that are displayed to the user, and the interactions with said menus.
class Menu {
	Portfolio &p; // Each menu object takes in a portfolio object.

public:

	Menu(Portfolio& p); // Taking the reference of the portfolio object as a parameter.

	void startMenu(); // Starting menu that will be displayed to the user.

	double getUserInput(); // Method to get input from the user, which could be a double to update the price, or an integer to change the menu, etc.

	void processUserInput(int userInput); // Processes user input using a switch statement. For each option the user may pick, there is a separate method.

	void addStockMenu(); 

	void removeStockMenu();

	void updateStockMenu();

	void savePortfolioMenu();

	void fetchPortfolioMenu();
};