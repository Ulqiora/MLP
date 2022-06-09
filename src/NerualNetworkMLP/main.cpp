#include "Model/Matrix.h"
int main()
{
    s21::Matrix a(2,10);
    a.setRandom();
    a.setValueForAll(1.023);
    a.print();
    return 0;
}
