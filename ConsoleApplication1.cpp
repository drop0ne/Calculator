#include <iostream>
#include <string>
#include <stack>
#include <cctype>
#include <sstream>
#include <stdexcept>
#include <functional>
#include <map>

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
class Arithmetic : public MathBase {
public:
    double add(double a, double b) { return a + b; }
    double subtract(double a, double b) { return a - b; }
    double multiply(double a, double b) { return a * b; }
    double divide(double a, double b) {
        if (b == 0) throw std::invalid_argument("Division by zero");
        return a / b;
    }
};
class Geometry : public MathBase {
public:
    double areaCircle(double radius) {
        if (radius < 0) throw std::invalid_argument("Radius cannot be negative");
        return 3.14159265358979323846 * radius * radius;
    }

    double circumferenceCircle(double radius) {
        if (radius < 0) throw std::invalid_argument("Radius cannot be negative");
        return 2 * 3.14159265358979323846 * radius;
    }

    double areaRectangle(double length, double width) {
        if (length < 0 || width < 0) throw std::invalid_argument("Length and width cannot be negative");
        return length * width;
    }

    double perimeterRectangle(double length, double width) {
        if (length < 0 || width < 0) throw std::invalid_argument("Length and width cannot be negative");
        return 2 * (length + width);
    }
};
#include <cmath>

class Trigonometry : public MathBase {
public:
    double sin(double angle) { return std::sin(angle); }
    double cos(double angle) { return std::cos(angle); }
    double tan(double angle) { return std::tan(angle); }
};
class Calculus : public MathBase {
public:
    double differentiate(std::function<double(double)> f, double x) {
        double h = 1e-5;
        return (f(x + h) - f(x)) / h;
    }

    double integrate(std::function<double(double)> f, double a, double b) {
        if (a > b) throw std::invalid_argument("Lower limit cannot be greater than upper limit");
        double h = 1e-5;
        double sum = 0.0;
        for (double x = a; x < b; x += h) {
            sum += f(x) * h;
        }
        return sum;
    }
};
#include <vector>

class LinearAlgebra : public MathBase {
public:
    std::vector<double> addVectors(const std::vector<double>& a, const std::vector<double>& b) {
        if (a.size() != b.size()) throw std::invalid_argument("Vectors must be the same size");
        std::vector<double> result(a.size());
        for (size_t i = 0; i < a.size(); ++i) {
            result[i] = a[i] + b[i];
        }
        return result;
    }

    std::vector<double> subtractVectors(const std::vector<double>& a, const std::vector<double>& b) {
        if (a.size() != b.size()) throw std::invalid_argument("Vectors must be the same size");
        std::vector<double> result(a.size());
        for (size_t i = 0; i < a.size(); ++i) {
            result[i] = a[i] - b[i];
        }
        return result;
    }
};
class MathApplication {
public:
    void run() {
        // Example usage of each math class

        // Arithmetic
        Arithmetic arithmetic;
        try {
            double result = arithmetic.add(5, 3);
            std::cout << "Addition result: " << result << std::endl;
        }
        catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }

        // Geometry
        Geometry geometry;
        try {
            double area = geometry.areaCircle(5);
            std::cout << "Area of circle with radius 5: " << area << std::endl;

            double perimeter = geometry.perimeterRectangle(5, 3);
            std::cout << "Perimeter of rectangle with length 5 and width 3: " << perimeter << std::endl;
        }
        catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }

        // Trigonometry
        Trigonometry trigonometry;
        try {
            double sine = trigonometry.sin(3.14159265358979323846 / 2);
            std::cout << "Sine of 90 degrees: " << sine << std::endl;
        }
        catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }

        // Calculus
        Calculus calculus;
        try {
            auto func = [](double x) { return x * x; }; // Example function: f(x) = x^2
            double derivative = calculus.differentiate(func, 2);
            std::cout << "Derivative of x^2 at x = 2: " << derivative << std::endl;

            double integral = calculus.integrate(func, 0, 2);
            std::cout << "Integral of x^2 from 0 to 2: " << integral << std::endl;
        }
        catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }

        // Linear Algebra
        LinearAlgebra linearAlgebra;
        try {
            std::vector<double> vec1 = { 1, 2, 3 };
            std::vector<double> vec2 = { 4, 5, 6 };
            auto resultVec = linearAlgebra.addVectors(vec1, vec2);
            std::cout << "Vector addition result: ";
            for (double val : resultVec) {
                std::cout << val << " ";
            }
            std::cout << std::endl;
        }
        catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }
};
int main() {
    MathApplication app;
    app.run();
    return 0;
}