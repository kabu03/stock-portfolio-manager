#include <iostream>
#include "Stock.h"
#include "Portfolio.h"
#include "Menus.h"
using namespace std;
// The main function.
int main() {
	Portfolio p1("Portfolio"); // Portfolio object created so we can make a menu object.
Menu m1(p1); // Menu object creation, which enables us to call the start menu method.
m1.startMenu();
}