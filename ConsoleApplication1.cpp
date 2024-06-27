#include <iostream>
#include <conio.h>  // For _getch() to get single character input without Enter key
#define NOMINMAX  // Prevent windows.h from defining min and max macros
#include <windows.h>  // For Windows console color control
#include <string>
#include <vector>
#include <numeric>
#include <stdexcept>  // For standard exceptions
#include <limits>  // For numeric limits

// SystemOutput class to manage printing to the console and setting text color
class SystemOutput {
public:
    // Enum class for console text colors
    enum class Color {
        Default = 7,
        Red = 12,
        Green = 10,
        Blue = 9,
        Yellow = 14,
        Cyan = 11,
        Magenta = 13
    };

    // Set the console text color
    static void setColor(Color color) {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, static_cast<WORD>(color));
    }

    // Print a message to the console with an optional color
    static void print(const std::string& message, Color color = Color::Default) {
        setColor(color);
        std::cout << message << std::endl;
        setColor(Color::Default);  // Reset to default color
    }

    // Print a fancy message to the console with an optional color
    static void printFancy(const std::string& message, Color color = Color::Default) {
        setColor(color);
        std::cout << "=============================" << std::endl;
        std::cout << message << std::endl;
        std::cout << "=============================" << std::endl;
        setColor(Color::Default);  // Reset to default color
    }
};

// UserInput class to handle all user inputs
class UserInput {
public:
    // Get a single character input from the user
    static char getChar() {
        return _getch();
    }

    // Get a string input from the user
    static std::string getString() {
        std::string input;
        std::getline(std::cin, input);
        return input;
    }

    // Get a double input from the user with validation
    static double getDouble() {
        double input;
        while (!(std::cin >> input)) {
            std::cin.clear(); // clear the error flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard invalid input
            SystemOutput::print("Invalid input. Please enter a valid number: ", SystemOutput::Color::Red);
        }
        return input;
    }

    // Get a vector of doubles from the user with validation
    static std::vector<double> getDoubleVector(int size) {
        std::vector<double> vec(size);
        for (int i = 0; i < size; ++i) {
            vec[i] = getDouble();
        }
        return vec;
    }
};

// ArithmeticWorker class to perform arithmetic operations
class ArithmeticWorker {
public:
    // Perform addition
    double add(double a, double b) { return a + b; }

    // Perform subtraction
    double subtract(double a, double b) { return a - b; }

    // Perform multiplication
    double multiply(double a, double b) { return a * b; }

    // Perform division with validation for division by zero
    double divide(double a, double b) {
        if (b == 0) { throw std::invalid_argument("Division by zero"); }
        return a / b;
    }

    // Perform the arithmetic operation based on user input
    void performArithmetic(char operation, double a, double b) {
        double result = 0;
        switch (operation) {
        case '1':
            result = add(a, b);
            SystemOutput::print("Result: " + std::to_string(result), SystemOutput::Color::Cyan);
            break;
        case '2':
            result = subtract(a, b);
            SystemOutput::print("Result: " + std::to_string(result), SystemOutput::Color::Cyan);
            break;
        case '3':
            result = multiply(a, b);
            SystemOutput::print("Result: " + std::to_string(result), SystemOutput::Color::Cyan);
            break;
        case '4':
            try {
                result = divide(a, b);
                SystemOutput::print("Result: " + std::to_string(result), SystemOutput::Color::Cyan);
            }
            catch (const std::invalid_argument& e) {
                SystemOutput::print(e.what(), SystemOutput::Color::Red);
            }
            break;
        default:
            SystemOutput::print("Invalid operation.", SystemOutput::Color::Red);
            break;
        }
    }
};

// LinearAlgebraWorker class to perform linear algebra operations
class LinearAlgebraWorker {
public:
    // Calculate the dot product of two vectors
    double dotProduct(const std::vector<double>& v1, const std::vector<double>& v2) {
        if (v1.size() != v2.size()) {
            throw std::invalid_argument("Vectors must be of the same size");
        }
        double result = std::inner_product(v1.begin(), v1.end(), v2.begin(), 0.0);
        return result;
    }

    // Handle the dot product operation with user inputs
    void performDotProduct() {
        SystemOutput::print("Enter the size of the vectors: ");
        int size;
        std::cin >> size;

        SystemOutput::print("Enter elements of the first vector: ");
        std::vector<double> v1 = UserInput::getDoubleVector(size);

        SystemOutput::print("Enter elements of the second vector: ");
        std::vector<double> v2 = UserInput::getDoubleVector(size);

        try {
            double result = dotProduct(v1, v2);
            SystemOutput::print("Dot Product Result: " + std::to_string(result), SystemOutput::Color::Cyan);
        }
        catch (const std::invalid_argument& e) {
            SystemOutput::print(e.what(), SystemOutput::Color::Red);
        }
    }
};

