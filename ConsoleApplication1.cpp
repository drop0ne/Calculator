#include <iostream>
#include <vector>
#include <cmath>
#include <stdexcept>
#include <functional>
#include <numeric>
#include <random>
#include <algorithm>
#include <stack>
#include <sstream>
#include <iomanip>

using namespace std;

class MathBase {
protected:
    random_device rd;
    mt19937 gen;
    uniform_real_distribution<> dis;

    MathBase() : gen(rd()), dis(-100, 100) {}

    void clearScreen() {
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif
    }

    void waitForUser() {
        cout << setw(40) << "Press any key to return to the main menu...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
    }

    double generateRandomDouble() {
        return limitRNG(dis(gen));
    }

    double limitRNG(double value) {
        return round(value * 100.0) / 100.0;  // Example of limiting to two decimal places for clarity
    }

    void resetCin() {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    double parseAndEvaluate(const string& expression, double x) {
        istringstream iss(expression);
        return parseExpression(iss, x);
    }

private:
    double parseExpression(istringstream& iss, double x) {
        stack<double> values;
        stack<char> ops;

        while (iss) {
            char token = iss.peek();
            if (isspace(token)) {
                iss.get();
                continue;
            }
            if (isdigit(token) || token == '.') {
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
                throw runtime_error("Invalid character in expression");
            }
        }

        while (!ops.empty()) {
            applyOperator(values, ops.top());
            ops.pop();
        }

        if (values.size() != 1) {
            throw runtime_error("Invalid expression");
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

    void applyOperator(stack<double>& values, char op) {
        if (values.size() < 2) {
            throw runtime_error("Invalid expression");
        }
        double right = values.top(); values.pop();
        double left = values.top(); values.pop();
        switch (op) {
        case '+': values.push(left + right); break;
        case '-': values.push(left - right); break;
        case '*': values.push(left * right); break;
        case '/': values.push(left / right); break;
        default: throw runtime_error("Unknown operator");
        }
    }
};

// Arithmetic class
class Arithmetic : public MathBase {
public:
    void performArithmetic() {
        cout << "\nSelect operation: 1. Addition 2. Subtraction 3. Multiplication 4. Division\n";
        int operation;
        cin >> operation;
        double num1, num2, result;

        cout << "Enter first number: ";
        cin >> num1;
        cout << "Enter second number: ";
        cin >> num2;

        switch (operation) {
        case 1:
            result = num1 + num2;
            break;
        case 2:
            result = num1 - num2;
            break;
        case 3:
            result = num1 * num2;
            break;
        case 4:
            if (num2 != 0) {
                result = num1 / num2;
            }
            else {
                cout << "Error: Division by zero\n";
                return;
            }
            break;
        default:
            cout << "Invalid operation\n";
            return;
        }
        cout << "Result: " << result << '\n';
        waitForUser();
    }

    void displayExample() {
        double a = generateRandomDouble();
        double b = generateRandomDouble();
        cout << "Arithmetic Example:\n";
        cout << "-------------------\n";
        cout << "Operation: Addition\n";
        cout << "Inputs: " << a << " + " << b << "\n";
        cout << "Result: " << (a + b) << "\n";
        cout << "Explanation: Addition is used to find the total or sum by combining two numbers.\n";
        cout << "Common Use: Calculating the total cost of items in a shopping cart.\n";
        cout << "-------------------\n";
    }
};

// Linear Algebra class
class LinearAlgebra : public MathBase {
public:
    void performLinearAlgebra() {
        cout << "\nSelect operation: 1. Matrix Multiplication 2. Determinant\n";
        int operation;
        cin >> operation;

        switch (operation) {
        case 1: {
            // Matrix multiplication example
            int n, m, p;
            cout << "Enter dimensions of first matrix (n x m): ";
            cin >> n >> m;
            vector<vector<double>> matrix1(n, vector<double>(m));
            cout << "Enter first matrix elements:\n";
            for (int i = 0; i < n; ++i)
                for (int j = 0; j < m; ++j)
                    cin >> matrix1[i][j];

            cout << "Enter number of columns for second matrix: ";
            cin >> p;
            vector<vector<double>> matrix2(m, vector<double>(p));
            cout << "Enter second matrix elements:\n";
            for (int i = 0; i < m; ++i)
                for (int j = 0; j < p; ++j)
                    cin >> matrix2[i][j];

            vector<vector<double>> result(n, vector<double>(p, 0));
            for (int i = 0; i < n; ++i)
                for (int j = 0; j < p; ++j)
                    for (int k = 0; k < m; ++k)
                        result[i][j] += matrix1[i][k] * matrix2[k][j];

            cout << "Resultant Matrix:\n";
            for (const auto& row : result) {
                for (const auto& val : row)
                    cout << val << " ";
                cout << '\n';
            }
            break;
        }
        case 2:
            // Determinant calculation example (2x2 matrix for simplicity)
            double a, b, c, d;
            cout << "Enter elements of 2x2 matrix (a b c d): ";
            cin >> a >> b >> c >> d;
            cout << "Determinant: " << (a * d - b * c) << '\n';
            break;
        default:
            cout << "Invalid operation\n";
        }
        waitForUser();
    }

    void displayExample() {
        vector<double> vec1 = { generateRandomDouble(), generateRandomDouble(), generateRandomDouble() };
        vector<double> vec2 = { generateRandomDouble(), generateRandomDouble(), generateRandomDouble() };
        auto resultVec = addVectors(vec1, vec2);
        cout << "Linear Algebra Example:\n";
        cout << "-------------------\n";
        cout << "Operation: Vector Addition\n";
        cout << "Inputs: [" << vec1[0] << "," << vec1[1] << "," << vec1[2] << "] + [";
        cout << vec2[0] << "," << vec2[1] << "," << vec2[2] << "]\n";
        cout << "Result: ";
        displayVector(resultVec);
        cout << "Explanation: Vector addition is the process of adding two vectors by adding the corresponding components.\n";
        cout << "Common Use: Combining forces in physics.\n";
        cout << "-------------------\n";
    }

private:
    vector<double> addVectors(const vector<double>& a, const vector<double>& b) {
        if (a.size() != b.size()) throw invalid_argument("Vectors must be the same size");
        vector<double> result(a.size());
        for (size_t i = 0; i < a.size(); ++i) {
            result[i] = a[i] + b[i];
        }
        return result;
    }

    void displayVector(const vector<double>& vec) {
        cout << "[";
        for (size_t i = 0; i < vec.size(); ++i) {
            cout << vec[i];
            if (i != vec.size() - 1) {
                cout << ", ";
            }
        }
        cout << "]" << endl;
    }
};

// Calculus class
class Calculus : public MathBase {
public:
    void performCalculus() {
        cout << "\nSelect operation: 1. Differentiation 2. Integration\n";
        int operation;
        cin >> operation;

        switch (operation) {
        case 1:
            // Differentiation example (polynomial)
            cout << "Differentiation is a complex task requiring symbolic math libraries.\n";
            break;
        case 2:
            // Integration example (definite integral of polynomial)
            cout << "Integration is a complex task requiring symbolic math libraries.\n";
            break;
        default:
            cout << "Invalid operation\n";
        }
        waitForUser();
    }

    void displayExample() {
        auto f = [](double x) { return x * x; }; // Example function: f(x) = x^2
        double a = generateRandomDouble();
        cout << "Calculus Example:\n";
        cout << "-------------------\n";
        cout << "Operation: Differentiation\n";
        cout << "Inputs: f(x) = x^2, x = " << a << "\n";
        cout << "Result: f'(" << a << ") = " << differentiate(f, a) << "\n";
        cout << "Explanation: Differentiation is the process of finding the derivative, which represents the rate of change.\n";
        cout << "Common Use: Calculating the instantaneous rate of change of a function, such as velocity in physics.\n";
        cout << "-------------------\n";
    }

private:
    double differentiate(function<double(double)> f, double x) {
        double h = 1e-5;
        return (f(x + h) - f(x)) / h;
    }
};

// Statistics class
class Statistics : public MathBase {
public:
    void performStatistics() {
        cout << "\nSelect operation: 1. Mean 2. Variance 3. Standard Deviation\n";
        int operation;
        cin >> operation;
        int n;
        cout << "Enter number of data points: ";
        cin >> n;
        vector<double> data(n);

        cout << "Enter data points:\n";
        for (int i = 0; i < n; ++i)
            cin >> data[i];

        double mean = accumulate(data.begin(), data.end(), 0.0) / n;
        switch (operation) {
        case 1:
            cout << "Mean: " << mean << '\n';
            break;
        case 2: {
            double variance = 0;
            for (double x : data)
                variance += (x - mean) * (x - mean);
            variance /= n;
            cout << "Variance: " << variance << '\n';
            break;
        }
        case 3: {
            double variance = 0;
            for (double x : data)
                variance += (x - mean) * (x - mean);
            variance /= n;
            cout << "Standard Deviation: " << sqrt(variance) << '\n';
            break;
        }
        default:
            cout << "Invalid operation\n";
        }
        waitForUser();
    }

    void displayExample() {
        int n = 5;
        vector<double> data(n);
        generate(data.begin(), data.end(), [this]() { return generateRandomDouble(); });
        double mean = accumulate(data.begin(), data.end(), 0.0) / n;
        cout << "Statistics Example:\n";
        cout << "-------------------\n";
        cout << "Operation: Mean\n";
        cout << "Inputs: ";
        for (double x : data) cout << x << " ";
        cout << "\nResult: " << mean << "\n";
        cout << "Explanation: The mean is the average of a set of numbers, calculated by summing them up and dividing by the count.\n";
        cout << "Common Use: Finding the average score of students in a class.\n";
        cout << "-------------------\n";
    }
};

// Probability class
class Probability : public MathBase {
public:
    void performProbability() {
        cout << "\nSelect operation: 1. Probability Distribution 2. Random Sampling\n";
        int operation;
        cin >> operation;

        switch (operation) {
        case 1:
            cout << "Probability Distribution calculation is complex and needs specific libraries.\n";
            break;
        case 2:
            // Random Sampling example
            int n, k;
            cout << "Enter population size: ";
            cin >> n;
            cout << "Enter sample size: ";
            cin >> k;

            if (n < k) {
                cout << "Error: Sample size cannot be greater than population size\n";
                return;
            }

            vector<int> population(n);
            iota(population.begin(), population.end(), 1);
            shuffle(population.begin(), population.end(), gen);

            cout << "Random Sample:\n";
            for (int i = 0; i < k; ++i)
                cout << population[i] << " ";
            cout << '\n';
            break;
        default:
            cout << "Invalid operation\n";
        }
        waitForUser();
    }

    void displayExample() {
        int n = 10;
        int k = 5;
        vector<int> population(n);
        iota(population.begin(), population.end(), 1);
        shuffle(population.begin(), population.end(), gen);

        cout << "Probability Example:\n";
        cout << "-------------------\n";
        cout << "Operation: Random Sampling\n";
        cout << "Inputs: Population size = " << n << ", Sample size = " << k << "\n";
        cout << "Result: Random Sample = ";
        for (int i = 0; i < k; ++i)
            cout << population[i] << " ";
        cout << "\nExplanation: Random sampling is the process of selecting a subset of individuals from a population to estimate characteristics of the whole population.\n";
        cout << "Common Use: Selecting participants for a survey.\n";
        cout << "-------------------\n";
    }
};

// Optimization class
class Optimization : public MathBase {
public:
    void performOptimization() {
        cout << "\nOptimization involves techniques like Gradient Descent, which requires detailed implementation.\n";
        waitForUser();
    }

    void displayExample() {
        cout << "Optimization Example:\n";
        cout << "-------------------\n";
        cout << "Optimization techniques like Gradient Descent are complex and require detailed implementation.\n";
        cout << "Common Use: Finding the minimum cost or maximum profit in various industries.\n";
        cout << "-------------------\n";
    }
};

// Universal Calculator class
class UniversalCalculator {
private:
    Arithmetic arithmetic;
    LinearAlgebra linearAlgebra;
    Calculus calculus;
    Statistics statistics;
    Probability probability;
    Optimization optimization;

public:
    void run() {
        while (true) {
            cout << "\nSelect the type of calculation you want to perform:\n";
            cout << "1. Arithmetic\n";
            cout << "2. Linear Algebra\n";
            cout << "3. Calculus\n";
            cout << "4. Statistics\n";
            cout << "5. Probability\n";
            cout << "6. Optimization\n";
            cout << "7. Show Examples of Use\n";
            cout << "8. Exit\n";
            int choice;
            cin >> choice;

            switch (choice) {
            case 1:
                arithmetic.performArithmetic();
                break;
            case 2:
                linearAlgebra.performLinearAlgebra();
                break;
            case 3:
                calculus.performCalculus();
                break;
            case 4:
                statistics.performStatistics();
                break;
            case 5:
                probability.performProbability();
                break;
            case 6:
                optimization.performOptimization();
                break;
            case 7:
                displayExamples();
                break;
            case 8:
                return;
            default:
                cout << "Invalid choice, please try again\n";
            }
        }
    }

private:
    void displayExamples() {
        clearScreen();
        cout << "Examples of Use:\n";
        cout << "-------------------\n";
        arithmetic.displayExample();
        cout << "-------------------\n";
        linearAlgebra.displayExample();
        cout << "-------------------\n";
        calculus.displayExample();
        cout << "-------------------\n";
        statistics.displayExample();
        cout << "-------------------\n";
        probability.displayExample();
        cout << "-------------------\n";
        optimization.displayExample();
        waitForUser();
    }

    void clearScreen() {
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif
    }

    void waitForUser() {
        cout << setw(40) << "Press any key to return to the main menu...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
    }
};

int main() {
    UniversalCalculator calculator;
    calculator.run();
    return 0;
}
