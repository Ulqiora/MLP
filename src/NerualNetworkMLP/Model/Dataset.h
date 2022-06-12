#ifndef DATASET_H
#define DATASET_H
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
namespace s21{
enum {NUM_OF_PIXELS=784};
struct Image{
    int _numOfSymbol;
    double _pixels[NUM_OF_PIXELS];
};

class Dataset
{
private:
    void parseImage(std::string& filename){
        std::ifstream file(filename);
        std::stringstream ss;
        std::string currentLine="fsda";
        int imageInfo=5;
        if(!file.is_open()) throw std::invalid_argument("Error load dataset!");
        while(std::getline(file,currentLine)){
            ss.clear();
            ss.str(currentLine);
            Image photo;
            for(int i = 0;i <= NUM_OF_PIXELS; i++){
                ss >> imageInfo;
                if(i > 0){
                    photo._pixels[i-1]=imageInfo;
                } else {
                    photo._numOfSymbol=imageInfo;
                }
                if(ss.peek() == ','){
                    ss.ignore();
                } else if(!(ss.eof() && i==NUM_OF_PIXELS)){
                    std::cout<<ss.eof()<<std::endl<<i;
                    throw std::invalid_argument("this file is not in the correct format!");
                }
            }
            _data.push_back(photo);
        }
        file.close();
    }
public:
    explicit Dataset(std::string& filename):_data(0){
        parseImage(filename);
    }
    std::vector<Image> _data;
    Image& operator()(int i){
        return _data[i];
    }
};

}    //     namespace s21
#endif // DATASET_H
