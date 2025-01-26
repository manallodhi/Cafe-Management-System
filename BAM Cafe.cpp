#include <iostream>  // Handles input/output operations
#include <string>    // For string operations
#include <ctime>     // Time manipulation for random number generation
#include <fstream>
#include <cstdlib>   // Provides std::srand and std::rand
#include <algorithm> // For std::random_shuffle
#include <cctype>  // For isalpha
#include <string>  // For std::string
using namespace std;

// Struct for Menu Item
struct MenuItem {
    string name; // Name of the menu item
    double price; // Price of the menu item
};

// Structure to store user information
struct User {
    string name;
    string email;
    string phone;
    string address;
};

// Function to display the menu
void displayMenu(MenuItem menu[], int size) {
    cout << "\n--- Menu ---\n";
    for (int i = 0; i < size; ++i) {
        cout << i + 1 << ". " << menu[i].name << " - $" << menu[i].price << "\n";
    }
    cout << endl;
}

// Function to handle order placement and save it to a file
double placeOrder(MenuItem menu[], int menuSize, MenuItem order[], int &orderSize, const string &fileName) {
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
    
    // Define the Order structure
struct Order {
    std::string name;
    double price;
};

// Function to save the order to a file
double saveOrderToFile(const std::string &fileName, const Order order[], int orderSize, double total){
    std::ofstream file(fileName.c_str(), std::ios::app); // Use .c_str() for C++98 compatibility
    if (file.is_open()) {
        file << "Order placed:\n";
        for (int i = 0; i < orderSize; i++) {
            file << order[i].name << " - $" << order[i].price << "\n";
        }
        file << "Total: $" << total << "\n";
        file << "---------------------\n";
        file.close();
        std::cout << "\nOrder saved to " << fileName << "!\n";
    } else {
        std::cout << "\nError: Unable to open the file to save the order.\n";
    }

    return total;
}

/*
    // Save the order to a file
    ofstream file(fileName, ios::app); // Append mode
    if (file.is_open()) {
        file << "Order placed:\n";
        for (int i = 0; i < orderSize; i++) {
            file << order[i].name << " - $" << order[i].price << "\n";
        }
        file << "Total: $" << total << "\n";
        file << "---------------------\n";
        file.close();
        cout << "\nOrder saved to " << fileName << "!\n";
    } else {
        cout << "\nError: Unable to open the file to save the order.\n";
    }

    return total;
} */



/* Function to validate the name (only alphabets and spaces)
bool isValidName(const string &name) {
<<<<<<< HEAD
	for (size_t i = 0; i < container.size(); ++i) {
    auto& item = container[i];
    

        if (!isalpha(ch) && ch != ' ') {
            return false; 
        }
=======
    for (size_t i = 0; i < name.size(); i++) {
    if (!isalpha(name[i]) && name[i] != ' ') {
        return false;
>>>>>>> 6ae10162d8cc1437ac0e726d26cd126a0cdf309c
    }
}
    return true;
} */

bool isValidName(const std::string &name) {
    for (size_t i = 0; i < name.size(); ++i) {  // Iterate over the string 'name'
        char ch = name[i];                     // Get each character in the string
        if (!isalpha(ch) && ch != ' ') {       // Check if it is not an alphabet or space
            return false;                      // Return false for invalid characters
        }
    }
    return true;  // Return true if all characters are valid
}

// Function to validate the email (should contain @gmail.com)
bool isValidEmail(const string &email) {
    return email.find("@gmail.com") != string::npos;
}

/* // Function to validate the phone number (should contain only digits)
bool isValidPhone(const string &phone) {
    for (char ch : phone) {
        if (!isdigit(ch)) {
            return false;  // Invalid if it contains non-digit characters
        }
    }
    return true;
} */

bool isValidPhone(const std::string &phone) {
    for (size_t i = 0; i < phone.size(); ++i) {
        char ch = phone[i];  // Access each character by index
        if (!isdigit(ch)) {
            return false;    // Invalid if it contains non-digit characters
        }
    }
    return true;  // Return true if all characters are digits
}

// Function to collect and validate user information
void collectUserInfo(User &userInfo) {
    cout << "\nPlease enter your details:\n";

    // Name input and validation
    do {
        cout << "Name: ";
        getline(cin, userInfo.name);
        if (!isValidName(userInfo.name)) {
            cout << "Invalid name! Name should only contain alphabets.\n";
            userInfo.name.clear();  // Clear the input to prompt the user again
        }
    } while (userInfo.name.empty() || !isValidName(userInfo.name));

    // Email input and validation
    do {
        cout << "Email: ";
        getline(cin, userInfo.email);
        if (!isValidEmail(userInfo.email)) {
            cout << "Invalid email! Please enter a valid Gmail address.\n";
            userInfo.email.clear();  // Clear the input to prompt the user again
        }
    } while (userInfo.email.empty() || !isValidEmail(userInfo.email));

    // Phone input and validation
    do {
        cout << "Phone: ";
        getline(cin, userInfo.phone);
        if (!isValidPhone(userInfo.phone)) {
            cout << "Invalid phone number! Phone should contain only digits.\n";
            userInfo.phone.clear();  // Clear the input to prompt the user again
        }
    } while (userInfo.phone.empty() || !isValidPhone(userInfo.phone));

    // Address input and validation
    do {
        cout << "Address: ";
        getline(cin, userInfo.address);
        if (userInfo.address.empty()) {
            cout << "Address cannot be empty!\n";
            userInfo.address.clear();  // Clear the input to prompt the user again
        }
    } while (userInfo.address.empty());

    // If any field is empty, request the user to fill all fields
    if (userInfo.name.empty() || userInfo.email.empty() || userInfo.phone.empty() || userInfo.address.empty()) {
        cout << "\nAll fields are required! Please fill in all the information.\n";
    }
}


// Function to load riddles from a file into arrays
int loadRiddles(const string &filename, string riddles[], string answers[], int maxRiddles) {
    ifstream file(filename); // Use the filename provided
    if (!file) {
        cerr << "Error opening file!" << endl;
        return 0;
    }

    int count = 0;
    string line;
    while (getline(file, line) && count < maxRiddles) {
        size_t delimiter = line.find('|');
        if (delimiter != string::npos) {
            riddles[count] = line.substr(0, delimiter);      // Extract riddle
            answers[count] = line.substr(delimiter + 1);    // Extract answer
            count++;
        }
    }
    file.close();
    return count; // Return the total number of riddles loaded
}

// Function to play the riddles game
void playRiddlesGame(string riddles[], string answers[], int totalRiddles) {
    if (totalRiddles == 0) {
        cout << "No riddles available in the file!" << endl;
        return;
    }

    srand(time(0)); // Seed for randomness
    char choice;
    do {
        int randomIndex = rand() % totalRiddles;

        cout << "\nRiddle: " << riddles[randomIndex] << endl;
        cout << "Your Answer: ";
        string userAnswer;
        getline(cin, userAnswer);

        if (userAnswer == answers[randomIndex]) {
            cout << "Correct!" << endl;
        } else {
            cout << "Wrong! The correct answer was: " << answers[randomIndex] << endl;
        }

        cout << "\nPress 'q' to quit or any other key to continue: ";
        cin >> choice;
        cin.ignore(); // Clear the input buffer
    } while (choice != 'q');
}

// Function to load hints and answers from the file
int loadTeachers(const string &filename, string hints[], string answers[], int maxTeachers) {
    ifstream file(filename);
    if (!file) {
        cerr << "Error opening file!" << endl;
        return 0;
    }

    int count = 0;
    string hint, answer;
    while (count < maxTeachers && getline(file, hint) && getline(file, answer)) {
        hints[count] = hint;   // Store the hint
        answers[count] = answer; // Store the corresponding answer
        count++;
    }
    file.close();
    return count; // Return the number of hints loaded
}

void playTeachersGame(string hints[], string answers[], int totalTeachers) {
    srand(time(0)); // Seed random number generator
    char choice;
    do {
        // Randomly select a hint
        int randomIndex = rand() % totalTeachers;
        cout << "Hint: " << hints[randomIndex] << endl;
        cout << "Your guess: ";
        string userGuess;
        getline(cin, userGuess);

        // Check the user's guess
        if (userGuess == answers[randomIndex]) {
            cout << "Correct! Well done!" << endl;
        } else {
            cout << "Wrong! The correct answer is: " << answers[randomIndex] << endl;
        }

        // Ask if the user wants to continue
        cout << "Do you want to try another hint? (y/n): ";
        cin >> choice;
        cin.ignore(); // Ignore the newline character after entering 'y' or 'n'
    } while (choice == 'y' || choice == 'Y');
}


/*// Main function
int main() {
    cout << "   Welcome to BAM Cafe   " << endl;

    MenuItem menu[9] = {
        {"HUNTER BEEF SANDWICH", 1,590.00},
        {"CRISPY FRIED CHICKEN BURGER", 1,460.00},
        {"FISH & CHIPS", 1,540.00},
        {"PARMESAN CRUSTED CHICKEN", 1,590.00},
        {"BABAR PASTA", 1,760.00},
        {"PASTA ALFREDO CHICKEN", 1,520.00},
        {"PIZZA MARGARITA", 1,540.00},
        {"BAM SPECIAL CHICKEN", 1,590.00},
    };
    int menuSize = sizeof(menu) / sizeof(menu[0]);

    // Display the menu
    displayMenu(menu, menuSize);

    MenuItem order[10]; // Array to store a maximum of 10 ordered items
    int orderSize = 0;

    // File name for storing orders
  // File name for storing orders and customer info
    string fileName = "orders.txt";

    // Place the order
    double total = placeOrder(menu, menuSize, order, orderSize, fileName);

    // Collect customer information
    if (total > 0) {
        User customer;
        collectUserInfo(customer);

        // Save customer info to the file
        ofstream outFile(fileName, ios::app); // Open file in append mode
        if (outFile.is_open()) {
            outFile << "\n--- Customer Information ---\n";
            outFile << "Name: " << customer.name << "\n";
            outFile << "Email: " << customer.email << "\n";
            outFile << "Phone: " << customer.phone << "\n";
            outFile << "Address: " << customer.address << "\n";
            outFile.close();
            cout << "Customer details saved successfully.\n";
        } else {
            cout << "Error saving customer details to the file.\n";
        }

        // Display order summary
        cout << "\nOrder Summary:\n";
        for (int i = 0; i < orderSize; i++) { // Standard for loop for compatibility
            cout << "- " << order[i].name << " - $" << order[i].price << "\n";
        }
        cout << "Total: $" << total << "\n";
    } else {
        cout << "No items ordered.\n";
    }

    // Game options
    // Main menu options
    cout << "\nWelcome to the Fun Games Menu of BAM cafe\n";
    cout << "1. Play the Riddles Game\n";
    cout << "2. Play the Guess the Teacher Game\n";
    cout << "3. Exit\n";
    cout << "Choose an option (1-3): ";

    int menuChoice;
    cin >> menuChoice;
    cin.ignore(); // Clear the input buffer

    switch(menuChoice) {

        case 1: {
            const int MAX_RIDDLES = 100; // Set a maximum limit for riddles
    string riddles[MAX_RIDDLES];
    string answers[MAX_RIDDLES];

    string filename = "riddles.txt";
    int totalRiddles = loadRiddles(filename, riddles, answers, MAX_RIDDLES);

    if (totalRiddles > 0) {
        playRiddlesGame(riddles, answers, totalRiddles);
    } else {
        cout << "Failed to load riddles from the file." << endl;
    }
            break;
        }
        case 2: {
           const int MAX_TEACHERS = 100;
    string hints[MAX_TEACHERS];
    string answers[MAX_TEACHERS];

    int totalTeachers = loadTeachers("teachers.txt", hints, answers, MAX_TEACHERS);
    if (totalTeachers == 0) {
        cout << "No hints loaded. Exiting program." << endl;
        return 1;
    }

    cout << "Welcome to the Guess the Teacher Game!" << endl;
    playTeachersGame(hints, answers, totalTeachers);

    cout << "Thank you for playing!" << endl;
    cout << "Thank you for ordering fro BAM Cafe " << endl ;
    break;
        }
        case 3:
            cout << "------ Thank you for visiting BAM ------";
            break;
        default:
            cout << "Invalid choice! Please select a valid option.\n";
    }

    return 0;
} */

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

    // File name for storing orders and customer info
    string fileName = "orders.txt";

    // Place the order
    double total = placeOrder(menu, menuSize, order, orderSize, fileName);

    // Collect customer information
    if (total > 0) {
        User customer;
        collectUserInfo(customer);

        // Save customer info to the file
        ofstream outFile(fileName, ios::app); // Open file in append mode
        if (outFile.is_open()) {
            outFile << "\n--- Customer Information ---\n";
            outFile << "Name: " << customer.name << "\n";
            outFile << "Email: " << customer.email << "\n";
            outFile << "Phone: " << customer.phone << "\n";
            outFile << "Address: " << customer.address << "\n";
            outFile.close();
            cout << "Customer details saved successfully.\n";
        } else {
            cout << "Error saving customer details to the file.\n";
        }

        // Display order summary
        cout << "\nOrder Summary:\n";
        for (int i = 0; i < orderSize; i++) { // Standard for loop for compatibility
            cout << "- " << order[i].name << " - $" << order[i].price << "\n";
        }
        cout << "Total: $" << total << "\n";
    } else {
        cout << "No items ordered.\n";
    }

    // Main menu options
    cout << "\nWelcome to the Fun Games Menu of BAM cafe\n";
    cout << "1. Play the Riddles Game\n";
    cout << "2. Play the Guess the Teacher Game\n";
    cout << "3. Exit\n";
    cout << "Choose an option (1-3): ";

    int menuChoice;
    cin >> menuChoice;
    cin.ignore(); // Clear the input buffer

    switch(menuChoice) {

        case 1: {
            const int MAX_RIDDLES = 100; // Set a maximum limit for riddles
            string riddles[MAX_RIDDLES];
            string answers[MAX_RIDDLES];

            string filename = "riddles.txt";
            int totalRiddles = loadRiddles(filename, riddles, answers, MAX_RIDDLES);

            if (totalRiddles > 0) {
                playRiddlesGame(riddles, answers, totalRiddles);
            } else {
                cout << "Failed to load riddles from the file." << endl;
            }
            break;
        }

        case 2: {
            const int MAX_TEACHERS = 100;
            string hints[MAX_TEACHERS];
            string answers[MAX_TEACHERS];

            int totalTeachers = loadTeachers("teachers.txt", hints, answers, MAX_TEACHERS);
            if (totalTeachers == 0) {
                cout << "No hints loaded. Exiting program." << endl;
                return 1;
            }

            cout << "Welcome to the Guess the Teacher Game!" << endl;
            playTeachersGame(hints, answers, totalTeachers);

            cout << "Thank you for playing!" << endl;
            cout << "Thank you for ordering from BAM Cafe." << endl;
            break;
        }

        case 3:
            cout << "------ Thank you for visiting BAM ------";
            break;

        default:
            cout << "Invalid choice! Please select a valid option.\n";
    }

    return 0; // End of main function
} // Closing brace for main()

