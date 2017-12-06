#include <vector>
#include <algorithm>
#include <iomanip>
#include <iostream>
#include "matrix.h"

Tmat MultiplicationStrassenPart1(Tmat &, Tmat &);

void MultiplicationStrassenPart2(Tmat &mat1, Tmat &mat2, Tmat &mat3,
                        int a1, int a2,
                        int b1, int b2,
                        int c1, int c2){

    int aD = a2-a1;
    int bD = b2-b1;
    int cD = c2-c1;
    int aP = a1+aD/2;
    int bP = b1+bD/2;
    int cP = c1+cD/2;

    if(std::min({aD, bD, cD})<96){
      MultiplicationRecursivePart(mat1, mat2, mat3, a1, a2, b1, b2, c1, c2);
    }
    else{
        //M1
        Tmat mA11A22 = Add(mat1, mat1,
            //A11
                           a1, aP,
                           b1, bP,
            //A22
                           aP, a2,
                           bP, b2);

        Tmat mB11B22 = Add(mat2, mat2,
            //B11
                           b1, bP,
                           c1, cP,
            //B22
                           bP, b2,
                           cP, c2);
        //M2
        Tmat mA21A22 = Add(mat1, mat1,
            //A21
                           aP, a2,
                           b1, bP,
            //A22
                           aP, a2,
                           bP, b2);

        Tmat maB11 = Slice(mat2,
            //B11
                           b1, bP,
                           c1, cP);

        //M3
        Tmat maA11 = Slice(mat1,
            //A11
                           a1, aP,
                           b1, bP);
                                          
        Tmat mB12B22 = Sub(mat2, mat2,
            //B12
                           b1, bP,
                           cP, c2,
            //B22
                           bP, b2,
                           cP, c2);

        //M4
        Tmat maA22 = Slice(mat1,
            //A22
                           aP, a2,
                           bP, b2);
                                          
        Tmat mB21B11 = Sub(mat2, mat2,
            //B21
                           bP, b2,
                           c1, cP,
            //B11
                           b1, bP,
                           c1, cP);

        //M5
        Tmat mA11A12 = Add(mat1, mat1,
            //A11
                           a1, aP,
                           b1, bP,
            //A12
                           a1, aP,
                           bP, b2);

        Tmat maB22 = Slice(mat2,
            //B22
                           bP, b2,
                           cP, c2);


        //M6
        Tmat mA21A11 = Sub(mat1, mat1,
            //A21
                           aP, a2,
                           b1, bP,
            //A11
                           a1, aP,
                           b1, bP);


        Tmat mB11B12 = Add(mat2, mat2,
            //B11
                           b1, bP,
                           c1, cP,
            //B12
                           b1, bP,
                           cP, c2);


        //M7
        Tmat mA12A22 = Sub(mat1, mat1,
            //A12
                           a1, aP,
                           bP, b2,
            //A22
                           aP, a2,
                           bP, b2);

        Tmat mB21B22 = Add(mat2, mat2,
            //B21
                           bP, b2,
                           c1, cP,
            //B22
                           bP, b2,
                           cP, c2);


        Tmat matM1 = MultiplicationStrassenPart1(mA11A22, mB11B22);
        Tmat matM2 = MultiplicationStrassenPart1(mA21A22, maB11);
        Tmat matM3 = MultiplicationStrassenPart1(maA11, mB12B22);
        Tmat matM4 = MultiplicationStrassenPart1(maA22, mB21B11);
        Tmat matM5 = MultiplicationStrassenPart1(mA11A12, maB22);
        Tmat matM6 = MultiplicationStrassenPart1(mA21A11, mB11B12);
        Tmat matM7 = MultiplicationStrassenPart1(mA12A22, mB21B22);
        //C11
        AddToResult(matM1, mat3, a1, c1);
        AddToResult(matM4, mat3, a1, c1);
        SubFromResult(matM5, mat3, a1, c1);
        AddToResult(matM7, mat3, a1, c1);
        //C12
        AddToResult(matM3, mat3, a1, cP);
        AddToResult(matM5, mat3, a1, cP);
        //C21
        AddToResult(matM2, mat3, aP, c1);
        AddToResult(matM4, mat3, aP, c1);
        //C22
        AddToResult(matM1, mat3, aP, cP);
        SubFromResult(matM2, mat3, aP, cP);
        AddToResult(matM3, mat3, aP, cP);
        AddToResult(matM6, mat3, aP, cP);
    }
}

Tmat MultiplicationStrassenPart1(Tmat &mat1, Tmat &mat2){
    int a = mat1.m;
    int b = std::min({mat2.m,mat1.n});
    int c = mat2.n;

    Tmat mat3(a,c);
    MultiplicationStrassenPart2(mat1, mat2, mat3, 0, a, 0, b, 0, c);

    return mat3;
}

Tmat MultiplicationStrassen(Tmat &mat1, Tmat &mat2){
    if (DimensionCheckFailed(mat1,mat2)){std::exit(-1);}

    return MultiplicationStrassenPart1(mat1, mat2);
}
