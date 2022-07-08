#ifndef DATASET_H
#define DATASET_H
#include <vector>
#include <iostream>
#pragma once
#include <fstream>
#include <string>
#include <sstream>
#include <QDebug>
#include "constantValues.h"
namespace s21{

class Image{
public:
    Image()=default;
    Image(std::stringstream& imageString);

    double pixel(int i)const;
    std::array<double,NUM_OF_PIXELS>::const_iterator cbegin()const;

    std::array<double,NUM_OF_PIXELS>::const_iterator cend()const;
private:
    std::array<double,NUM_OF_PIXELS> _pixels;
};

class Dataset
{
private:
    void parse(std::string& filename);

    std::vector<Image> _images;
    std::vector<int> _answers;
public:
    Dataset();
    explicit Dataset(std::string& filename);

    void setDate(std::string& filename);

    const Image& getImage(int i)const;
    int getAnswer(int i)const;

    int getSize()const;
};
}    //     namespace s21
#endif // DATASET_H
