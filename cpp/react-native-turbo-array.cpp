#include "react-native-turbo-array.h"
#include <algorithm>
#include <cmath>
#include <regex>
#include <sstream>
#include <stack>

namespace turboarray {

using namespace facebook::jsi;
using namespace facebook::react;

// Expression Evaluator Implementation
double ExpressionEvaluator::evaluate(const std::string& expr, double x) {
    std::stack<double> values;
    std::stack<char> ops;
    std::string num;

    for (size_t i = 0; i < expr.length(); i++) {
        if (expr[i] == 'x') {
            values.push(x);
        }
        else if (isdigit(expr[i]) || expr[i] == '.') {
            num += expr[i];
        }
        else if (expr[i] == '(') {
            ops.push(expr[i]);
        }
        else if (expr[i] == ')') {
            if (!num.empty()) {
                values.push(std::stod(num));
                num.clear();
            }
            while (!ops.empty() && ops.top() != '(') {
                applyOperation(values, ops);
            }
            ops.pop(); // Remove '('
        }
        else if (isOperator(expr[i])) {
            if (!num.empty()) {
                values.push(std::stod(num));
                num.clear();
            }
            while (!ops.empty() && precedence(ops.top()) >= precedence(expr[i])) {
                applyOperation(values, ops);
            }
            ops.push(expr[i]);
        }
    }

    if (!num.empty()) {
        values.push(std::stod(num));
    }

    while (!ops.empty()) {
        applyOperation(values, ops);
    }

    return values.top();
}

bool ExpressionEvaluator::isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

int ExpressionEvaluator::precedence(char op) {
    if (op == '^') return 3;
    if (op == '*' || op == '/') return 2;
    if (op == '+' || op == '-') return 1;
    return 0;
}

void ExpressionEvaluator::applyOperation(std::stack<double>& values, std::stack<char>& ops) {
    double b = values.top(); values.pop();
    double a = values.top(); values.pop();
    char op = ops.top(); ops.pop();

    switch (op) {
        case '+': values.push(a + b); break;
        case '-': values.push(a - b); break;
        case '*': values.push(a * b); break;
        case '/': values.push(a / b); break;
        case '^': values.push(std::pow(a, b)); break;
    }
}

// TurboArray Implementation
TurboArray::TurboArray(std::shared_ptr<CallInvoker> jsInvoker)
    : NativeTurboArrayCxxSpec(std::move(jsInvoker)),
      expressionEvaluator_(std::make_unique<ExpressionEvaluator>()) {}

TurboArray::~TurboArray() = default;

TurboArray::Operation TurboArray::parseOperation(Runtime& rt, const Object& obj) {
    Operation op;

    if (obj.hasProperty(rt, "op")) {
        op.type = obj.getProperty(rt, "op").asString(rt).utf8(rt);
    }
    if (obj.hasProperty(rt, "value")) {
        op.value = obj.getProperty(rt, "value").asNumber();
    }
    if (obj.hasProperty(rt, "field")) {
        op.field = obj.getProperty(rt, "field").asString(rt).utf8(rt);
    }
    if (obj.hasProperty(rt, "expr")) {
        op.expression = obj.getProperty(rt, "expr").asString(rt).utf8(rt);
    }

    return op;
}

double TurboArray::evaluateOperation(const Operation& op, double value) {
    if (!op.expression.empty()) {
        return expressionEvaluator_->evaluate(op.expression, value);
    }

    if (op.type == "+") return value + op.value;
    if (op.type == "-") return value - op.value;
    if (op.type == "*") return value * op.value;
    if (op.type == "/") return value / op.value;
    if (op.type == "^") return std::pow(value, op.value);
    if (op.type == "sqrt") return std::sqrt(value);
    if (op.type == "abs") return std::abs(value);

    return value;
}

bool TurboArray::evaluateCondition(const Operation& op, double value) {
    if (!op.expression.empty()) {
        return expressionEvaluator_->evaluate(op.expression, value) != 0;
    }

    if (op.type == ">") return value > op.value;
    if (op.type == "<") return value < op.value;
    if (op.type == ">=") return value >= op.value;
    if (op.type == "<=") return value <= op.value;
    if (op.type == "==") return std::abs(value - op.value) < 1e-10;
    if (op.type == "!=") return std::abs(value - op.value) >= 1e-10;

    return false;
}

// Implement other methods (map, filter, find, reduce, etc.) following the same pattern...

} // namespace turboarray
