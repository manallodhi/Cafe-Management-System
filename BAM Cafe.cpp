
#include <iostream>  // Handles input/output operations.
#include <fstream>   // File input/output operations.
#include <vector>    // Dynamic array/container.
#include <ctime>     // Time manipulation.
#include <cstdlib>   // Provides std::rand for generating random numbers and std::srand
                   //for seeding the random number generator.
#include <stdexcept> // Exception handling.
#include <algorithm> // For std::shuffle (Algorithms for common operations)
#include <random>    // For std::random_device (Random number generation.)

using namespace std ;

// Struct for Menu Item: Defines a structure to hold details of a menu item (name and price)
struct MenuItem {
    string name;   // Name of the menu item (e.g., "Coffee")
    double price;  // Price of the menu item (e.g., 2.5 for $2.50)
};

// Function to display the menu: Displays the list of available menu items with their prices
void displayMenu(const vector<MenuItem>& menu) {
    cout << "\n--- Menu ---\n";  // Print the title of the menu
    for (size_t i = 0; i < menu.size(); ++i) {  // Loop through each item in the menu vector
        // Print the item number (index + 1), item name, and its price
        cout << i + 1 << ". " << menu[i].name << " - $" << menu[i].price << "\n";
    }
    cout << endl;  // Print a new line for better formatting
}


int main() {

  return 0 ;
}
