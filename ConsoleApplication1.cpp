#include <iostream>
#include <conio.h>  // For _getch() to get single character input without Enter key
#define NOMINMAX  // Prevent windows.h from defining min and max macros
#include <windows.h>  // For Windows console color control
#include <string>
#include <vector>
#include <numeric>
#include <cmath>
#include <functional>
#include <memory>
#include <random>
#include <algorithm>

// Structures to hold data
struct AlignedDataA {
    int a;
    double b;
};

struct AlignedDataB {
    char c;
    float d;
};

// DataManager class to manage shared data structures
class DataManager {
private:
    std::shared_ptr<AlignedDataA> dataA;
    std::shared_ptr<AlignedDataB> dataB;

public:
    DataManager()
        : dataA(std::make_shared<AlignedDataA>()), dataB(std::make_shared<AlignedDataB>()) {
        dataA->a = 0;
        dataA->b = 0.0;
        dataB->c = '\0';
        dataB->d = 0.0f;
    }

    void setDataA(int a, double b) {
        dataA->a = a;
        dataA->b = b;
    }

    std::shared_ptr<AlignedDataA> getDataA() const {
        return dataA;
    }

    void setDataB(char c, float d) {
        dataB->c = c;
        dataB->d = d;
    }

    std::shared_ptr<AlignedDataB> getDataB() const {
        return dataB;
    }

    void printData() const {
        std::cout << "DataA: a = " << dataA->a << ", b = " << dataA->b << std::endl;
        std::cout << "DataB: c = " << dataB->c << ", d = " << dataB->d << std::endl;
    }
};

// ArithmeticWorker class to perform arithmetic operations
class ArithmeticWorker {
private:
    std::shared_ptr<DataManager> dataManager;

public:
    ArithmeticWorker(std::shared_ptr<DataManager> dm) : dataManager(dm) {}

    void performArithmetic() {
        auto data = dataManager->getDataA();
        std::cout << "Performing Arithmetic Operation: Addition" << std::endl;
        data->a += 10;
        data->b *= 2;
        dataManager->setDataA(data->a, data->b);
        dataManager->printData();
    }
};

// LinearAlgebraWorker class to perform linear algebra operations
class LinearAlgebraWorker {
private:
    std::shared_ptr<DataManager> dataManager;

public:
    LinearAlgebraWorker(std::shared_ptr<DataManager> dm) : dataManager(dm) {}

    void performLinearAlgebra() {
        auto data = dataManager->getDataB();
        std::cout << "Performing Linear Algebra Operation: Scalar Multiplication" << std::endl;
        data->c = 'Z';
        data->d += 3.14f;
        dataManager->setDataB(data->c, data->d);
        dataManager->printData();
    }
};

// StatisticsWorker class to perform statistical operations
class StatisticsWorker {
private:
    std::shared_ptr<DataManager> dataManager;

public:
    StatisticsWorker(std::shared_ptr<DataManager> dm) : dataManager(dm) {}

    void performStatistics() {
        std::vector<double> data = { 3.5, 7.1, 5.6 }; // Example data
        double mean = std::accumulate(data.begin(), data.end(), 0.0) / data.size();
        std::cout << "Performing Statistics Operation: Mean Calculation" << std::endl;
        std::cout << "Mean: " << mean << std::endl;
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
};

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

    static void printFancy(const std::string& message, Color color = Color::Default) {
        setColor(color);
        std::cout << "=============================" << std::endl;
        std::cout << message << std::endl;
        std::cout << "=============================" << std::endl;
        setColor(Color::Default);  // Reset to default color
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

    void displayArithmeticFunctions() {
        SystemOutput::print("  Basic Arithmetic Functions:", SystemOutput::Color::Default);
        SystemOutput::print("    1. Addition (a + b)", SystemOutput::Color::Default);
        SystemOutput::print("    2. Subtraction (a - b)", SystemOutput::Color::Default);
        SystemOutput::print("    3. Multiplication (a * b)", SystemOutput::Color::Default);
        SystemOutput::print("    4. Division (a / b)", SystemOutput::Color::Default);
    }

    void displayLinearAlgebraFunctions() {
        SystemOutput::print("  Linear Algebra Functions:", SystemOutput::Color::Default);
        SystemOutput::print("    1. Vector Dot Product (v1 · v2)", SystemOutput::Color::Default);
        SystemOutput::print("    2. Matrix Multiplication (M1 * M2)", SystemOutput::Color::Default);
    }

    void displayCalculusFunctions() {
        SystemOutput::print("  Calculus Functions:", SystemOutput::Color::Default);
        SystemOutput::print("    1. Differentiation (f'(x))", SystemOutput::Color::Default);
        SystemOutput::print("    2. Integration (∫f(x)dx)", SystemOutput::Color::Default);
    }

    void displayStatisticsFunctions() {
        SystemOutput::print("  Statistics Functions:", SystemOutput::Color::Default);
        SystemOutput::print("    1. Mean (average)", SystemOutput::Color::Default);
        SystemOutput::print("    2. Variance (var)", SystemOutput::Color::Default);
        SystemOutput::print("    3. Standard Deviation (std dev)", SystemOutput::Color::Default);
    }

    void displayProbabilityFunctions() {
        SystemOutput::print("  Probability Functions:", SystemOutput::Color::Default);
        SystemOutput::print("    1. Random Sampling", SystemOutput::Color::Default);
    }

    void displayMachineLearningFunctions() {
        SystemOutput::print("  Machine Learning Functions:", SystemOutput::Color::Default);
        SystemOutput::print("    1. ReLU (max(0, x))", SystemOutput::Color::Default);
        SystemOutput::print("    2. Sigmoid (1 / (1 + exp(-x)))", SystemOutput::Color::Default);
        SystemOutput::print("    3. Tanh (tanh(x))", SystemOutput::Color::Default);
    }

    void displayCalculatorFunctionDetails(char choice) {
        clearScreen();
        switch (choice) {
        case '1':
            displayArithmeticFunctions();
            break;
        case '2':
            displayLinearAlgebraFunctions();
            break;
        case '3':
            displayCalculusFunctions();
            break;
        case '4':
            displayStatisticsFunctions();
            break;
        case '5':
            displayProbabilityFunctions();
            break;
        case '6':
            displayMachineLearningFunctions();
            break;
        default:
            SystemOutput::print("Invalid choice.", SystemOutput::Color::Red);
            return;
        }

        std::cout << "\n\nResult: [Your result here]" << std::endl;
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
    auto dataManager = std::make_shared<DataManager>();
    ArithmeticWorker arithmeticWorker(dataManager);
    LinearAlgebraWorker linearAlgebraWorker(dataManager);
    StatisticsWorker statisticsWorker(dataManager);

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
