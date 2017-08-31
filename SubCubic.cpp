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
  // standard declaration with no parameter
  matrix() : row(0), col(0){};
  // initialisation with matrix row and column
  matrix(unsigned int userRow, unsigned int userCol)
      : row(userRow), col(userCol) {
    for (unsigned int index = 0; index < row; index++) {
      data[index] = new T[col];
      for (unsigned int ikimashou = 0; ikimashou < col; ikimashou++) {
        data[index][ikimashou] = 0;
      }
    }
  }
  // destructor also delete the 2d array
  ~matrix() {
    for (int index = 0; index < row; index++) {
      delete[] data[index];
      data[index] = NULL;
    }
    delete[] data;
    data = NULL;
  }
  // for which to reset the matrix size
  void SetSize(unsigned int userRow, unsigned int userCol) {
    matrix(userRow, userCol);
  }
  // set random value for whole matrix incase there a test for accuracy
  void SetRandomValue() {
    for (int index = 0; index < row; index++) {
      for (int ikimashou = 0; ikimashou < col; ikimashou++) {
        data[index][ikimashou] = (T)(rand() % 10000 + 1) / 100;
      }
    }
  }
  unsigned int GetRow() { return row; }
  unsigned int GetCol() { return col; }
  // print matrix value on screen
  void Print() {
    for (int index = 0; index < row; index++) {
      for (int ikimashou = 0; ikimashou < col; ikimashou++) {
        std::cout << std::setw(10) << data[index][ikimashou];
      }
      std::cout << std::endl;
    }
    std::cout << std::endl;
  }

  // addition for two matrix
  matrix Add(const matrix &MatB) {
    matrix MatC(MatB.row, MatB.col);
    for (int index = 0; index < MatB.row; index++) {
      for (int ikimashou = 0; ikimashou < MatB.col; ikimashou++) {
        MatC.data[index][ikimashou] =
            data[index][ikimashou] + MatB.data[index][ikimashou];
      }
    }
    return MatC;
  }
  // suctraction for two matrix
  matrix Subtract(const matrix &MatB) {
    matrix MatC(MatB.row, MatB.col);
    for (int index = 0; index < MatB.row; index++) {
      for (int ikimashou = 0; ikimashou < MatB.col; ikimashou++) {
        MatC.data[index][ikimashou] =
            data[index][ikimashou] - MatB.data[index][ikimashou];
      }
    }
    return MatC;
  }
  void operator=(matrix assignMat) {
    SetSize(assignMat.row, assignMat.col);
    for (int index = 0; index < assignMat.row; index++) {
      for (int ikimashou = 0; ikimashou < assignMat.col; ikimashou++) {
        data[index][ikimashou] = assignMat.data[index][ikimashou];
      }
    }
  }
  void BasicMultiply(const matrix &MatA, const matrix &MatB) {
    if (MatA.col == MatB.row) { // condition of multiplpication matrix
      this->SetSize(MatA.row, MatB.col);
      for (unsigned int index = 0; index < MatA.row; index++) {
        for (unsigned int ikimashou = 0; ikimashou < MatB.col; ikimashou++) {
          for (unsigned int hajimaru = 0; hajimaru < MatA.col; hajimaru++) {
            this->data[index][ikimashou] +=
                (MatA.data[index][hajimaru] * MatB.data[hajimaru][ikimashou]);
          }
        }
      }
    }
  }
  void StrassenMultiplyCore(const matrix &MatA, const matrix &MatB) {
    matrix MatC(MatB.row, MatB.row);
    if (MatB.row == 1) { // base case
      this->data[0][0] = MatA.data[0][0] * MatB.data[0][0];
    } else {
      unsigned int newSize = MatB.row / 2;
      matrix MatB11(newSize, newSize), MatB12(newSize, newSize),
          MatB21(newSize, newSize), MatB22(newSize, newSize),
          //***********************************************//
          MatA11(newSize, newSize), MatA12(newSize, newSize),
          MatA21(newSize, newSize), MatA22(newSize, newSize),
          //***********************************************//
          MatC11(newSize, newSize), MatC12(newSize, newSize),
          MatC21(newSize, newSize), MatC22(newSize, newSize);
      //***********************************************//
      for (int index = 0; index < MatB.row; index++) {
        for (int ikimashou = 0; ikimashou < MatB.row; ikimashou++) {
          if (index < newSize && ikimashou < newSize) { // top left submatrix
            MatB11.data[index][ikimashou] = MatB.data[index][ikimashou];
            MatA11.data[index][ikimashou] = MatA.data[index][ikimashou];
          } else if (index < newSize &&
                     ikimashou > newSize - 1) { // top right submatrix
            MatB12.data[index][ikimashou - newSize] =
                MatB.data[index][ikimashou];
            MatA12.data[index][ikimashou - newSize] =
                MatA.data[index][ikimashou];
          } else if (index > newSize - 1 &&
                     ikimashou < newSize) { // bottom left submatrix
            MatB21.data[index - newSize][ikimashou] =
                MatB.data[index][ikimashou];
            MatA21.data[index - newSize][ikimashou] =
                MatA.data[index][ikimashou];
          } else { // bottom right matrix
            MatB22.data[index - newSize][ikimashou - newSize] =
                MatB.data[index][ikimashou];
            MatA22.data[index - newSize][ikimashou - newSize] =
                MatA.data[index][ikimashou];
          }
        }
      }

      // according to Strassen work, he found there are 7 equations to calculate
      // that is able to multiply matrix
      matrix *P = new matrix[7];
      for (unsigned int kitta = 0; kitta < 7; kitta++)
        P[kitta].SetSize(newSize, newSize);

      // P0 = A11*(B12-B22) //
      P[0].StrassenMultiplyCore(MatA11, MatB12.Subtract(MatB22));
      // P1 = A11*(A11+B22) //
      P[1].StrassenMultiplyCore(MatA11.Add(MatA12), MatB22);
      // P2 = A21*(A22+B11) //
      P[2].StrassenMultiplyCore(MatA21.Add(MatA22), MatB11);
      // P3 = A22*(B21-B11) //
      P[3].StrassenMultiplyCore(MatA22, MatB21.Subtract(MatB11));
      // P4 = (A11+A22)*(B11+B22) //
      P[4].StrassenMultiplyCore(MatA11.Add(MatA22), MatB11.Add(MatB22));
      // P5 = (A12-A22)*(B21-B22) //
      P[5].StrassenMultiplyCore(MatA12.Subtract(MatA22), MatB21.Add(MatB22));
      // P6 = (A11-A21)*(B11+B12) //
      P[6].StrassenMultiplyCore(MatA11.Subtract(MatA21), MatB11.Add(MatB12));

      // 4 submatrices of result matrix are calculated as below
      // how did Strassen think?
      MatC11 = P[4].Add(P[3]);
      MatC11 = MatC11.Subtract(P[1]);
      MatC11 = MatC11.Add(P[5]);

      MatC12 = P[0].Add(P[1]);

      MatC21 = P[2].Add(P[3]);

      MatC22 = P[4].Add(P[0]);
      MatC22 = MatC22.Subtract(P[2]);
      MatC22 = MatC22.Subtract(P[6]);

      // assign 4 submatrices to the result matrix
      for (int index = 0; index < MatB.row; index++) {
        for (int ikimashou = 0; ikimashou < MatB.row; ikimashou++) {
          if (index < newSize && ikimashou < newSize) { // top left submatrix
            this->data[index][ikimashou] = MatC11.data[index][ikimashou];
          } else if (index < newSize &&
                     ikimashou > newSize - 1) { // top right matrix
            this->data[index][ikimashou] =
                MatC12.data[index][ikimashou - newSize];
          } else if (index > newSize - 1 &&
                     ikimashou < newSize) { // bottom left matrix
            this->data[index][ikimashou] =
                MatC21.data[index - newSize][ikimashou];
          } else { // bottom right matrix
            this->data[index][ikimashou] =
                MatC22.data[index - newSize][ikimashou - newSize];
          }
        }
      }
    }
  }
  bool ChechDoublePower(unsigned int size) {
    while (size != 2) {
      size /= 2;
      if (size % 2 == 1)
        return false;
    }
    return true;
  }
  void StrassenMultiply(const matrix &MatA, const matrix &MatB) {
    // strassen algorithm
    // for square matrix with edge of 2^n only
    // time elapsed: n^(log_2(7))

    unsigned int size = MatB.row;

    // check if matrix is square
    if (MatB.row != MatB.col || MatA.row != MatA.col) {
      std::cout << "Cannot perform." << std::endl;
    } else {
      // check if matrix size is 2^n
      if (!ChechDoublePower(size)) {
        std::cout << "Must be n^2 matrix size." << std::endl;
        return;
      }

      // resize the original matrix to fit the result
      this->SetSize(size, size);

      // go to the strassen algorithm
      this->StrassenMultiplyCore(MatA, MatB);
    }
  }
};

int main(int argc, char **argv) {
  /*  source code for calculating execution time:
   *  http://en.cppreference.com/w/cpp/chrono
   *  require:    c++11
   *              #include <chrono>
  */
  chronoTime startTime, endTime;

  srand(time(NULL));
  unsigned int userSize = 0;
  std::cout << "Size of square matrix: ";
  std::cin >> userSize;

  unsigned int selection;
  std::cout << "Select algorithm: 1 for Naive, 2 for Strassen";
  std::cin >> selection;

  matrix<int> MatA(userSize, userSize);
  MatA.SetRandomValue();

  matrix<int> MatB(userSize, userSize);
  MatB.SetRandomValue();

  startTime = std::chrono::system_clock::now();

  switch (selection) {
  case 1: {
    matrix<int> MatD(userSize,userSize);
    MatD.BasicMultiply(MatA, MatB);
    break;
  }
  case 2:{
    matrix<int> MatC(userSize, userSize);
    MatC.StrassenMultiply(MatA, MatB);
    break;
  }
  }
  endTime = std::chrono::system_clock::now();

  std::chrono::duration<double> elapsed_seconds = endTime - startTime;
  std::cout << "Elapsed time: " << elapsed_seconds.count() << "s\n";
  return 0;
}