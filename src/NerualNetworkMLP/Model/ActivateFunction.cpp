#include "ActivateFunction.h"

namespace  s21{
ActivateFunction::ActivateFunction(typeFunction type)
{
    if(type==typeFunction::SIGMOIND){
        _function=[](double x){return 1/(1+std::exp(-x));};
        _derivative=[this](double x){return _function(x)*(1-_function(x));};
    }
}
double ActivateFunction::use(double arg){
    return _function(arg);
}

Matrix ActivateFunction::use(Matrix& arg){
    int rows=arg.getRows(),cols=arg.getCols();
    Matrix result(rows,cols);
    for(int i=0;i<rows;i++){
        for(int j=0;j<cols;j++){
            result(i,j)=_function(arg(i,j));
        }
    }
    return result;
}

double ActivateFunction::useDerivative(double arg){
    return _derivative(arg);
}

Matrix ActivateFunction::useDerivative(Matrix& arg){
    int rows=arg.getRows(),cols=arg.getCols();
    Matrix result(rows,cols);
    for(int i=0;i<rows;i++){
        for(int j=0;j<cols;j++){
            result(i,j)=_derivative(arg(i,j));
        }
    }
    return result;
}
}
