#include <iostream>
#include <memory>
#include <vector>
#include <cmath>
#include <numeric>
#include <algorithm>
#include <random>
#include <functional>
#include <stack>
#include <sstream>
#include <iomanip>
#include <cassert>

// Define a simple data structure
struct alignas(64) AlignedData {
    int a;
    double b;
    char c;

    // Constructor
    AlignedData(int a_val = 0, double b_val = 0.0, char c_val = '\0')
        : a(a_val), b(b_val), c(c_val) {}
};

// Ensure the structure is 64-bit aligned
static_assert(alignof(AlignedData) == 64, "AlignedData is not 64-bit aligned");
class DataManager {
private:
    std::shared_ptr<AlignedData> data;

public:
    DataManager() : data(std::make_shared<AlignedData>()) {}

    void setData(int a, double b, char c) {
        data->a = a;
        data->b = b;
        data->c = c;
    }

    std::shared_ptr<AlignedData> getData() const {
        return data;
    }

    void printData() const {
        std::cout << "a: " << data->a << ", b: " << data->b << ", c: " << data->c << std::endl;
    }
};
class MathBase {
public:
    MathBase() : gen(rd()), dis(-100, 100) {}

protected:
    double generateRandomDouble() {
        return limitRNG(dis(gen));
    }

    double limitRNG(double value) {
        return round(value * 100.0) / 100.0;  // Example of limiting to two decimal places for clarity
    }

    double parseAndEvaluate(const std::string& expression, double x) {
        std::istringstream iss(expression);
        return parseExpression(iss, x);
    }

private:
    std::random_device rd;
    std::mt19937 gen;
    std::uniform_real_distribution<> dis;

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
private:
    std::shared_ptr<AlignedData> data;

public:
    Arithmetic(std::shared_ptr<AlignedData> data) : data(data) {}

    void performArithmetic() {
        std::cout << "\nSelect operation: 1. Addition 2. Subtraction 3. Multiplication 4. Division\n";
        int operation;
        std::cin >> operation;

        double result = performOperation(operation);
        if (result != -1) {
            std::cout << "Result: " << result << '\n';
        }
        else {
            std::cout << "Invalid operation or error occurred.\n";
        }
    }

    void displayExample() {
        double a = generateRandomDouble();
        double b = generateRandomDouble();
        std::cout << "Arithmetic Example:\n";
        std::cout << "-------------------\n";
        std::cout << "Operation: Addition\n";
        std::cout << "Inputs: " << a << " + " << b << "\n";
        std::cout << "Result: " << (a + b) << "\n";
        std::cout << "Explanation: Addition is used to find the total or sum by combining two numbers.\n";
        std::cout << "Common Use: Calculating the total cost of items in a shopping cart.\n";
        std::cout << "-------------------\n";
    }

private:
    double performOperation(int operation) {
        double num1 = data->a;
        double num2 = data->b;

        switch (operation) {
        case 1: return num1 + num2;
        case 2: return num1 - num2;
        case 3: return num1 * num2;
        case 4:
            if (num2 != 0) return num1 / num2;
            else std::cout << "Error: Division by zero\n";
            return -1;
        default:
            std::cout << "Invalid operation\n";
            return -1;
        }
    }
};
class LinearAlgebra : public MathBase {
private:
    std::shared_ptr<AlignedData> data;

public:
    LinearAlgebra(std::shared_ptr<AlignedData> data) : data(data) {}

    void performLinearAlgebra() {
        std::cout << "\nSelect operation: 1. Matrix Multiplication 2. Determinant\n";
        int operation;
        std::cin >> operation;

        if (!performOperation(operation)) {
            std::cout << "Invalid operation or error occurred.\n";
        }
    }

