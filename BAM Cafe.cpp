
#include <iostream>  // Handles input/output operations
#include <string>    // For string operations
#include <ctime>     // Time manipulation for random number generation
#include <cstdlib>   // Provides std::srand and std::rand
#include <algorithm> // For std::random_shuffle
using namespace std;

// Struct for Menu Item
struct MenuItem {
    string name;   // Name of the menu item
    double price;  // Price of the menu item
};

// Function to display the menu
void displayMenu(MenuItem menu[], int size) {
    cout << "\n--- Menu ---\n";
    for (int i = 0; i < size; ++i) {
        cout << i + 1 << ". " << menu[i].name << " - $" << menu[i].price << "\n";
    }
    cout << endl;
}

// Function to handle order placement
double placeOrder(MenuItem menu[], int menuSize, MenuItem order[], int &orderSize) {
    int choice;
    double total = 0.0;
    orderSize = 0;

    cout << "\nPlace your order (Enter 0 to finish):\n";
    while (true) {
        cin >> choice;
        if (choice == 0) break;
        if (choice < 1 || choice > menuSize) {
            cout << "Invalid choice! Try again.\n";
            continue;
        }
        order[orderSize] = menu[choice - 1];
        total += menu[choice - 1].price;
        cout << menu[choice - 1].name << " added to your order.\n";
        orderSize++;
    }
    return total;
}

// Function to play a scrambled word guessing game
void scrambleGame() {
    string word = "cafe";
    string scrambled = word;

    std::srand(std::time(0)); // Seed the random number generator
    std::random_shuffle(scrambled.begin(), scrambled.end());

    cout << "\nScrambled word: " << scrambled << endl;
    cout << "Can you guess the original word? It's something you enjoy at a cafe!\n";
    cout << "Your guess (hint: it's 4 letters): ";
    string guess;
    cin >> guess;

    if (guess == word) {
        cout << "Correct! You guessed it. Well done!\n";
    } else {
        cout << "Wrong! The correct word was: " << word << ". Better luck next time!\n";
    }

    cout << "What's your favorite drink at a cafe? ";
    string favoriteDrink;
    cin.ignore(); // Clear input buffer
    getline(cin, favoriteDrink);
    cout << "Yum! " << favoriteDrink << " sounds great!\n";
}

// Main function
int main() {
    cout << "   Welcome to BAM Cafe   " << endl;

    MenuItem menu[4] = {
        {"Coffee", 2.5},
        {"Tea", 1.5},
        {"Sandwich", 4.0},
        {"Cake", 3.0}
    };
    int menuSize = sizeof(menu) / sizeof(menu[0]);

    // Display the menu
    displayMenu(menu, menuSize);

    MenuItem order[10]; // Array to store a maximum of 10 ordered items
    int orderSize = 0;

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
            scrambleGame();
            break;
        case 2:
            cout << "Thank you for visiting BAM Cafe!\n";
            break;
        default:
            cout << "Invalid choice! Exiting...\n";
    }

    return 0;
}
