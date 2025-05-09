#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
#include <algorithm>

using namespace std;


struct MenuItem {
    string name;
    double price;
};


struct User {
    string name;
    string email;
    string phone;
    string address;
};

// Function to display the menu
void displayMenu(MenuItem menu[], int size) {
    cout << "\n--- Menu ---\n";

    for (int i = 0; i < size; i++) {

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
    string input;
    cout << "Enter your choice: ";
    cin >> input; // Read input as string

    // Check if input is a number
    if (all_of(input.begin(), input.end(), ::isdigit)) {
        choice = stoi(input); // Convert string to integer
    } else {
        cout << "Invalid input! Please enter a number" << endl;
        continue;
    }

    if (choice == 0) break;
    if (choice < 1 || choice > menuSize) {
        cout << "Invalid choice! Try again.\n";
        continue;
    }

    // Add the item to the order
    order[orderSize] = menu[choice - 1]; // Store the menu item in the order array
    total += menu[choice - 1].price; // Add item price to the total
    cout << menu[choice - 1].name << " added to your order.\n";
    orderSize++; // Increment the order size
}

    // Save the order to a file
    ofstream file(fileName, ios::app); // Append mode
    if (file.is_open()) {
        file << "\nOrder placed:\n";
        for (int i = 0; i < orderSize; i++) {// Write each item in the order to the file
            file << order[i].name << " - $" << order[i].price << "\n";
        }
        file << "Total: $" << total << "\n";
        file << "---------------------\n";
        file.close();

    } else {
        cout << "\nError: Unable to open the file to save the order.\n";
    }

    return total;// Return the total price of the order
}

// Function to validate the name (only alphabets and spaces)
bool isValidName(const string &name) {

    for (char ch : name) {
        if (!isalpha(ch) && ch != ' ') {
            return false;
        }
    }
    return true;
}

// Function to validate the email (should contain @gmail.com)
bool isValidEmail(const string &email) {
    return email.find("@gmail.com") != string::npos;
}


bool isValidPhone(const string &phone) {

    if (phone.size() != 10 ) {
        return false;
    }

    // Check if the remaining characters are all digits
    for (size_t i = 3; i < phone.size(); ++i) {
        if (!isdigit(phone[i])) {
            return false;        }
    }

    return true;
}

// Function to collect and validate user information
void collectUserInfo(User &userInfo) {
    cin.ignore(); // Clear input buffer
    cout << "\nPlease enter your details:\n";


    do {
        cout << "Name: " ;
        getline(cin, userInfo.name);
        if (!isValidName(userInfo.name)) {
            cout << "Invalid name! Name should only contain alphabets.\n";
        }
    } while (!isValidName(userInfo.name));




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

        if (userInfo.phone.size() != 10 || !isValidPhone(userInfo.phone)) {
            cout << "Invalid phone number!.\n";
        }
    } while (userInfo.phone.size() != 10 || !isValidPhone(userInfo.phone));


    // Address input and validation
    do {
        cout << "Address: ";
        getline(cin, userInfo.address);
        if (userInfo.address.empty()) {// Ensure the address is not empty
            cout << "Address cannot be empty!\n";
        }
    } while (userInfo.address.empty());// Repeat until a valid address is entered
}


// Function to trim leading and trailing spaces

string trimR(const string &str) {
    //size_t store the index of the spaces
	// Find the first non-space character
    size_t first = str.find_first_not_of(' ');
    // Find the last non-space character
    size_t last = str.find_last_not_of(' ');
    // Return the substring between the first and last non-space characters
    return str.substr(first, (last - first + 1));
}

// Function to convert a string to lowercase without using transform
string toLowerCaseR(const string &str) {
    string lowerStr = str;// Create a copy of the input string
    for (char &c : lowerStr) {// Iterate over each character in the string
        c = tolower(c);  // Convert each character to lowercase
    }
    return lowerStr;// Return the lowercase string
}

// Function to load riddles from a file into arrays
int loadRiddles(const string &filename, string riddles[], string answers[], int maxRiddles) {
    ifstream file(filename); // Open the file with the given filename
    if (!file) {// Check if the file could not be opened
        cerr << "Error opening file!" << endl;
        return 0;// Return 0 to indicate failure
    }

    int count = 0;// Initialize the count of riddles
    string line;// Variable to hold each line from the file
    while (getline(file, line) && count < maxRiddles) {// Read lines until the end of file or maxRiddles is reached
        size_t delimiter = line.find('|'); // Find the position of the delimiter '|'
        if (delimiter != string::npos) { // Check if the delimiter exists
                //this checks if the search was successfull

                //extract the part before the delimeter
            riddles[count] = line.substr(0, delimiter);  // Extract the riddle part before the delimiter
        //this will skip the dilimiter and moves one step right to the delimeter
            answers[count] = line.substr(delimiter + 1); // Extract the answer part after the delimiter
            count++;// Increment the count of riddles
        }
    }
    file.close();// Close the file
    return count; // Return the total number of riddles loaded
}

