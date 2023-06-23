#include <gtest/gtest.h>

#include "NerualNetworkMLP/Model/GNN/GNN.h"
#include "NerualNetworkMLP/Model/MNN/MNN.h"

TEST(MatrixConstructor, Matrix_test1_standart) {
  s21::Matrix a;
  ASSERT_EQ(a.getCols(), a.getRows());
  ASSERT_EQ(a.getCols(), 1);
}

TEST(MatrixConstructor, Matrix_test2_Param) {
  ASSERT_ANY_THROW({ s21::Matrix a(0, 0); });
}

TEST(MatrixConstructor, Matrix_test3_Param) {
  ASSERT_ANY_THROW({ s21::Matrix a(-1, 1); });
}

TEST(MatrixConstructor, Matrix_test4_Param) {
  ASSERT_ANY_THROW({ s21::Matrix a(1, -1); });
}

TEST(MatrixConstructor, Matrix_test5_Param) {
  ASSERT_NO_THROW({ s21::Matrix a(1, 1); });
}

TEST(MatrixConstructor, Matrix_test6_Copy) {
  ASSERT_NO_THROW({
    s21::Matrix a(1, 1);
    a.setValue(0, 0, 1.0);
    s21::Matrix b(a);
  });
}

TEST(MatrixConstructor, Matrix_test7_Copy) {
  s21::Matrix a(1, 1);
  a.setValue(0, 0, 1.0);
  s21::Matrix b(a);
  ASSERT_NEAR(a(0, 0), b(0, 0), 1e-6);
  ASSERT_EQ(a.getCols(), b.getCols());
  ASSERT_EQ(a.getRows(), b.getRows());
}

TEST(MatrixConstructor, Matrix_test8_Move) {
  s21::Matrix a(1, 1);
  a.setValue(0, 0, 1.0);
  s21::Matrix b(std::move(a));
  ASSERT_NEAR(b(0, 0), 1.0, 1e-6);
  ASSERT_EQ(b.getCols(), 1);
  ASSERT_EQ(b.getRows(), 1);
  ASSERT_EQ(a.getCols(), 0);
  ASSERT_EQ(a.getRows(), 0);
}

TEST(Dataset, withoutException) {
  ASSERT_NO_THROW({ s21::Dataset data("../src/Tests/test1.txt"); });
}
TEST(Dataset, withException1) {
  ASSERT_ANY_THROW({ s21::Dataset data("../src/Tests/test2.txt"); });
}

TEST(Dataset, calcForBackPropagation) {
  s21::Matrix a(1, 1);
  s21::ActivateFunction func;
  a.setValue(0, 0, 0.5);
  double res1 = func.useDerivative(a)(0, 0);
  ASSERT_DOUBLE_EQ(res1, 0.25);
}

TEST(Dataset, calcForForwardPropagation) {
  s21::Matrix a(1, 1);
  s21::ActivateFunction func;
  a.setValue(0, 0, 0);
  double res1 = func.use(a)(0, 0);
  ASSERT_DOUBLE_EQ(res1, 0.5);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
