/*
* =========================================================================================
* Name        : SubCubic.cpp
* Author      : Joseph Nguyen
* Email       : 1611657@hcmut.edu.vn
* Copyright   : Faculty of Computer Science and Engineering - Bach Khoa
* University
* Description : This is used for analysing the performance of matrix
* multiplication algorithm.
* =========================================================================================
*/

#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>

#define chronoTime std::chrono::time_point<std::chrono::system_clock>

template <class T> class matrix {
private:
  unsigned int row, col;
  T **data = new T *[row];

public:
  matrix() : row(0), col(0){};
  matrix(unsigned int userRow, unsigned int userCol)
      : row(userRow), col(userCol) {
    for (unsigned int index = 0; index < row; index++) {
      data[index] = new T[col];
    }
  }
  ~matrix() {
    for (int index = 0; index < row; index++) {
      delete[] data[index];
      data[index] = NULL;
    }
    delete[] data;
    data = NULL;
  }
  void SetSize(unsigned int userRow, unsigned int userCol) {
    matrix(userRow, userCol);
  }
  void SetRandomValue() {
    for (int index = 0; index < row; index++) {
      for (int ikimashou = 0; ikimashou < col; ikimashou++) {
        data[index][ikimashou] = (T)(rand() % 10000 + 1) / 100;
      }
    }
  }
  unsigned int GetRow() { return row; }
  unsigned int GetCol() { return col; }
  void Print() {
    for (int index = 0; index < row; index++) {
      for (int ikimashou = 0; ikimashou < col; ikimashou++) {
        std::cout << std::setw(10) << data[index][ikimashou];
      }
      std::cout << std::endl;
    }
  }
  friend matrix operator*(matrix MatB){};
  friend matrix operator+(const matrix &MatB, const matrix &MatC) {
    if (MatB.GetRow() != MatC.GetRow() || MatB.GetCol() != MatC.GetRow()) {
    } else {
      for (int index = 0; index < MatB.GetRow(); index++) {
        for (int ikimashou = 0; ikimashou < MatB.GetCol(); ikimashou++) {
          MatC.data[index][ikimashou] =
              MatC.data[index][ikimashou] + MatB.data[index][ikimashou];
        }
      }
      return MatC;
    }
  };
  friend matrix operator-(matrix MatB){};
};

int main(int argc, char **argv) {
  /*  source code for calculating execution time:
   *  http://en.cppreference.com/w/cpp/chrono
   *  require:    c++11
   *              #include <chrono>
  */
  chronoTime startTime, endTime;
  startTime = std::chrono::system_clock::now();

  srand(time(NULL));
  matrix<float> MatA(3, 3);
  MatA.SetRandomValue();
  MatA.Print();

  matrix<float> MatB(3, 3);
  MatB.SetRandomValue();
  MatB.Print();

  endTime = std::chrono::system_clock::now();

  std::chrono::duration<double> elapsed_seconds = endTime - startTime;
  std::cout << "Elapsed time: " << elapsed_seconds.count() << "s\n";
  return 0;
}