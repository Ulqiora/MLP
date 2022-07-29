#pragma once
#include <array>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <initializer_list>
#include <sstream>
//#include <QDebug>
#include "constantValues.h"
namespace s21{

class Image{
public:
    Image()=default;
    Image(std::array<double,NUM_OF_PIXELS> values):_pixels(values){}
    Image(std::stringstream& imageString);

    double pixel(int i)const;
    std::array<double,NUM_OF_PIXELS>::const_iterator cbegin()const;

    std::array<double,NUM_OF_PIXELS>::const_iterator cend()const;
    bool operator==(const Image& b)const {
        return _pixels==b._pixels;
    }
    void setValue(int i,double value){
        _pixels[i]=value;
    }
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
