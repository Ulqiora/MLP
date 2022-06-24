#ifndef DATASET_H
#define DATASET_H
#include <vector>
#include <iostream>
#pragma once
#include <fstream>
#include <string>
#include <sstream>
#include "constantValues.h"
namespace s21{

class Image{
public:
    Image()=default;
    Image(std::stringstream& imageString){
        for(int i=0;i<NUM_OF_PIXELS;++i){
            imageString>>_pixels[i];
            if(imageString.peek()!=','||(imageString.peek()!='\n' && i==NUM_OF_PIXELS-1)){
                throw std::invalid_argument("Error load dataset!");
            }
        }
    }

    double& operator()(int i){
        return _pixels[i];
    }
private:
    double _pixels[NUM_OF_PIXELS];
};

class Dataset
{
private:
    void parse(std::string& filename){
        std::ifstream file(filename);
        std::stringstream ss;
        std::string currentLine="fsda";
        int imageInfo;
        if(!file.is_open()) {
            throw std::invalid_argument("Error load dataset!");
        }
        while(std::getline(file,currentLine)){
            ss.clear();
            ss.str(currentLine);
            ss>>imageInfo;
            _answers.push_back(imageInfo);
            if(ss.peek()!=',')
                throw std::invalid_argument("Error,wrong file!");
            try {
                _images.push_back(Image(ss));
            }  catch (std::exception& e) {
                throw;
            }

        }
        file.close();
    }
    std::vector<Image> _images;
    std::vector<int> _answers;
public:
    explicit Dataset(std::string& filename):_images(0),_answers(0){
        try {
            parse(filename);
        }  catch (std::exception& e) {
            throw;
        }
    }

    Image& getImage(int i){
        return _images[i];
    }
    int& getAnswer(int i){
        return _answers[i];
    }
};
}    //     namespace s21
#endif // DATASET_H
