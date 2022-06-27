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
    Image(std::stringstream& imageString){
        for(int i=0;i<NUM_OF_PIXELS;++i){
            imageString>>_pixels[i];
            _pixels[i]=_pixels[i]/255.0;
            if(imageString.peek()==',' && i!=NUM_OF_PIXELS-1){
                imageString.ignore();
            }else if(!(imageString.eof() || imageString.peek()=='\r')){
                qDebug()<<"|"<<imageString.peek()<<"|";
                throw std::invalid_argument("Error, wrong file format");
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
        std::string currentLine="";
        int imageInfo;
        if(!file.is_open()) {
            qDebug()<<"Error load dataset!";
            throw std::invalid_argument("Error load dataset!");
        }
        while(std::getline(file,currentLine)){
            ss.clear();
            ss.str(currentLine);
            ss>>imageInfo;
            _answers.push_back(imageInfo);
            if(ss.peek()!=','){
                qDebug()<<"Error,wrong file!1";
                throw std::invalid_argument("Error,wrong file!1");
            }
            ss.ignore();
            try {
                _images.push_back(Image(ss));
            }  catch (std::exception& e) {
                throw e;
            }

        }
        file.close();
    }
    std::vector<Image> _images;
    std::vector<int> _answers;
public:
    Dataset():_images(0),_answers(0){}
    explicit Dataset(std::string& filename):_images(0),_answers(0){
        try {
            parse(filename);
        }  catch (std::exception& e) {
            throw std::invalid_argument("Error,wrong file!1");
        }
    }

    void setDate(std::string& filename){
        _images.clear();
        _answers.clear();
        try {
            parse(filename);
        }  catch (std::exception& e) {
            throw e;
        }
    }

    Image& getImage(int i){
        return _images[i];
    }
    int& getAnswer(int i){
        return _answers[i];
    }

    int getSize(){
        return _answers.size();
    }
};
}    //     namespace s21
#endif // DATASET_H
