#include <gtest/gtest.h>
#include "NerualNetworkMLP/Model/Dataset.h"

TEST(Dataset_Tests, ReadImageNoExcept) {
    std::array<double,NUM_OF_PIXELS> arrayResult={  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                                                    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,20,
                                                    27,8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,33,84,169,190,126,33,
                                                    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,47,190,233,251,253,244,163,33,
                                                    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,20,67,175,247,254,254,254,254,244,127,
                                                    10,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,45,122,231,253,254,255,255,254,251,175,
                                                    34,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,114,203,254,254,254,253,254,254,254,243,
                                                    113,32,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,22,145,222,254,253,228,218,242,254,254,243,
                                                    113,32,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,110,232,249,253,219,126,213,246,254,252,177,
                                                    34,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,21,172,252,254,232,98,91,233,252,254,245,115,
                                                    4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,32,203,254,254,209,54,118,245,254,254,232,82,2,
                                                    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,37,217,254,250,142,77,188,252,254,252,172,22,0,0,
                                                    0,0,0,0,0,0,0,0,0,0,0,0,0,0,37,214,232,207,111,177,250,254,254,250,130,5,0,0,0,
                                                    0,0,0,0,0,0,0,0,0,0,0,0,0,20,138,93,51,119,243,254,255,255,252,173,22,0,0,0,0,0,
                                                    0,0,0,0,0,0,0,0,0,0,0,1,15,6,4,93,236,254,254,254,254,232,100,32,17,0,0,0,0,0,0,
                                                    0,0,0,0,0,0,0,0,0,0,0,1,53,165,215,222,233,251,253,232,152,75,2,0,0,0,0,0,0,0,0,
                                                    0,0,0,0,0,0,0,0,0,18,81,125,140,173,232,253,250,170,81,2,0,0,0,0,0,0,0,0,0,0,0,
                                                    0,0,0,0,0,0,0,2,4,9,22,100,230,250,188,108,9,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                                                    0,0,0,0,0,20,111,190,243,218,77,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                                                    7,115,242,243,112,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,33,160,188,
                                                    51,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,92,145,50,0,0,0,0,0,0,0,
                                                    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,33,106,106,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                                                    0,0,0,0,0,0,0,0,0,0,8,42,112,15,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                                                    0,0,5,24,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                                                    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,9};
    s21::Dataset data;
    s21::Image imageFromFile(arrayResult);
    std::string filePathWithData = "/Users/jcraster/MLP/src/Tests/test1.txt";
    data.setDate(filePathWithData);
    if(data.getImage(0)==imageFromFile && data.getAnswer(0)==0){
        ASSERT_EQ(1,1);
    }
}

TEST(Dataset_Tests, ReadFileDataException) {
    s21::Dataset data;
    std::string filePathWithData = "/Users/jcraster/MLP/src/Tests/test2.txt";
    ASSERT_ANY_THROW({data.setDate(filePathWithData);});
}

TEST(Dataset_Tests, ReadFileImageException) {
    s21::Dataset data;
    std::string filePathWithData = "/Users/jcraster/MLP/src/Tests/test3.txt";
    ASSERT_ANY_THROW({data.setDate(filePathWithData);});
}

TEST(Dataset_Tests, ReadFileImageException2) {
    s21::Dataset data;
    std::string filePathWithData = "/Users/jcraster/MLP/src/Tests/test4.txt";
    ASSERT_ANY_THROW({data.setDate(filePathWithData);});
}


int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}