// Function to play the riddles game
void playRiddlesGame(string riddles[], string answers[], int totalRiddles) {
    if (totalRiddles == 0) {// Check if there are no riddles available
        cout << "No riddles available in the file!" << endl;
        return; // Exit the function
    }

    srand(time(0)); // Seed the random number generator with the current time
    char choice;
    do {
        int randomIndex = rand() % totalRiddles;// Generate a random index for the riddle

        cout << "\nRiddle: " << riddles[randomIndex] << endl;// Display the riddle
        cout << "Your Answer: ";
        string userAnswer;// Variable to hold user's answer
        getline(cin, userAnswer);// Get the user's answer

        // Normalize both user answer and the correct answer (lowercase and trimmed)
        string normalizedAnswer = toLowerCaseR(trimR(answers[randomIndex]));
        string normalizedUserAnswer = toLowerCaseR(trimR(userAnswer));

        if (normalizedUserAnswer == normalizedAnswer) {// Compare the normalized answers
            cout << "Correct!" << endl;
        } else {
            cout << "Wrong! The correct answer was: " << answers[randomIndex] << endl;// Display correct answer
        }

        cout << "\nPress 'q' to quit or any other key to continue: ";
        cin >> choice;// Get the user's choice to continue or quit
        cin.ignore(); // Clear the input buffer
    } while (choice != 'q');// Repeat the loop until the user chooses to quit
    cout << "\nThank you for playing! Your order will be there soon." << endl;
}

// Function to trim leading and trailing spaces
string trimT(const string &str) {
    size_t first = str.find_first_not_of(' '); // Find first non-space character
    size_t last = str.find_last_not_of(' ');// Find last non-space character
    return str.substr(first, (last - first + 1));// Return the trimmed string
}

// Function to convert a string to lowercase
string toLowerCaseT(const string &str) {
    string lowerStr = str;// Create a copy of the input string
    transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower); // Convert to lowercase
    return lowerStr;
}

// Function to load hints and answers from the file
int loadTeachers(const string &filename, string hints[], string answers[], int maxTeachers) {
    ifstream file(filename);// Open the file with the given filename
    if (!file) {// Check if the file could not be opened
        cerr << "Error opening file!" << endl;
        return 0;// Return 0 to indicate failure
    }

    int count = 0;// Initialize the count of hints
    string hint, answer;
    while (count < maxTeachers && getline(file, hint) && getline(file, answer)) {// Read hints and answers from the file
        hints[count] = hint;   // Store the hint
        answers[count] = answer; // Store the corresponding answer
        count++;// Increment the count
    }
    file.close(); // Close the file
    return count; // Return the number of hints loaded
}

// Function to play the Teachers' Game
// Function to play the Teachers' Game
void playTeachersGame(string hints[], string answers[], int totalTeachers) {
    // This makes sure whenever you run the program, it will give a different index each time
    srand(time(0)); // Seed random number generator with the current time
    char choice;
    do {
        // Randomly select a hint
        int randomIndex = rand() % totalTeachers; // Generate a random index for the hint
        cout << "Hint: " << hints[randomIndex] << endl; // Display the hint
        cout << "Your guess: ";
        string userGuess; // Variable to hold user's guess
        getline(cin, userGuess); // Get the user's guess

        // Normalize both the correct answer and user guess (lowercase and trimmed)
        string normalizedAnswer = toLowerCaseT(trimT(answers[randomIndex]));
        string normalizedUserGuess = toLowerCaseT(trimT(userGuess));

        // Check the user's guess
        if (normalizedUserGuess == normalizedAnswer) { // Compare the normalized answers
            cout << "Correct! Well done!" << endl;
        } else {
            cout << "Wrong! The correct answer is: " << answers[randomIndex] << endl; // Display correct answer
        }

        // Ask if the user wants to continue
        cout << "\nPress 'q' to quit or any other key to continue: ";
        cin >> choice;
        cin.ignore(); // Ignore the newline character after entering 'q'
    } while (choice != 'q'); // Repeat until the user chooses to quit

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
    int menuSize = sizeof(menu) / sizeof(menu[0]);// Calculate the number of menu items

    // Display the menu
    displayMenu(menu, menuSize);

    MenuItem order[10]; // Array to store a maximum of 10 ordered items
    int orderSize = 0;// Initialize the order size to 0

    // File name for storing orders and customer info
    string fileName = "orders.txt";

    double total = placeOrder(menu, menuSize, order, orderSize, fileName);// Place the order and calculate total

    // Collect customer information
    if (total > 0) {

        cout << "\nOrder saved!\n";

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
            outFile.close();// Close the file
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
        cout << "Would you like to Play Games in the mean time?\n\n";
        cout << "If yes you can choose from the following options ...\n" ;


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
    string riddles[MAX_RIDDLES];// Array to store riddles
    string answers[MAX_RIDDLES];// Array to store answers

    string filename = "riddles.txt";// File containing riddles
    int totalRiddles = loadRiddles(filename, riddles, answers, MAX_RIDDLES);// Load riddles from the file

    if (totalRiddles > 0) {// If riddles are loaded successfully
        playRiddlesGame(riddles, answers, totalRiddles); // Play the riddles game
    } else {
        cout << "Failed to load riddles from the file." << endl;
    }
            break;
        }
    case 2 : {
        const int MAX_TEACHERS = 100;// Set a maximum limit for hints
    string hints[MAX_TEACHERS];// Array to store hints
    string answers[MAX_TEACHERS];

    int totalTeachers = loadTeachers("teachers.txt", hints, answers, MAX_TEACHERS);// Load hints and answers
    if (totalTeachers == 0) {// If no hints are loaded
        cout << "No hints loaded. Exiting program." << endl;
        return 1;// Exit the program
    }

    cout << "Welcome to the Guess the Teacher Game!\n" << endl;
    playTeachersGame(hints, answers, totalTeachers);// Play the Guess the Teacher game

    cout << "Thank you for playing!\n" << endl;
    cout << "Thank you for ordering from BAM Cafe.\nYour order will be there soon\n" << endl;
    break;
    }

        case 3:
            cout << "------ Thank you for visiting BAM ------";// Exit message
            break;

        default:
            cout << "Invalid choice! Please select a valid option.\n";// Handle invalid input
    }
     } else {
        cout << "\nNo order placed.\n";
        cout << "Have a nice Day ! \n" ;
    }

    return 0; // End of main function
}
