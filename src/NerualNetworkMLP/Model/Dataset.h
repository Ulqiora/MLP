#ifndef DATASET_H
#define DATASET_H
#include <QFile>
#include <QString>
#include <vector>
#include <fstream>
#include <sstream>
namespace s21{
enum {NUM_OF_PIXELS=784};
struct Image{
    char _symbol;
    int _pixels[NUM_OF_PIXELS];
};

class Dataset
{
private:
    std::vector<Image> _data;
    void parseImage(const QString& filename){
        std::ifstream file(filename.toStdString());
        std::stringstream ss;
        std::string currentLine="", prefix="";
        if(file.is_open()) throw std::invalid_argument("Error load dataset!");
        while(std::getline(file,currentLine)){
            ss.clear();
            ss.str(currentLine);

        }
    }
public:
    explicit Dataset(const QString& filename){
        parseImage(filename);
    }
    Image& operator()(int i);
};
}    //     namespace s21
#endif // DATASET_H
