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
    string name;   // Name of the menu item
    double price;  // Price of the menu item
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


/* Function to validate the name (only alphabets and spaces)
bool isValidName(const string &name) {
	for (size_t i = 0; i < container.size(); ++i) {
    auto& item = container[i];
    

        if (!isalpha(ch) && ch != ' ') {
            return false; 
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
    do {
        cout << "\nPlease enter your details:\n";

        cout << "Name: ";
        getline(cin, userInfo.name);
        if (!isValidName(userInfo.name)) {
            cout << "Invalid name! Name should only contain alphabets.\n";
            userInfo.name.clear();  // Clear the input to prompt the user again
            getline(cin, userInfo.name);
        }

        cout << "Email: ";
        getline(cin, userInfo.email);
        if (!isValidEmail(userInfo.email)) {
            cout << "Invalid email! Please enter a valid Gmail address.\n";
            userInfo.email.clear();  // Clear the input to prompt the user again
            getline(cin, userInfo.email);
        }

        cout << "Phone: ";
        getline(cin, userInfo.phone);
        if (!isValidPhone(userInfo.phone)) {
            cout << "Invalid phone number! Phone should contain only digits.\n";
            userInfo.phone.clear();  // Clear the input to prompt the user again
            getline(cin, userInfo.phone);
        }

        cout << "Address: ";
        getline(cin, userInfo.address);
        if (userInfo.address.empty()) {
            cout << "Address cannot be empty!\n";
            userInfo.address.clear();  // Clear the input to prompt the user again
            getline(cin, userInfo.address);
        }

        if (userInfo.name.empty() || userInfo.email.empty() || userInfo.phone.empty() || userInfo.address.empty()) {
            cout << "\nAll fields are required! Please fill in all the information.\n";
        }

    } while (userInfo.name.empty() || userInfo.email.empty() || userInfo.phone.empty() || userInfo.address.empty());
}

// Function to play a riddles guessing game
void riddlesGame() {
    // Array of riddles and their corresponding answers
    const string riddles[][2] = {
        {"I speak without a mouth and hear without ears. I have no body, but I come alive with wind. What am I?", "echo"},
        {"The more of me you take, the more you leave behind. What am I?", "footsteps"},
        {"I have keys but no locks. I have space but no room. You can enter but you can't go outside. What am I?", "keyboard"}
    };

    // Number of riddles in the array
    const int riddleCount = sizeof(riddles) / sizeof(riddles[0]);

    // Seed the random number generator
    srand(time(0));

    // Select a random riddle
    int randomIndex = rand() % riddleCount;

    // Display the riddle
    cout << "\nRiddle: " << riddles[randomIndex][0] << endl;
    cout << "Your answer: ";
    string userAnswer;
    cin.ignore();
    getline(cin, userAnswer); // Get the user's answer

    // Check if the answer is correct (case-insensitive)
    transform(userAnswer.begin(), userAnswer.end(), userAnswer.begin(), ::tolower);
    if (userAnswer == riddles[randomIndex][1]) {
        cout << "Correct! Well done!\n";
    } else {
        cout << "Wrong! The correct answer was: " << riddles[randomIndex][1] << ".\n";
    }
}
// Function to play "Guess the Teacher" game
void guessTeacherGame() {
    const int MAX_TEACHERS = 100; // Maximum number of teacher names
    string teachers[MAX_TEACHERS]; // Array to store teacher names
    int teacherCount = 0; // Counter for the number of teachers

    // Open the file containing the list of teachers
    ifstream file("teachers_list.txt");

    // Check if the file was successfully opened
    if (!file.is_open()) {
        cerr << "Error opening teachers list file." << endl;
        return;
    }

    // Read teacher names into the array from the file
    while (getline(file, teachers[teacherCount]) && teacherCount < MAX_TEACHERS) {
        teacherCount++;
    }

    file.close(); // Close the file after reading

    // Check if the file contained any teacher names
    if (teacherCount == 0) {
        cout << "No teachers found in the list!" << endl;
        return;
    }

    // Select a random teacher from the list
    srand(time(0));
    int randomIndex = rand() % teacherCount;

    // Display the list of teachers
    cout << "\nGuess the teacher's name from the following list:\n";
    for (int i = 0; i < teacherCount; ++i) {
        cout << "- " << teachers[i] << endl;
    }

    // Prompt the user for their guess
    cout << "\nYour guess: ";
    string guess;
    cin >> guess;

    // Check if the guess matches the randomly selected teacher's name
    if (guess == teachers[randomIndex]) {
        cout << "Correct! The teacher is " << teachers[randomIndex] << ".\n";
    } else {
        cout << "Wrong! The teacher was " << teachers[randomIndex] << ".\n";
    }

    //  questions related to subjects
    cout << "\nLet's test your knowledge of the teachers:\n";

    cout << "1. This teacher is a wizard of OOP, often teaching through real-world analogies. Who is it? ";
    cin.ignore(); // Clear the input buffer
    string oopAnswer;
    getline(cin, oopAnswer);
    if (oopAnswer == "Sir Farzeen" || oopAnswer == "sir farzeen") {
        cout << "Correct! Sir Farzeen simplifies OOP concepts masterfully.\n";
    } else {
        cout << "Wrong! The correct answer is Sir Farzeen.\n";
    }

    cout << "2. Known for making ICT classes engaging with practical applications, who is this teacher? ";
    string ictAnswer;
    getline(cin, ictAnswer);
    if (ictAnswer == "Miss Sania" || ictAnswer == "miss sania") {
        cout << "Correct! Miss Sania excels in making ICT fun.\n";
    } else {
        cout << "Wrong! The correct answer is Miss Sania.\n";
    }

    cout << "3. This math genius often explains the trickiest calculus problems with ease. Who is it? ";
    string mathAnswer;
    getline(cin, mathAnswer);
    if (mathAnswer == "Sir Imran" || mathAnswer == "sir imran") {
        cout << "Correct! Sir Imran is a math wizard.\n";
    } else {
        cout << "Wrong! The correct answer is Sir Imran.\n";
    }

    cout << "4. Who introduces PF concepts with relatable examples, making coding a breeze? ";
    string pfAnswer;
    getline(cin, pfAnswer);
    if (pfAnswer == "Sir Mansoor" || pfAnswer == "sir mansoor") {
        cout << "Correct! Sir Mansoor is excellent at teaching PF.\n";
    } else {
        cout << "Wrong! The correct answer is Sir Mansoor.\n";
    }
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
    // Main menu options
    cout << "\nWelcome to the Fun Games Menu of BAM cafe\n";
    cout << "1. Place Order and Provide Details\n";
    cout << "2. Play the Riddles Game\n";
    cout << "3. Play the Guess the Teacher Game\n";
    cout << "4. Exit\n";
    cout << "Choose an option (1-4): ";

    int menuChoice;
    cin >> menuChoice;
    cin.ignore(); // Clear the input buffer

    switch(menuChoice) {
        case 1: {
            // Collect user info
            User userInfo;  // Declare a User structure to hold the information
            collectUserInfo(userInfo);

            // Display the collected information
            cout << "\nCollected Information:\n";
            cout << "Name: " << userInfo.name << endl;
            cout << "Email: " << userInfo.email << endl;
            cout << "Phone: " << userInfo.phone << endl;
            cout << "Address: " << userInfo.address << endl;

            // Display a thank-you message
            cout << "\nThank you, " << userInfo.name << "! Your order has been placed successfully.\n";
            cout << "We will deliver it to " << userInfo.address << ".\n";

            // Ask if the user wants to play a game while waiting
            cout << "\nWould you like to play a game while your order is being prepared? (yes/no): ";
            string playGame;
            cin.ignore(); // Clear the input buffer
            getline(cin, playGame);

            if (playGame == "yes" || playGame == "Yes") {
                cout << "\nWhich game would you like to play?\n";
                cout << "1. Riddles Game\n";
                cout << "2. Guess the Teacher Game\n";
                cout << "Choose an option (1-2): ";

                int gameChoice;
                cin >> gameChoice;
                cin.ignore(); // Clear the input buffer

                if (gameChoice == 1) {
                    riddlesGame(); // Call the riddles game function
                } else if (gameChoice == 2) {
                    guessTeacherGame(); // Call the guess the teacher game function
                } else {
                    cout << "Invalid choice! Returning to the main menu.\n";
                }
            } else {
                cout << "\n====== Alright, enjoy your time ======\n";
            }
            break;
        }
        case 2: {
            riddlesGame(); // Call the riddles game function
            break;
        }
        case 3: {
            guessTeacherGame(); // Call the guess the teacher game function
            break;
        }
        case 4:
            cout << "------ Thank you for visiting BAM ------";
            break;
        default:
            cout << "Invalid choice! Please select a valid option.\n";
    }

    return 0;
}

