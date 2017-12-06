#include <vector>
#include <iostream>
#include "matrix.h"

Tmat MultiplicationClassic(Tmat &mat1, Tmat &mat2){
    if (DimensionCheckFailed(mat1,mat2)){std::exit(-1);}
    
    int a = mat1.m;
    int b = mat1.n;
    int c = mat2.n;

    Tmat mat3(a,c);
    MultiplicationClassicPart(mat1, mat2, mat3, 0, a, 0, b, 0, c);

    return mat3;
}