// StatisticsWorker class to perform statistical operations
class StatisticsWorker {
public:
    // Calculate the mean of a dataset
    double mean(const std::vector<double>& data) {
        if (data.empty()) {
            throw std::invalid_argument("Data set cannot be empty");
        }
        return std::accumulate(data.begin(), data.end(), 0.0) / data.size();
    }

    // Handle the mean calculation operation with user inputs
    void performMean() {
        SystemOutput::print("Enter the size of the data set: ");
        int size;
        std::cin >> size;

        SystemOutput::print("Enter elements of the data set: ");
        std::vector<double> data = UserInput::getDoubleVector(size);

        try {
            double result = mean(data);
            SystemOutput::print("Mean Result: " + std::to_string(result), SystemOutput::Color::Cyan);
        }
        catch (const std::invalid_argument& e) {
            SystemOutput::print(e.what(), SystemOutput::Color::Red);
        }
    }
};

// ScreenManager class to handle the different screens and formats their display output
class ScreenManager {
public:
    // Display the welcome screen
    void displayWelcomeScreen() {
        clearScreen();
        SystemOutput::print("Welcome to Universal Calculator", SystemOutput::Color::Green);
        SystemOutput::print("This program offers various mathematical functionalities including:", SystemOutput::Color::Default);
        SystemOutput::print("1. Basic Arithmetic (Addition, Subtraction, Multiplication, Division)", SystemOutput::Color::Default);
        SystemOutput::print("2. Linear Algebra (Vector and Matrix operations)", SystemOutput::Color::Default);
        SystemOutput::print("3. Calculus (Differentiation and Integration)", SystemOutput::Color::Default);
        SystemOutput::print("4. Statistics (Mean, Variance, Standard Deviation)", SystemOutput::Color::Default);
        SystemOutput::print("5. Probability (Random Sampling)", SystemOutput::Color::Default);
        SystemOutput::print("6. Machine Learning (Activation and Loss Functions)", SystemOutput::Color::Default);
        std::cout << "\n\nPress any key to continue..." << std::endl;
        UserInput::getChar();
    }

    // Display the main menu
    void displayMainMenu() {
        clearScreen();
        SystemOutput::print("Main Menu", SystemOutput::Color::Green);
        SystemOutput::print("1. Use the calculator", SystemOutput::Color::Default);
        SystemOutput::print("2. Show examples", SystemOutput::Color::Default);
        SystemOutput::print("3. Exit program", SystemOutput::Color::Default);
    }

    // Display the calculator menu
    void displayCalculatorMenu() {
        clearScreen();
        SystemOutput::print("Calculator Menu", SystemOutput::Color::Green);
        SystemOutput::print("Choose a math group:", SystemOutput::Color::Default);
        SystemOutput::print("1. Basic Arithmetic", SystemOutput::Color::Default);
        SystemOutput::print("2. Linear Algebra", SystemOutput::Color::Default);
        SystemOutput::print("3. Calculus", SystemOutput::Color::Default);
        SystemOutput::print("4. Statistics", SystemOutput::Color::Default);
        SystemOutput::print("5. Probability", SystemOutput::Color::Default);
        SystemOutput::print("6. Machine Learning", SystemOutput::Color::Default);
    }

    // Display the options for arithmetic operations
    void displayArithmeticFunctions() {
        SystemOutput::print("  Basic Arithmetic Functions:", SystemOutput::Color::Default);
        SystemOutput::print("    1. Addition (a + b)", SystemOutput::Color::Default);
        SystemOutput::print("    2. Subtraction (a - b)", SystemOutput::Color::Default);
        SystemOutput::print("    3. Multiplication (a * b)", SystemOutput::Color::Default);
        SystemOutput::print("    4. Division (a / b)", SystemOutput::Color::Default);
        std::cout << "Choose an operation: ";
    }

    // Display the options for linear algebra operations
    void displayLinearAlgebraFunctions() {
        SystemOutput::print("  Linear Algebra Functions:", SystemOutput::Color::Default);
        SystemOutput::print("    1. Vector Dot Product (v1 · v2)", SystemOutput::Color::Default);
    }

    // Display the options for calculus operations
    void displayCalculusFunctions() {
        SystemOutput::print("  Calculus Functions:", SystemOutput::Color::Default);
        SystemOutput::print("    1. Differentiation (f'(x))", SystemOutput::Color::Default);
        SystemOutput::print("    2. Integration (∫f(x)dx)", SystemOutput::Color::Default);
    }

    // Display the options for statistics operations
    void displayStatisticsFunctions() {
        SystemOutput::print("  Statistics Functions:", SystemOutput::Color::Default);
        SystemOutput::print("    1. Mean (average)", SystemOutput::Color::Default);
    }

