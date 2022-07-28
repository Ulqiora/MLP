#include "Dataset.h"
namespace s21 {
Image::Image(std::stringstream &imageString) {
    double pixel = 0.0;
    for (int i = 0; i < NUM_OF_PIXELS; ++i) {
        if(i==783)
            std::cout<<"au";
        imageString >> pixel;
        _pixels[i] = pixel / 255.0;
        if (imageString.peek() == ',' && i != NUM_OF_PIXELS - 1) {
            imageString.ignore();
        } else if (imageString.eof() || imageString.peek() == '\r' || imageString.peek()==(-1)) {
            qDebug()<<"ALO:"<<imageString.peek();
            throw std::invalid_argument("Error, wrong file format");
        }
    }
}

double Image::pixel(int i) const { return _pixels[i]; }

std::array<double, NUM_OF_PIXELS>::const_iterator Image::cbegin() const { return _pixels.cbegin(); }

std::array<double, NUM_OF_PIXELS>::const_iterator Image::cend() const { return _pixels.cend(); }

void Dataset::parse(std::string &filename) {
    std::ifstream file(filename);
    std::stringstream ss;
    std::string currentLine = "";
    int imageInfo;
    if (!file.is_open()) {
        throw std::invalid_argument("Error load dataset!");
    }
    while (std::getline(file, currentLine)) {
        ss.clear();
        ss.str(currentLine);
        ss >> imageInfo;
        _answers.push_back(imageInfo - 1);
        if (ss.peek() != ',') {
            throw std::invalid_argument("Error,wrong file!1");
        }
        ss.ignore();
        try {
            _images.push_back(Image(ss));
        } catch (std::exception &e) {
            throw e;
        }
    }
    file.close();
}

Dataset::Dataset() : _images(0), _answers(0) {}
Dataset::Dataset(std::string &filename) : Dataset() {
    try {
        parse(filename);
    } catch (std::exception &e) {
        throw e;
    }
}

void Dataset::setDate(std::string &filename) {
    _images.clear();
    _answers.clear();
    try {
        parse(filename);
    } catch (std::exception &e) {
        throw e;
    }
}

const Image &Dataset::getImage(int i) const { return _images[i]; }
int Dataset::getAnswer(int i) const { return _answers[i]; }

int Dataset::getSize() const { return _answers.size(); }
}
