#include <iostream>
#include <conio.h>  // For _getch() to get single character input without Enter key
#include <windows.h>  // For Windows console color control
#include <string>
#include <vector>
#include <numeric>
#include <cmath>
#include <functional>
#include <memory>
#include <random>
#include <algorithm>

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
        Yellow = 14
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
};

// ScreenManager class to handle the different screens and formats their display output
class ScreenManager {
public:
    // Display the welcome screen
    void displayWelcomeScreen() {
        clearScreen();
        SystemOutput::print("Welcome to Universal Calculator", SystemOutput::Color::Green);
        SystemOutput::print("This program has the following capabilities:", SystemOutput::Color::Default);
        SystemOutput::print("1. Use the calculator", SystemOutput::Color::Default);
        SystemOutput::print("2. Show examples", SystemOutput::Color::Default);
        SystemOutput::print("3. Exit program", SystemOutput::Color::Default);
        SystemOutput::print("Press any key to continue...", SystemOutput::Color::Yellow);
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

    // Clear the console screen
    void clearScreen() {
        system("cls");
    }
};

// BasicMath class for basic arithmetic operations
class BasicMath {
public:
    static double add(double a, double b) { return a + b; }
    static double subtract(double a, double b) { return a - b; }
    static double multiply(double a, double b) { return a * b; }
    static double divide(double a, double b) {
        if (b == 0) { throw std::invalid_argument("Division by zero"); }
        return a / b;
    }
};

// Vector class for linear algebra operations
class Vector {
private:
    std::vector<double> data;

public:
    Vector(std::initializer_list<double> elements) : data(elements) {}
    double dot(const Vector& other) const {
        if (data.size() != other.data.size()) { throw std::invalid_argument("Vector sizes do not match"); }
        double result = 0;
        for (size_t i = 0; i < data.size(); ++i) { result += data[i] * other.data[i]; }
        return result;
    }
};

// Matrix class for linear algebra operations
class Matrix {
private:
    std::vector<std::vector<double>> data;

public:
    Matrix(size_t rows, size_t cols) : data(rows, std::vector<double>(cols, 0.0)) {}
    void set(size_t row, size_t col, double value) { data[row][col] = value; }
    double get(size_t row, size_t col) const { return data[row][col]; }
    Matrix multiply(const Matrix& other) const {
        if (data[0].size() != other.data.size()) { throw std::invalid_argument("Matrix sizes do not match for multiplication"); }
        size_t rows = data.size(), cols = other.data[0].size();
        Matrix result(rows, cols);
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                for (size_t k = 0; k < data[0].size(); ++k) { result.data[i][j] += data[i][k] * other.data[k][j]; }
            }
        }
        return result;
    }
};

// Calculus class for differentiation and integration
class Calculus {
public:
    static double differentiate(std::function<double(double)> f, double x, double h = 1e-5) {
        return (f(x + h) - f(x)) / h;
    }

    static double integrate(std::function<double(double)> f, double a, double b, int n = 1000) {
        double h = (b - a) / n;
        double sum = 0.5 * (f(a) + f(b));
        for (int i = 1; i < n; ++i) { sum += f(a + i * h); }
        return sum * h;
    }
};

// Statistics class for statistical operations
class Statistics {
public:
    static double mean(const std::vector<double>& data) {
        return std::accumulate(data.begin(), data.end(), 0.0) / data.size();
    }

    static double variance(const std::vector<double>& data) {
        double m = mean(data), accum = 0.0;
        for (double x : data) { accum += (x - m) * (x - m); }
        return accum / data.size();
    }

    static double standardDeviation(const std::vector<double>& data) {
        return std::sqrt(variance(data));
    }
};

// Probability class for random sampling
class Probability {
public:
    static std::vector<int> randomSample(int n, int k) {
        std::vector<int> population(n);
        std::iota(population.begin(), population.end(), 1);
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(population.begin(), population.end(), g);
        return std::vector<int>(population.begin(), population.begin() + k);
    }
};

// ActivationFunction class for machine learning activation functions
class ActivationFunction {
public:
    static double relu(double x) { return std::max(0.0, x); }
    static double sigmoid(double x) { return 1 / (1 + std::exp(-x)); }
    static double tanh(double x) { return std::tanh(x); }
};

// LossFunction class for machine learning loss functions
class LossFunction {
public:
    static double meanSquaredError(const std::vector<double>& predicted, const std::vector<double>& actual) {
        if (predicted.size() != actual.size()) { throw std::invalid_argument("Vector sizes do not match"); }
        double sum = 0;
        for (size_t i = 0; i < predicted.size(); ++i) { sum += std::pow(predicted[i] - actual[i], 2); }
        return sum / predicted.size();
    }

    static double crossEntropy(const std::vector<double>& predicted, const std::vector<double>& actual) {
        if (predicted.size() != actual.size()) { throw std::invalid_argument("Vector sizes do not match"); }
        double sum = 0;
        for (size_t i = 0; i < predicted.size(); ++i) {
            sum -= actual[i] * std::log(predicted[i]) + (1 - actual[i]) * std::log(1 - predicted[i]);
        }
        return sum / predicted.size();
    }
};

// Structures to hold data
struct AlignedDataA { int a; double b; };
struct AlignedDataB { char c; float d; };

// DataManager class to manage shared data structures
class DataManager {
private:
    std::shared_ptr<AlignedDataA> dataA;
    std::shared_ptr<AlignedDataB> dataB;

public:
    DataManager()
        : dataA(std::make_shared<AlignedDataA>()), dataB(std::make_shared<AlignedDataB>()) {
        dataA->a = 0; dataA->b = 0.0;
        dataB->c = '\0'; dataB->d = 0.0f;
    }

    void setDataA(int a, double b) { dataA->a = a; dataA->b = b; }
    std::shared_ptr<AlignedDataA> getDataA() const { return dataA; }
    void setDataB(char c, float d) { dataB->c = c; dataB->d = d; }
    std::shared_ptr<AlignedDataB> getDataB() const { return dataB; }

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

int main() {
    ScreenManager screenManager;
    screenManager.displayWelcomeScreen();

    bool running = true;
    while (running) {
        screenManager.displayMainMenu();

        char choice = UserInput::getChar();
        switch (choice) {
        case '1':
            // Implement calculator functionality
            SystemOutput::print("Calculator functionality not implemented yet.", SystemOutput::Color::Yellow);
            break;
        case '2':
            // Implement show examples functionality
            SystemOutput::print("Show examples functionality not implemented yet.", SystemOutput::Color::Yellow);
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
