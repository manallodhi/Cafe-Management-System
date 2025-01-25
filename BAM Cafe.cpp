
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

// Function to handle order placement using arrays instead of vectors
double placeOrder(MenuItem menu[], int menuSize, MenuItem order[], int &orderSize) {
    int choice;            // To store the user's choice
    double total = 0.0;    // To store the total cost of the order
    orderSize = 0;         // To keep track of the number of items in the order

    cout << "\nPlace your order (Enter 0 to finish):\n";
    while (true) {
        cin >> choice;     // Take the user's input
        if (choice == 0) break;  // Exit the loop if the user enters 0
        if (choice < 1 || choice > menuSize) {  // Check for invalid input
            cout << "Invalid choice! Try again.\n";
            continue;  // Skip the rest of the loop and ask for input again
        }

        // Add the selected menu item to the order array
        order[orderSize] = menu[choice - 1];
        total += menu[choice - 1].price;  // Add the price to the total
        cout << menu[choice - 1].name << " added to your order.\n";
        orderSize++;  // Increment the number of items in the order
    }
    return total;  // Return the total cost of the order
}

// Function to play a scrambled word guessing game
void scrambleGame() {
    // Define the original word to be scrambled
    string word = "cafe";
    string scrambled = word;

    // Shuffle the word using a random generator
    std::random_device rd;  // Seed for random number generator
    std::mt19937 g(rd());   // Random number generator
    std::shuffle(scrambled.begin(), scrambled.end(), g);  // Shuffle the letters

    // Display the scrambled word to the user
    cout << "\nScrambled word: " << scrambled << endl;

    // Prompt the user to guess the original word
    cout << "Can you guess the original word? It's something you enjoy at a cafe!\n";
    cout << "Your guess (hint: it's 4 letters): ";
    string guess;
    cin >> guess;  // Read the user's guess

    // Check if the user's guess is correct
    if (guess == word) {
        cout << "Correct! You guessed it. Well done!\n";
    } else {
        cout << "Wrong! The correct word was: " << word << ". Better luck next time!\n";
    }

    // Add some engagement with follow-up questions
    cout << "What's your favorite drink at a cafe? ";
    string favoriteDrink;
    cin.ignore();          // Clear the input buffer
    getline(cin, favoriteDrink);  // Read user's favorite drink
    cout << "Yum! " << favoriteDrink << " sounds great!\n";
}


int main() {

    cout << "   Welcome to BAM Cafe   " << endl ;

    MenuItem menu[4] = {
        {"Coffee", 2.5},
        {"Tea", 1.5},
        {"Sandwich", 4.0},
        {"Cake", 3.0}
    };
    int menuSize = sizeof(menu) / sizeof(menu[0]);  // Size of menu array

    // Display the menu to the user
    displayMenu(menu, menuSize);

    MenuItem order[10];  // Array to store a maximum of 10 ordered items
    int orderSize = 0;   // Number of items in the order

    // Place the order
    double total = placeOrder(menu, menuSize, order, orderSize);

    // Display the order summary
    if (total > 0) {
        cout << "\nOrder Summary:\n";
        for (int i = 0; i < orderSize; ++i) {
            cout << "- " << order[i].name << " - $" << order[i].price << "\n";
        }
        cout << "Total: $" << total << "\n";
    } else {
        cout << "No items ordered.\n";
    }

    // Game options
    int gameChoice;
    cout << "\nWould you like to play a game?\n";
    cout << "1. Scramble Game\n2. Exit\n";
    cout << "Enter your choice: ";
    cin >> gameChoice;

    switch (gameChoice) {
        case 1:
            // Play the scramble game
            scrambleGame();
            break;
        case 2:
            // Exit the program
            cout << "Thank you for visiting Bam Cafe!\n";
            break;
        default:
            // Handle invalid input
            cout << "Invalid choice! Exiting...\n";
    }

    return 0;
}
