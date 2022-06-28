#include "ActivateFunction.h"

namespace  s21{

double Sigmoind::use(double& arg){
    return (1.0/1.0+std::exp(arg));
}

Matrix Sigmoind::use(Matrix& arg){
    int rows=arg.getRows(),cols=arg.getCols();
    Matrix result(rows,cols);
    for(int i=0;i<rows;i++){
        for(int j=0;j<cols;j++){
            result(i,j)=use(arg(i,j));
        }
    }
    return result;
}

double Sigmoind::useDerivative(double& arg){
    return use(arg)*(1.0-use(arg));
}

Matrix Sigmoind::useDerivative(Matrix& arg){
    int rows=arg.getRows(),cols=arg.getCols();
    Matrix result(rows,cols);
    for(int i=0;i<rows;i++){
        for(int j=0;j<cols;j++){
            result(i,j)=use(arg(i,j));
        }
    }
    return result;
}
}
