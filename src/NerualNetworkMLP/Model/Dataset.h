#pragma once
#include <array>
#include <fstream>
#include <initializer_list>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "constantValues.h"
namespace s21 {

class Image {
 public:
    Image() = default;
    explicit Image(std::array<double, NUM_OF_PIXELS> values) : _pixels(values) {}
    explicit Image(std::stringstream& imageString);

    double pixel(int i) const;
    std::array<double, NUM_OF_PIXELS>::const_iterator cbegin() const;

    std::array<double, NUM_OF_PIXELS>::const_iterator cend() const;
    bool operator==(const Image& b) const { return _pixels == b._pixels; }
    void setValue(int i, double value) { _pixels[i] = value; }

 private:
    std::array<double, NUM_OF_PIXELS> _pixels;
};

class Dataset {
 private:
    void parse(const std::string& filename);

    std::vector<Image> _images;
    std::vector<int> _answers;

 public:
    Dataset();
    explicit Dataset(const std::string& filename);

    void setDate(const std::string& filename);

    const Image& getImage(int i) const;
    int getAnswer(int i) const;

    int getSize() const;
};
}  //     namespace s21
