#include <vector>
#include <iostream>
#include <iomanip>
#include "matrix.h"

bool DimensionCheckFailed(Tmat &mat1,Tmat &mat2) {
  if(mat1.n != mat2.m){
     std::cout << "Abnormal use of multiplication." << std::endl;
     std::cout << " mat1.m=" << mat1.m << " mat1.n=" << mat1.n << std::endl;
     std::cout << " mat2.m=" << mat2.m << " mat2.n=" << mat2.n << std::endl;
     std::cout << "Dimension mat1.n and mat2.m should mach." << std::endl;
     return true;
  }
  return false;
}

void PrintMatrix(Tmat &mat){
  int m = mat.m;
  int n = mat.n;

  for (int i = 0; i < m; i++){
    for (int j = 0; j < n; j++){
      std::cout << std::setw(9) << mat(i,j) << " | ";
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}

Tmat Transpose(Tmat &mat){
    int a = mat.m;
    int b = mat.n;

    Tmat mat3(b,a);
    for (int i = 0; i<a; i+=1){
        for (int j = 0; j<b; j+=1){
            mat3(j,i) = mat(i,j);
        }   
    }
    return mat3;
}

void MultiplicationClassicPart(Tmat &mat1, Tmat &mat2, Tmat &mat3,
                               int a1, int a2,
                               int b1, int b2,
                               int c1, int c2){

    for (int i = a1; i<a2; i+=1){
        for (int j = c1; j<c2; j+=1){
            double s = 0;
            for (int k = b1; k<b2; k+=1){
                    s+=mat1(i,k)*mat2(k,j);
            }
            mat3(i,j) += s;
        }
    }
}


void MultiplicationClassicTransposedPart(Tmat &mat1, Tmat &mat2, Tmat &mat3,
                                         int a1, int a2,
                                         int b1, int b2,
                                         int c1, int c2){

    //mat2 is transposed
    for (int i = a1; i<a2; i+=1){
        for (int j = c1; j<c2; j+=1){
            double s = 0;
            for (int k = b1; k<b2; k+=1){
                    s+=mat1(i,k)*mat2(j,k);
            }
            mat3(i,j) += s;
        }
    }
}