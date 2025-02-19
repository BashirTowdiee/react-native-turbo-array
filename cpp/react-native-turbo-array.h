#ifndef TURBOARRAY_H
#define TURBOARRAY_H

#include <AppSpecsJSI.h>
#include <memory>
#include <string>
#include <vector>
#include <map>
#include <functional>

namespace turboarray {

// Forward declarations
class ExpressionEvaluator;

class TurboArray : public NativeTurboArrayCxxSpec<TurboArray> {
public:
    TurboArray(std::shared_ptr<facebook::react::CallInvoker> jsInvoker);
    ~TurboArray();

    // Core array operations with JSI support
    std::vector<double> map(facebook::jsi::Runtime& rt, std::vector<double> array, facebook::jsi::Object operation);
    std::vector<double> filter(facebook::jsi::Runtime& rt, std::vector<double> array, facebook::jsi::Object condition);
    double find(facebook::jsi::Runtime& rt, std::vector<double> array, facebook::jsi::Object condition);
    double reduce(facebook::jsi::Runtime& rt, std::vector<double> array, facebook::jsi::Object operation, double initialValue);

    // Advanced operations
    facebook::jsi::Object groupBy(facebook::jsi::Runtime& rt, std::vector<double> array, facebook::jsi::Object key);
    std::vector<double> sortBy(facebook::jsi::Runtime& rt, std::vector<double> array, facebook::jsi::Object comparator);
    std::vector<double> chain(facebook::jsi::Runtime& rt, std::vector<double> array, facebook::jsi::Array operations);
    facebook::jsi::Object aggregate(facebook::jsi::Runtime& rt, std::vector<double> array, std::vector<std::string> operations);

private:
    // Operation structure for internal use
    struct Operation {
        std::string type;
        double value{0.0};
        std::string field;
        std::string expression;
    };

    // Helper methods
    Operation parseOperation(facebook::jsi::Runtime& rt, const facebook::jsi::Object& obj);
    double evaluateOperation(const Operation& op, double value);
    bool evaluateCondition(const Operation& op, double value);
    std::function<double(double)> createMapFunction(const Operation& op);
    std::function<bool(double)> createFilterFunction(const Operation& op);

    // Expression evaluator instance
    std::unique_ptr<ExpressionEvaluator> expressionEvaluator_;
};

// Expression evaluator class declaration
class ExpressionEvaluator {
public:
    double evaluate(const std::string& expr, double x);

private:
    bool isOperator(char c);
    int precedence(char op);
    void applyOperation(std::stack<double>& values, std::stack<char>& ops);
};

} // namespace turboarray

#endif /* TURBOARRAY_H */
