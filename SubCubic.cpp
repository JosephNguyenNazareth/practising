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
#include <sstream>
#include <string>

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
  void SetValue(T **ReadValue, unsigned int ReadRow, unsigned int ReadCol) {
    for (int index = 0; index < row; index++) {
      for (int ikimashou = 0; ikimashou < col; ikimashou++) {
        data[index][ikimashou] = ReadValue[index][ikimashou];
      }
    }
  }
  // read value from file to test
  T **ReadValueFromFile(const unsigned int &size) {
    // create new matrix value
    T **Matrix = new T *[size];
    for (unsigned int ikimashou = 0; ikimashou < size; ikimashou++) {
      Matrix[ikimashou] = new T[size];
    }

    // read file
    std::string ReadValue;
    for (unsigned int index = 0; index < size; index++) {
      std::getline(std::cin, ReadValue);
      std::stringstream read_detail(ReadValue);
      for (unsigned int step = 0; step < size; step++) {
        read_detail >> Matrix[index][step];
      }
    }
    // skip last blank line
    std::getline(std::cin, ReadValue);
    return Matrix;
  }
  // print matrix value on screen
  void Print() {
    for (int index = 0; index < row; index++) {
      for (int ikimashou = 0; ikimashou < col; ikimashou++) {
        std::cout << std::setw(7) << data[index][ikimashou];
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

      for (int index = 0; index < newSize; index++) {
        for (int ikimashou = 0; ikimashou < newSize; ikimashou++) {

          // top left
          MatB11.data[index][ikimashou] = MatB.data[index][ikimashou];
          MatA11.data[index][ikimashou] = MatA.data[index][ikimashou];

          // top right
          MatB12.data[index][ikimashou] = MatB.data[index][ikimashou + newSize];
          MatA12.data[index][ikimashou] = MatA.data[index][ikimashou + newSize];

          // bottom left
          MatB21.data[index][ikimashou] = MatB.data[index + newSize][ikimashou];
          MatA21.data[index][ikimashou] = MatA.data[index + newSize][ikimashou];

          // bottom right
          MatB22.data[index][ikimashou] =
              MatB.data[index + newSize][ikimashou + newSize];
          MatA22.data[index][ikimashou] =
              MatA.data[index + newSize][ikimashou + newSize];
        }
      }

      // according to Strassen work, he found there are 7 equations to calculate
      // that is able to multiply matrix
      matrix P0(newSize, newSize), P1(newSize, newSize), P2(newSize, newSize),
          P3(newSize, newSize), P4(newSize, newSize), P5(newSize, newSize),
          P6(newSize, newSize);

      // P0 = A11*(B12-B22) //
      P0.StrassenMultiplyCore(MatA11, MatB12.Subtract(MatB22));

      // P1 = A11*(A11+B22) //
      P1.StrassenMultiplyCore(MatA11.Add(MatA12), MatB22);

      // P2 = A21*(A22+B11) //
      P2.StrassenMultiplyCore(MatA21.Add(MatA22), MatB11);

      // P3 = A22*(B21-B11) //
      P3.StrassenMultiplyCore(MatA22, MatB21.Subtract(MatB11));

      // P4 = (A11+A22)*(B11+B22) //
      P4.StrassenMultiplyCore(MatA11.Add(MatA22), MatB11.Add(MatB22));

      // P5 = (A12-A22)*(B21-B22) //
      P5.StrassenMultiplyCore(MatA12.Subtract(MatA22), MatB21.Add(MatB22));

      // P6 = (A11-A21)*(B11+B12) //
      P6.StrassenMultiplyCore(MatA11.Subtract(MatA21), MatB11.Add(MatB12));

      // 4 submatrices of result matrix are calculated as below
      // how did Strassen think?
      MatC11 = ((P4.Add(P3)).Subtract(P1)).Add(P5);
      MatC12 = P0.Add(P1);
      MatC21 = P2.Add(P3);
      MatC22 = ((P4.Add(P0)).Subtract(P2)).Subtract(P6);

      // assign 4 submatrices to the result matrix
      for (int index = 0; index < newSize; index++) {
        for (int ikimashou = 0; ikimashou < newSize; ikimashou++) {
          // top left submatrix
          this->data[index][ikimashou] = MatC11.data[index][ikimashou];
          // top right matrix
          this->data[index][ikimashou + newSize] =
              MatC12.data[index][ikimashou];
          // bottom left matrix
          this->data[index + newSize][ikimashou] =
              MatC21.data[index][ikimashou];
          // bottom right matrix
          this->data[index + newSize][ikimashou + newSize] =
              MatC22.data[index][ikimashou];
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
  void ParallelAdd(const matrix &MatB) {
    if (MatB.row == 1)
      this->data[0][0] += MatB.data[0][0];
    else {
      unsigned int newSize = MatB.row / 2;
      matrix MatB11(newSize, newSize), MatB12(newSize, newSize),
          MatB21(newSize, newSize), MatB22(newSize, newSize),

          //***********************************************//

          MatA11(newSize, newSize), MatA12(newSize, newSize),
          MatA21(newSize, newSize), MatA22(newSize, newSize);

      for (int index = 0; index < newSize; index++) {
        for (int ikimashou = 0; ikimashou < newSize; ikimashou++) {

          // top left
          MatB11.data[index][ikimashou] = MatB.data[index][ikimashou];
          MatA11.data[index][ikimashou] = this->data[index][ikimashou];

          // top right
          MatB12.data[index][ikimashou] = MatB.data[index][ikimashou + newSize];
          MatA12.data[index][ikimashou] =
              this->data[index][ikimashou + newSize];

          // bottom left
          MatB21.data[index][ikimashou] = MatB.data[index + newSize][ikimashou];
          MatA21.data[index][ikimashou] =
              this->data[index + newSize][ikimashou];

          // bottom right
          MatB22.data[index][ikimashou] =
              MatB.data[index + newSize][ikimashou + newSize];
          MatA22.data[index][ikimashou] =
              this->data[index + newSize][ikimashou + newSize];
        }
      }
      MatB11.ParallelAdd(MatA11);
      MatB12.ParallelAdd(MatA12);
      MatB21.ParallelAdd(MatA21);
      MatB22.ParallelAdd(MatA22);

      for (int index = 0; index < newSize; index++) {
        for (int ikimashou = 0; ikimashou < newSize; ikimashou++) {
          // top left submatrix
          this->data[index][ikimashou] = MatB11.data[index][ikimashou];
          // top right matrix
          this->data[index][ikimashou + newSize] =
              MatB12.data[index][ikimashou];
          // bottom left matrix
          this->data[index + newSize][ikimashou] =
              MatB21.data[index][ikimashou];
          // bottom right matrix
          this->data[index + newSize][ikimashou + newSize] =
              MatB22.data[index][ikimashou];
        }
      }
    }
  }
  void ParallelMultiply(const matrix &MatA, const matrix &MatB) {
    if (MatA.row == 1)
      this->data[0][0] = MatA.data[0][0] * MatB.data[0][0];
    else {
      unsigned int newSize = MatB.row / 2;
      matrix MatB11(newSize, newSize), MatB12(newSize, newSize),
          MatB21(newSize, newSize), MatB22(newSize, newSize),

          //***********************************************//

          MatA11(newSize, newSize), MatA12(newSize, newSize),
          MatA21(newSize, newSize), MatA22(newSize, newSize),

          //***********************************************//

          MatT(MatB.row, MatB.row), MatT11(newSize, newSize),
          MatT12(newSize, newSize), MatT21(newSize, newSize),
          MatT22(newSize, newSize),

          //***********************************************//

          MatC11(newSize, newSize), MatC12(newSize, newSize),
          MatC21(newSize, newSize), MatC22(newSize, newSize);

      for (int index = 0; index < newSize; index++) {
        for (int ikimashou = 0; ikimashou < newSize; ikimashou++) {

          // top left
          MatB11.data[index][ikimashou] = MatB.data[index][ikimashou];
          MatA11.data[index][ikimashou] = MatA.data[index][ikimashou];

          // top right
          MatB12.data[index][ikimashou] = MatB.data[index][ikimashou + newSize];
          MatA12.data[index][ikimashou] = MatA.data[index][ikimashou + newSize];

          // bottom left
          MatB21.data[index][ikimashou] = MatB.data[index + newSize][ikimashou];
          MatA21.data[index][ikimashou] = MatA.data[index + newSize][ikimashou];

          // bottom right
          MatB22.data[index][ikimashou] =
              MatB.data[index + newSize][ikimashou + newSize];
          MatA22.data[index][ikimashou] =
              MatA.data[index + newSize][ikimashou + newSize];
        }
      }

      MatC11.ParallelMultiply(MatA11, MatB11);
      MatC12.ParallelMultiply(MatA11, MatB12);
      MatC21.ParallelMultiply(MatA21, MatB11);
      MatC22.ParallelMultiply(MatA21, MatB12);
      MatT11.ParallelMultiply(MatA12, MatB21);
      MatT12.ParallelMultiply(MatA12, MatB22);
      MatT21.ParallelMultiply(MatA22, MatB21);
      MatT22.ParallelMultiply(MatA22, MatB22);

      for (int index = 0; index < newSize; index++) {
        for (int ikimashou = 0; ikimashou < newSize; ikimashou++) {
          // top left submatrix
          this->data[index][ikimashou] = MatC11.data[index][ikimashou];
          MatT.data[index][ikimashou] = MatT11.data[index][ikimashou];
          // top right matrix
          this->data[index][ikimashou + newSize] =
              MatC12.data[index][ikimashou];
          MatT.data[index][ikimashou + newSize] = MatT12.data[index][ikimashou];
          // bottom left matrix
          this->data[index + newSize][ikimashou] =
              MatC21.data[index][ikimashou];
          MatT.data[index + newSize][ikimashou] = MatT21.data[index][ikimashou];
          // bottom right matrix
          this->data[index + newSize][ikimashou + newSize] =
              MatC22.data[index][ikimashou];
          MatT.data[index + newSize][ikimashou + newSize] =
              MatT22.data[index][ikimashou];
        }
      }

      this->ParallelAdd(MatT);
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
  unsigned int userSize = 128;

  matrix<int> MatA(userSize, userSize);
  MatA.SetValue(MatA.ReadValueFromFile(userSize), userSize, userSize);
  // MatA.SetRandomValue();
  // MatA.Print();

  matrix<int> MatB(userSize, userSize);
  MatB.SetValue(MatB.ReadValueFromFile(userSize), userSize, userSize);
  // MatB.SetRandomValue();
  // MatB.Print();

  // basic algorithm computing
  startTime = std::chrono::system_clock::now();

  matrix<int> MatD(userSize, userSize);
  MatD.BasicMultiply(MatA, MatB);

  endTime = std::chrono::system_clock::now();

  std::chrono::duration<double> elapsed_seconds = endTime - startTime;
  std::cout << "Elapsed time: " << elapsed_seconds.count() << "s\n";

  // strassen algorithm computing
  startTime = std::chrono::system_clock::now();

  matrix<int> MatC(userSize, userSize);
  MatC.StrassenMultiply(MatA, MatB);

  endTime = std::chrono::system_clock::now();

  elapsed_seconds = endTime - startTime;
  std::cout << "Elapsed time: " << elapsed_seconds.count() << "s\n";

  // parallel algorithm computing
  startTime = std::chrono::system_clock::now();

  matrix<int> MatE(userSize, userSize);
  MatE.ParallelMultiply(MatA, MatB);

  endTime = std::chrono::system_clock::now();

  elapsed_seconds = endTime - startTime;
  std::cout << "Elapsed time: " << elapsed_seconds.count() << "s\n";
  //*/
  system("pause");
  return 0;
}