    void displayExample() {
        std::vector<double> vec1 = { generateRandomDouble(), generateRandomDouble(), generateRandomDouble() };
        std::vector<double> vec2 = { generateRandomDouble(), generateRandomDouble(), generateRandomDouble() };
        auto resultVec = addVectors(vec1, vec2);
        std::cout << "Linear Algebra Example:\n";
        std::cout << "-------------------\n";
        std::cout << "Operation: Vector Addition\n";
        std::cout << "Inputs: [" << vec1[0] << "," << vec1[1] << "," << vec1[2] << "] + [";
        std::cout << vec2[0] << "," << vec2[1] << "," << vec2[2] << "]\n";
        std::cout << "Result: ";
        displayVector(resultVec);
        std::cout << "Explanation: Vector addition is the process of adding two vectors by adding the corresponding components.\n";
        std::cout << "Common Use: Combining forces in physics.\n";
        std::cout << "-------------------\n";
    }

private:
    bool performOperation(int operation) {
        switch (operation) {
        case 1: return matrixMultiplication();
        case 2: return determinantCalculation();
        default: return false;
        }
    }

    bool matrixMultiplication() {
        int n, m, p;
        std::cout << "Enter dimensions of first matrix (n x m): ";
        std::cin >> n >> m;
        std::vector<std::vector<double>> matrix1(n, std::vector<double>(m));
        std::cout << "Enter first matrix elements:\n";
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                std::cin >> matrix1[i][j];

        std::cout << "Enter number of columns for second matrix: ";
        std::cin >> p;
        std::vector<std::vector<double>> matrix2(m, std::vector<double>(p));
        std::cout << "Enter second matrix elements:\n";
        for (int i = 0; i < m; ++i)
            for (int j = 0; j < p; ++j)
                std::cin >> matrix2[i][j];

        std::vector<std::vector<double>> result(n, std::vector<double>(p, 0));
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < p; ++j)
                for (int k = 0; k < m; ++k)
                    result[i][j] += matrix1[i][k] * matrix2[k][j];

        std::cout << "Resultant Matrix:\n";
        for (const auto& row : result) {
            for (const auto& val : row)
                std::cout << val << " ";
            std::cout << '\n';
        }
        return true;
    }

    bool determinantCalculation() {
        double a, b, c, d;
        std::cout << "Enter elements of 2x2 matrix (a b c d): ";
        std::cin >> a >> b >> c >> d;
        std::cout << "Determinant: " << (a * d - b * c) << '\n';
        return true;
    }

    std::vector<double> addVectors(const std::vector<double>& a, const std::vector<double>& b) const {
        if (a.size() != b.size()) throw std::invalid_argument("Vectors must be the same size");
        std::vector<double> result(a.size());
        for (size_t i = 0; i < a.size(); ++i) {
            result[i] = a[i] + b[i];
        }
        return result;
    }

    void displayVector(const std::vector<double>& vec) const {
        std::cout << "[";
        for (size_t i = 0; i < vec.size(); ++i) {
            std::cout << vec[i];
            if (i != vec.size() - 1) {
                std::cout << ", ";
            }
        }
        std::cout << "]" << std::endl;
    }
};
class Calculus : public MathBase {
private:
    std::shared_ptr<AlignedData> data;

public:
    Calculus(std::shared_ptr<AlignedData> data) : data(data) {}

    void performCalculus() {
        std::cout << "\nSelect operation: 1. Differentiation 2. Integration\n";
        int operation;
        std::cin >> operation;

        if (!performOperation(operation)) {
            std::cout << "Invalid operation or error occurred.\n";
        }
    }

    void displayExample() {
        auto f = [](double x) { return x * x; }; // Example function: f(x) = x^2
        double a = generateRandomDouble();
        std::cout << "Calculus Example:\n";
        std::cout << "-------------------\n";
        std::cout << "Operation: Differentiation\n";
        std::cout << "Inputs: f(x) = x^2, x = " << a << "\n";
        std::cout << "Result: f'(" << a << ") = " << differentiate(f, a) << "\n";
        std::cout << "Explanation: Differentiation is the process of finding the derivative, which represents the rate of change.\n";
        std::cout << "Common Use: Calculating the instantaneous rate of change of a function, such as velocity in physics.\n";
        std::cout << "-------------------\n";
    }

private:
    bool performOperation(int operation) {
        switch (operation) {
        case 1: return differentiation();
        case 2: return integration();
        default: return false;
        }
    }

