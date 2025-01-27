#include <iostream>  // Handles input/output operations
#include <string>    // For string operations
#include <ctime>     // Time manipulation for random number generation
#include <fstream>   // For file operations
#include <cstdlib>   // Provides std::srand and std::rand
#include <algorithm> //transform keyword

using namespace std;

// Struct for Menu Item
struct MenuItem {
    string name;
    double price;
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
    // Loop through each menu item
    for (int i = 0; i < size; ++i) {
    // Display item number, name, and price	
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
    // Use a while loop here for indefinite iteration since we allow the user to keep adding items until they enter 0
    while (true) {
        try {
            cout << "Enter your choice: ";
            cin >> choice;

            // Check if the input is invalid
            if (cin.fail()) {
                throw invalid_argument("Invalid input! Please enter a number.");
            }

            if (choice == 0) break;// Exit the loop when user enters 0 to finish ordering
           
            if (choice < 1 || choice > menuSize) { // Ensure choice is within valid range
                cout << "Invalid choice! Try again.\n";
                continue;// Skip the current iteration and prompt again
            }

            // Add the item to the order
            order[orderSize] = menu[choice - 1];// Store the menu item in the order array
            total += menu[choice - 1].price;// Add item price to the total
            cout << menu[choice - 1].name << " added to your order.\n";
            orderSize++;// Increment the order size

        } catch (const invalid_argument &e) {
            // Handle exceptions for invalid input
            cout << e.what() << endl;
            cin.clear();            // Clear the error flag
            cin.ignore(1000, '\n'); // Discard invalid input
        }
    }

    // Save the order to a file
    ofstream file(fileName, ios::app); // Append mode
    if (file.is_open()) {// Check if the file is successfully opened
        file << "\nOrder placed:\n";
        for (int i = 0; i < orderSize; i++) {// Write each item in the order to the file
            file << order[i].name << " - $" << order[i].price << "\n";
        }
        file << "Total: $" << total << "\n";
        file << "---------------------\n";
        file.close();
        cout << "\nOrder saved!\n";
    } else {
        cout << "\nError: Unable to open the file to save the order.\n";
    }

    return total;// Return the total price of the order
}

// Function to validate the name (only alphabets and spaces)
bool isValidName(const string &name) {
	// Loop through each character
    for (char ch : name) {
        if (!isalpha(ch) && ch != ' ') {// Check if the character is not a letter or space
            return false;// Invalid name if any non-alphabetic character is found
        }
    }
    return true;// Name is valid
}

// Function to validate the email (should contain @gmail.com)
bool isValidEmail(const string &email) {
    return email.find("@gmail.com") != string::npos;// Check if email contains @gmail.com
}

// Function to validate the phone number (should start with +92 and have 13 digits)
bool isValidPhone(const string &phone) {
    // Check if the phone number starts with +92 and has 13 characters
    if (phone.size() != 10 ) {
        return false;
    }

    // Check if the remaining characters are all digits
    for (size_t i = 3; i < phone.size(); ++i) {// Loop through each character
        if (!isdigit(phone[i])) { // Check if the character is not a digit
            return false;// Invalid if any non-digit is found
        }
    }

    return true;// Phone number is valid
}

// Function to collect and validate user information
void collectUserInfo(User &userInfo) {
    cin.ignore(); // Clear input buffer
    cout << "\nPlease enter your details:\n";

    // Name input and validation
    do {
        cout << "Name: "
        getline(cin, userInfo.name);// Get full name from user
        if (!isValidName(userInfo.name)) {// Validate name
            cout << "Invalid name! Name should only contain alphabets.\n";
        }
    } while (!isValidName(userInfo.name));    // Repeat until a valid name is entered
    // Repeat until a valid email is entered


    // Email input and validation
    do {
        cout << "Email: ";
        getline(cin, userInfo.email);
        if (!isValidEmail(userInfo.email)) {
            cout << "Invalid email! Please enter a valid Gmail address.\n";
        }
    } while (!isValidEmail(userInfo.email));

    // Phone input and validation
    do {
        cout << "Phone : +92";
        getline(cin, userInfo.phone);
        // Ensure the input is exactly 10 digits, with the +92 part already implied
        if (userInfo.phone.size() != 10 || !isValidPhone(userInfo.phone)) {
            cout << "Invalid phone number!.\n";
        }
    } while (userInfo.phone.size() != 10 || !isValidPhone(userInfo.phone));// Repeat until a valid phone number is entered


    // Address input and validation
    do {
        cout << "Address: ";
        getline(cin, userInfo.address);
        if (userInfo.address.empty()) {
            cout << "Address cannot be empty!\n";
        }
    } while (userInfo.address.empty());
}


// Function to trim leading and trailing spaces
string trimR(const string &str) {
    size_t first = str.find_first_not_of(' ');
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}

// Function to convert a string to lowercase without using transform
string toLowerCaseR(const string &str) {
    string lowerStr = str;
    for (char &c : lowerStr) {
        c = tolower(c);  // Convert each character to lowercase
    }
    return lowerStr;
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

        // Normalize both user answer and the correct answer (lowercase and trimmed)
        string normalizedAnswer = toLowerCaseR(trimR(answers[randomIndex]));
        string normalizedUserAnswer = toLowerCaseR(trimR(userAnswer));

        if (normalizedUserAnswer == normalizedAnswer) {
            cout << "Correct!" << endl;
        } else {
            cout << "Wrong! The correct answer was: " << answers[randomIndex] << endl;
        }

        cout << "\nPress 'q' to quit or any other key to continue: ";
        cin >> choice;
        cin.ignore(); // Clear the input buffer
    } while (choice != 'q');
    cout << "\nThank you for playing! Your order will be there soon." << endl;
}

