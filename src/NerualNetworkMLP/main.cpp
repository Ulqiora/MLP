#include "Model/Dataset.h"
int main()
{
    std::string str("../../datasets/emnist-letters/emnist-letters-train.csv");
    s21::Dataset dataset(str);
    std::cout<<dataset._data[0]._pixels[86];
    return 0;
}