    bool differentiation() {
        std::cout << "Differentiation is a complex task requiring symbolic math libraries.\n";
        return true;
    }

    bool integration() {
        std::cout << "Integration is a complex task requiring symbolic math libraries.\n";
        return true;
    }

    double differentiate(std::function<double(double)> f, double x) const {
        double h = 1e-5;
        return (f(x + h) - f(x)) / h;
    }
};
class Statistics : public MathBase {
private:
    std::shared_ptr<AlignedData> data;

public:
    Statistics(std::shared_ptr<AlignedData> data) : data(data) {}

    void performStatistics() {
        std::cout << "\nSelect operation: 1. Mean 2. Variance 3. Standard Deviation\n";
        int operation;
        std::cin >> operation;

        if (!performOperation(operation)) {
            std::cout << "Invalid operation or error occurred.\n";
        }
    }

    void displayExample() {
        int n = 5;
        std::vector<double> data(n);
        std::generate(data.begin(), data.end(), [this]() { return generateRandomDouble(); });
        double mean = std::accumulate(data.begin(), data.end(), 0.0) / n;
        std::cout << "Statistics Example:\n";
        std::cout << "-------------------\n";
        std::cout << "Operation: Mean\n";
        std::cout << "Inputs: ";
        for (double x : data) std::cout << x << " ";
        std::cout << "\nResult: " << mean << "\n";
        std::cout << "Explanation: The mean is the average of a set of numbers, calculated by summing them up and dividing by the count.\n";
        std::cout << "Common Use: Finding the average score of students in a class.\n";
        std::cout << "-------------------\n";
    }

private:
    bool performOperation(int operation) {
        int n;
        std::cout << "Enter number of data points: ";
        std::cin >> n;
        std::vector<double> data(n);
        std::cout << "Enter data points:\n";
        for (int i = 0; i < n; ++i)
            std::cin >> data[i];

        double mean = std::accumulate(data.begin(), data.end(), 0.0) / n;
        switch (operation) {
        case 1: return calculateMean(mean);
        case 2: return calculateVariance(data, mean);
        case 3: return calculateStandardDeviation(data, mean);
        default: return false;
        }
    }

    bool calculateMean(double mean) const {
        std::cout << "Mean: " << mean << '\n';
        return true;
    }

    bool calculateVariance(const std::vector<double>& data, double mean) const {
        double variance = 0;
        for (double x : data)
            variance += (x - mean) * (x - mean);
        variance /= data.size();
        std::cout << "Variance: " << variance << '\n';
        return true;
    }

    bool calculateStandardDeviation(const std::vector<double>& data, double mean) const {
        double variance = 0;
        for (double x : data)
            variance += (x - mean) * (x - mean);
        variance /= data.size();
        std::cout << "Standard Deviation: " << std::sqrt(variance) << '\n';
        return true;
    }
};
class Probability : public MathBase {
private:
    std::shared_ptr<AlignedData> data;

public:
    Probability(std::shared_ptr<AlignedData> data) : data(data) {}

    void performProbability() {
        std::cout << "\nSelect operation: 1. Probability Distribution 2. Random Sampling\n";
        int operation;
        std::cin >> operation;

        if (!performOperation(operation)) {
            std::cout << "Invalid operation or error occurred.\n";
        }
    }

    void displayExample() {
        int n = 10;
        int k = 5;
        std::vector<int> population(n);
        std::iota(population.begin(), population.end(), 1);
        std::shuffle(population.begin(), population.end(), gen);

        std::cout << "Probability Example:\n";
        std::cout << "-------------------\n";
        std::cout << "Operation: Random Sampling\n";
        std::cout << "Inputs: Population size = " << n << ", Sample size = " << k << "\n";
        std::cout << "Result: Random Sample = ";
        for (int i = 0; i < k; ++i)
            std::cout << population[i] << " ";
        std::cout << "\nExplanation: Random sampling is the process of selecting a subset of individuals from a population to estimate characteristics of the whole population.\n";
        std::cout << "Common Use: Selecting participants for a survey.\n";
        std::cout << "-------------------\n";
    }

private:
    bool performOperation(int operation) {
        switch (operation) {
        case 1: return probabilityDistribution();
        case 2: return randomSampling();
        default: return false;
        }
    }

