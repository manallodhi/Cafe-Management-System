
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

/// Struct for Menu Item: Defines a structure to hold details of a menu item (name and price)
struct MenuItem {
    string name;   // Name of the menu item (e.g., "Coffee")
    double price;  // Price of the menu item (e.g., 2.5 for $2.50)
};

// Function to display the menu: Displays the list of available menu items with their prices
void displayMenu(MenuItem menu[], int size) {
    cout << "\n--- Menu ---\n";
    for (int i = 0; i < size; ++i) {  // Loop through each item in the menu array
        // Print the item number (index + 1), item name, and its price
        cout << i + 1 << ". " << menu[i].name << " - $" << menu[i].price << "\n";
    }
    cout << endl;  // Print a new line for better formatting
}

int main() {
    // Creating an array of menu items with name and price details
    MenuItem menu[4] = {
        {"Coffee", 2.5},    // Item 1: Coffee, price $2.50
        {"Tea", 1.5},       // Item 2: Tea, price $1.50
        {"Sandwich", 4.0},  // Item 3: Sandwich, price $4.00
        {"Cake", 3.0}       // Item 4: Cake, price $3.00
    };

    // Getting the number of menu items by dividing total size by size of one item
    int menuSize = sizeof(menu) / sizeof(menu[0]);  // Size of the menu array

    // Displaying the menu using the displayMenu function
    displayMenu(menu, menuSize);

    return 0;
}
