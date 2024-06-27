#include <iostream>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <functional>
#include <stdexcept>
#include <sstream>
#include <map>
#include <stack>

class MathBase {
public:
    virtual ~MathBase() = default;
protected:
    double parseAndEvaluate(const std::string& expression, double x) {
        std::istringstream iss(expression);
        return parseExpression(iss, x);
    }

private:
    double parseExpression(std::istringstream& iss, double x) {
        std::stack<double> values;
        std::stack<char> ops;

        while (iss) {
            char token = iss.peek();
            if (std::isspace(token)) {
                iss.get();
                continue;
            }
            if (std::isdigit(token) || token == '.') {
                double value;
                iss >> value;
                values.push(value);
            }
            else if (token == 'x') {
                iss.get();
                values.push(x);
            }
            else if (token == '(') {
                iss.get();
                values.push(parseExpression(iss, x));
            }
            else if (token == ')') {
                iss.get();
                break;
            }
            else if (isOperator(token)) {
                while (!ops.empty() && precedence(ops.top()) >= precedence(token)) {
                    applyOperator(values, ops.top());
                    ops.pop();
                }
                ops.push(token);
                iss.get();
            }
            else {
                throw std::runtime_error("Invalid character in expression");
            }
        }

        while (!ops.empty()) {
            applyOperator(values, ops.top());
            ops.pop();
        }

        if (values.size() != 1) {
            throw std::runtime_error("Invalid expression");
        }
        return values.top();
    }

    bool isOperator(char token) const {
        return token == '+' || token == '-' || token == '*' || token == '/';
    }

    int precedence(char op) const {
        if (op == '+' || op == '-') return 1;
        if (op == '*' || op == '/') return 2;
        return 0;
    }

    void applyOperator(std::stack<double>& values, char op) {
        if (values.size() < 2) {
            throw std::runtime_error("Invalid expression");
        }
        double right = values.top(); values.pop();
        double left = values.top(); values.pop();
        switch (op) {
        case '+': values.push(left + right); break;
        case '-': values.push(left - right); break;
        case '*': values.push(left * right); break;
        case '/': values.push(left / right); break;
        default: throw std::runtime_error("Unknown operator");
        }
    }
};

class WelcomeScreen {
public:
    void displayWelcome() {
        clearScreen();
        std::cout << "Welcome to the Math Application!" << std::endl;
        std::cout << "Please select an option:" << std::endl;
        std::cout << "1. Use the Calculator" << std::endl;
        std::cout << "2. Show Examples of Use" << std::endl;
        std::cout << "Enter your choice (1 or 2): ";
    }

    void handleUserChoice() {
        int choice;
        std::cin >> choice;
        clearScreen();

        if (choice == 1) {
            displayCalculator();
        }
        else if (choice == 2) {
            displayExamples();
        }
        else {
            std::cerr << "Invalid choice. Please restart the program." << std::endl;
        }
    }

private:
    void clearScreen() {
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif
    }

    void displayCalculator() {
        std::cout << "Calculator Interface" << std::endl;
        std::cout << "Available Math Types:" << std::endl;
        std::cout << "1. Arithmetic" << std::endl;
        std::cout << "2. Geometry" << std::endl;
        std::cout << "3. Trigonometry" << std::endl;
        std::cout << "4. Calculus" << std::endl;
        std::cout << "5. Linear Algebra" << std::endl;
        std::cout << "Enter the number corresponding to the math type: ";

        int mathType;
        std::cin >> mathType;
        clearScreen();

        switch (mathType) {
        case 1:
            displayArithmeticFunctions();
            break;
        case 2:
            displayGeometryFunctions();
            break;
        case 3:
            displayTrigonometryFunctions();
            break;
        case 4:
            displayCalculusFunctions();
            break;
        case 5:
            displayLinearAlgebraFunctions();
            break;
        default:
            std::cerr << "Invalid choice. Please restart the program." << std::endl;
            break;
        }
    }

    void displayExamples() {
        std::cout << "Examples of Use:" << std::endl;
        std::cout << "1. Arithmetic: Add 5 and 3 -> add 5 3" << std::endl;
        std::cout << "2. Geometry: Area of a circle with radius 5 -> area_circle 5" << std::endl;
        std::cout << "3. Trigonometry: Sin of 90 degrees -> sin 1.5708" << std::endl;
        std::cout << "4. Calculus: Differentiate x^2 at x=2 -> differentiate x^2 2" << std::endl;
        std::cout << "5. Linear Algebra: Add vectors [1,2,3] and [4,5,6] -> add_vectors [1,2,3] [4,5,6]" << std::endl;
    }

    void displayArithmeticFunctions() {
        std::cout << "Arithmetic Functions:" << std::endl;
        std::cout << "1. Add" << std::endl;
        std::cout << "2. Subtract" << std::endl;
        std::cout << "3. Multiply" << std::endl;
        std::cout << "4. Divide" << std::endl;
        std::cout << "Usage: Enter the operation followed by two operands, e.g., 'add 5 3'." << std::endl;
    }

    void displayGeometryFunctions() {
        std::cout << "Geometry Functions:" << std::endl;
        std::cout << "1. Area of Circle" << std::endl;
        std::cout << "2. Circumference of Circle" << std::endl;
        std::cout << "3. Area of Rectangle" << std::endl;
        std::cout << "4. Perimeter of Rectangle" << std::endl;
        std::cout << "Usage: Enter the operation followed by required parameters, e.g., 'area_circle 5'." << std::endl;
    }

    void displayTrigonometryFunctions() {
        std::cout << "Trigonometry Functions:" << std::endl;
        std::cout << "1. Sin" << std::endl;
        std::cout << "2. Cos" << std::endl;
        std::cout << "3. Tan" << std::endl;
        std::cout << "Usage: Enter the operation followed by an angle in radians, e.g., 'sin 1.5708'." << std::endl;
    }

    void displayCalculusFunctions() {
        std::cout << "Calculus Functions:" << std::endl;
        std::cout << "1. Differentiate" << std::endl;
        std::cout << "2. Integrate" << std::endl;
        std::cout << "Usage: Enter the operation followed by the function and point or range, e.g., 'differentiate x^2 2'." << std::endl;
    }

    void displayLinearAlgebraFunctions() {
        std::cout << "Linear Algebra Functions:" << std::endl;
        std::cout << "1. Add Vectors" << std::endl;
        std::cout << "2. Subtract Vectors" << std::endl;
        std::cout << "Usage: Enter the operation followed by two vectors, e.g., 'add_vectors [1,2,3] [4,5,6]'." << std::endl;
    }
};

class MathApplication {
public:
    void run() {
        WelcomeScreen welcomeScreen;
        welcomeScreen.displayWelcome();
        welcomeScreen.handleUserChoice();
    }
};

int main() {
    MathApplication app;
    app.run();
    return 0;
}