// Function to trim leading and trailing spaces
string trimT(const string &str) {
    size_t first = str.find_first_not_of(' ');
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}

// Function to convert a string to lowercase
string toLowerCaseT(const string &str) {
    string lowerStr = str;
    transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
    return lowerStr;
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

// Function to play the Teachers' Game
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

        // Normalize both the correct answer and user guess (lowercase and trimmed)
        string normalizedAnswer = toLowerCaseT(trimT(answers[randomIndex]));
        string normalizedUserGuess = toLowerCaseT(trimT(userGuess));

        // Check the user's guess
        if (normalizedUserGuess == normalizedAnswer) {
            cout << "Correct! Well done!" << endl;
        } else {
            cout << "Wrong! The correct answer is: " << answers[randomIndex] << endl;
        }

        // Ask if the user wants to continue
        cout << "\nPress 'q' to quit or any other key to continue: ";
        cin >> choice;
        cin.ignore(); // Ignore the newline character after entering 'q'
    } while (choice != 'q');

    cout << "\nThank you for playing! Your order will be there soon." << endl;
}


// Main function
int main() {
    cout << "   Welcome to BAM Cafe   " << endl;

    MenuItem menu[8] = {
        {"HUNTER BEEF SANDWICH", 1590.00},
        {"CRISPY FRIED CHICKEN BURGER", 1460.00},
        {"FISH & CHIPS", 1540.00},
        {"PARMESAN CRUSTED CHICKEN", 1590.00},
        {"BABAR PASTA", 1760.00},
        {"PASTA ALFREDO CHICKEN", 1520.00},
        {"PIZZA MARGARITA", 1540.00},
        {"BAM SPECIAL CHICKEN", 1590.00}
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
            cout << "Details saved successfully.\n";
        } else {
            cout << "Error saving customer details to the file.\n";
        }

        // Display order summary
        cout << "\nOrder Summary:\n";
        for (int i = 0; i < orderSize; ++i) {
            cout << order[i].name << " - $" << order[i].price << "\n";
        }
        cout << "Total: $" << total << "\n";
        cout << "\nYour Order will take approx 45 Minutes !\n" ;
        cout << "Would you like to Play Games in the mean time,\n\n";
        cout << "If yes you can choose from the following options ...\n" ;
    } else {
        cout << "No order placed.\n";
    }

     // Main menu options
    cout << "\nWelcome to the Fun Games Menu of BAM cafe\n\n";
    cout << "1. Play the Riddles Game\n";
    cout << "2. Play the Guess the Teacher Game\n";
    cout << "3. Exit\n\n";
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
    case 2 : {
        const int MAX_TEACHERS = 100;
    string hints[MAX_TEACHERS];
    string answers[MAX_TEACHERS];

    int totalTeachers = loadTeachers("teachers.txt", hints, answers, MAX_TEACHERS);
    if (totalTeachers == 0) {
        cout << "No hints loaded. Exiting program." << endl;
        return 1;
    }

    cout << "Welcome to the Guess the Teacher Game!\n" << endl;
    playTeachersGame(hints, answers, totalTeachers);

    cout << "Thank you for playing!\n" << endl;
    cout << "Thank you for ordering from BAM Cafe.\nYour order will be there soon\n" << endl;
    break;
    }

        case 3:
            cout << "------ Thank you for visiting BAM ------";
            break;

        default:
            cout << "Invalid choice! Please select a valid option.\n";
    }

    return 0; // End of main function
}