    // Display the options for probability operations
    void displayProbabilityFunctions() {
        SystemOutput::print("  Probability Functions:", SystemOutput::Color::Default);
        SystemOutput::print("    1. Random Sampling", SystemOutput::Color::Default);
    }

    // Display the options for machine learning operations
    void displayMachineLearningFunctions() {
        SystemOutput::print("  Machine Learning Functions:", SystemOutput::Color::Default);
        SystemOutput::print("    1. ReLU (max(0, x))", SystemOutput::Color::Default);
        SystemOutput::print("    2. Sigmoid (1 / (1 + exp(-x)))", SystemOutput::Color::Default);
        SystemOutput::print("    3. Tanh (tanh(x))", SystemOutput::Color::Default);
    }

    // Display the details for the chosen calculator function
    void displayCalculatorFunctionDetails(char choice) {
        clearScreen();
        switch (choice) {
        case '1':
            displayArithmeticFunctions();
            handleArithmeticInput();
            break;
        case '2':
            displayLinearAlgebraFunctions();
            handleLinearAlgebraInput();
            break;
        case '3':
            displayCalculusFunctions();
            handleCalculusInput();
            break;
        case '4':
            displayStatisticsFunctions();
            handleStatisticsInput();
            break;
        case '5':
            displayProbabilityFunctions();
            handleProbabilityInput();
            break;
        case '6':
            displayMachineLearningFunctions();
            handleMachineLearningInput();
            break;
        default:
            SystemOutput::print("Invalid choice.", SystemOutput::Color::Red);
            return;
        }
    }

    // Handle user input for arithmetic operations
    void handleArithmeticInput() {
        char operation = UserInput::getChar();
        std::cout << "Enter first number: ";
        double a = UserInput::getDouble();
        std::cout << "Enter second number: ";
        double b = UserInput::getDouble();

        ArithmeticWorker arithmeticWorker;
        arithmeticWorker.performArithmetic(operation, a, b);

        std::cout << "\n\n\nPress any key to return to main menu..." << std::endl;
        UserInput::getChar();
    }

    // Handle user input for linear algebra operations
    void handleLinearAlgebraInput() {
        LinearAlgebraWorker linearAlgebraWorker;
        linearAlgebraWorker.performDotProduct();

        std::cout << "\n\n\nPress any key to return to main menu..." << std::endl;
        UserInput::getChar();
    }

    // Handle user input for calculus operations
    void handleCalculusInput() {
        SystemOutput::print("Calculus functionality not implemented yet.", SystemOutput::Color::Yellow);

        std::cout << "\n\n\nPress any key to return to main menu..." << std::endl;
        UserInput::getChar();
    }

    // Handle user input for statistics operations
    void handleStatisticsInput() {
        StatisticsWorker statisticsWorker;
        statisticsWorker.performMean();

        std::cout << "\n\n\nPress any key to return to main menu..." << std::endl;
        UserInput::getChar();
    }

    // Handle user input for probability operations
    void handleProbabilityInput() {
        SystemOutput::print("Probability functionality not implemented yet.", SystemOutput::Color::Yellow);

        std::cout << "\n\n\nPress any key to return to main menu..." << std::endl;
        UserInput::getChar();
    }

    // Handle user input for machine learning operations
    void handleMachineLearningInput() {
        SystemOutput::print("Machine Learning functionality not implemented yet.", SystemOutput::Color::Yellow);

        std::cout << "\n\n\nPress any key to return to main menu..." << std::endl;
        UserInput::getChar();
    }

    // Display the show examples screen
    void displayShowExamplesScreen() {
        clearScreen();
        SystemOutput::print("Examples of Calculator Usage:", SystemOutput::Color::Cyan);
        SystemOutput::print("1. Addition: 3 + 4 = 7", SystemOutput::Color::Default);
        SystemOutput::print("2. Differentiation: d/dx (x^2) at x = 2 is 4", SystemOutput::Color::Default);
        SystemOutput::print("3. Mean: Average of [1, 2, 3] is 2", SystemOutput::Color::Default);
        std::cout << "\n\nPress any key to return to main menu..." << std::endl;
        UserInput::getChar();
    }

    // Clear the console screen
    void clearScreen() {
        system("cls");
    }
};

int main() {
    ScreenManager screenManager;

    screenManager.displayWelcomeScreen();

    bool running = true;
    while (running) {
        screenManager.displayMainMenu();

        char choice = UserInput::getChar();
        switch (choice) {
        case '1':
            screenManager.displayCalculatorMenu();
            choice = UserInput::getChar();
            screenManager.displayCalculatorFunctionDetails(choice);
            break;
        case '2':
            screenManager.displayShowExamplesScreen();
            break;
        case '3':
            running = false;
            break;
        default:
            SystemOutput::print("Invalid choice, please try again.", SystemOutput::Color::Red);
            break;
        }
    }

    return 0;
}
