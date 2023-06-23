#ifndef SRC_NERUALNETWORKMLP_MODEL_ACTIVATEFUNCTION_H_
#define SRC_NERUALNETWORKMLP_MODEL_ACTIVATEFUNCTION_H_
#include <cmath>
#include <functional>

#include "MNN/Matrix.h"
namespace s21 {

enum class typeFunction { SIGMOIND = 0 };

class ActivateFunction {
 private:
    std::function<double(double)> _function;
    std::function<double(double)> _derivative;

 public:
    explicit ActivateFunction(typeFunction type = typeFunction::SIGMOIND);
    double use(double arg);
    Matrix use(const Matrix& arg);
    double useDerivative(double arg);
    Matrix useDerivative(const Matrix& arg);
};

}  // namespace s21

#endif  // SRC_NERUALNETWORKMLP_MODEL_ACTIVATEFUNCTION_H_