    bool probabilityDistribution() {
        std::cout << "Probability Distribution calculation is complex and needs specific libraries.\n";
        return true;
    }

    bool randomSampling() {
        int n, k;
        std::cout << "Enter population size: ";
        std::cin >> n;
        std::cout << "Enter sample size: ";
        std::cin >> k;

        if (n < k) {
            std::cout << "Error: Sample size cannot be greater than population size\n";
            return false;
        }

        std::vector<int> population(n);
        std::iota(population.begin(), population.end(), 1);
        std::shuffle(population.begin(), population.end(), gen);

        std::cout << "Random Sample:\n";
        for (int i = 0; i < k; ++i)
            std::cout << population[i] << " ";
        std::cout << '\n';
        return true;
    }
};
class Optimization : public MathBase {
private:
    std::shared_ptr<AlignedData> data;

public:
    Optimization(std::shared_ptr<AlignedData> data) : data(data) {}

    void performOptimization() {
        std::cout << "\nOptimization involves techniques like Gradient Descent, which requires detailed implementation.\n";
    }

    void displayExample() {
        std::cout << "Optimization Example:\n";
        std::cout << "-------------------\n";
        std::cout << "Optimization techniques like Gradient Descent are complex and require detailed implementation.\n";
        std::cout << "Common Use: Finding the minimum cost or maximum profit in various industries.\n";
        std::cout << "-------------------\n";
    }
};
class UniversalCalculator {
private:
    std::shared_ptr<DataManager> dataManager;

    std::unique_ptr<Arithmetic> arithmetic;
    std::unique_ptr<LinearAlgebra> linearAlgebra;
    std::unique_ptr<Calculus> calculus;
    std::unique_ptr<Statistics> statistics;
    std::unique_ptr<Probability> probability;
    std::unique_ptr<Optimization> optimization;

public:
    UniversalCalculator()
        : dataManager(std::make_shared<DataManager>()),
        arithmetic(std::make_unique<Arithmetic>(dataManager->getData())),
        linearAlgebra(std::make_unique<LinearAlgebra>(dataManager->getData())),
        calculus(std::make_unique<Calculus>(dataManager->getData())),
        statistics(std::make_unique<Statistics>(dataManager->getData())),
        probability(std::make_unique<Probability>(dataManager->getData())),
        optimization(std::make_unique<Optimization>(dataManager->getData())) {}

    void run() {
        while (true) {
            displayMenu();
            int choice = getUserChoice();
            handleChoice(choice);
        }
    }

private:
    void displayMenu() const {
        std::cout << "\nSelect the type of calculation you want to perform:\n";
        std::cout << "1. Arithmetic\n";
        std::cout << "2. Linear Algebra\n";
        std::cout << "3. Calculus\n";
        std::cout << "4. Statistics\n";
        std::cout << "5. Probability\n";
        std::cout << "6. Optimization\n";
        std::cout << "7. Show Examples of Use\n";
        std::cout << "8. Exit\n";
    }

    int getUserChoice() const {
        int choice;
        std::cin >> choice;
        return choice;
    }

    void handleChoice(int choice) const {
        switch (choice) {
        case 1:
            arithmetic->performArithmetic();
            break;
        case 2:
            linearAlgebra->performLinearAlgebra();
            break;
        case 3:
            calculus->performCalculus();
            break;
        case 4:
            statistics->performStatistics();
            break;
        case 5:
            probability->performProbability();
            break;
        case 6:
            optimization->performOptimization();
            break;
        case 7:
            displayExamples();
            break;
        case 8:
            exit(0);
        default:
            std::cout << "Invalid choice, please try again\n";
        }
    }

    void displayExamples() const {
        dataManager->printData();
        arithmetic->displayExample();
        linearAlgebra->displayExample();
        calculus->displayExample();
        statistics->displayExample();
        probability->displayExample();
        optimization->displayExample();
        dataManager->printData();
    }
};

int main() {
    UniversalCalculator calculator;
    calculator.run();
    return 0;
}
