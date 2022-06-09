#ifndef ACTICATEFUNCTION_H
#define ACTICATEFUNCTION_H
#include <functional>
#include <math.h>
#include "Matrix.h"
namespace s21{

enum class typeFunction{SIGMOIND=1};

class ActicateFunction
{
private:
    std::function<double(double)> _function;
    std::function<double(double)> _derivative;
public:
    explicit ActicateFunction(typeFunction type=typeFunction::SIGMOIND);
    double use(double arg);
    Matrix use(Matrix& arg);
    double useDerivative(double arg);
    Matrix useDerivative(Matrix& arg);
};

}    //     namespace s21;

#endif // ACTICATEFUNCTION_H
