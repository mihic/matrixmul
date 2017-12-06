#include <vector>
#include <algorithm>
#include <iostream>
#include "matrix.h"


Tmat Slice(Tmat &mat1,
           int x1, int x1max,
           int x2, int x2max){

    int x1D = x1max - x1;
    int x2D = x2max - x2;

    Tmat mat3(x1D,x2D);
    for (int i = 0; i<x1D; i+=1){
        for (int j = 0; j<x2D; j+=1){
            mat3(i,j) = mat1(x1+i,x2+j);
        }
    }

    return mat3;
}

void AddToResult(Tmat &mat1, Tmat &mat3,
                 int x1,
                 int x2){

    int x1D = mat1.m;
    int x2D = mat1.n;

    for (int i = 0; i<x1D; i+=1){
        for (int j = 0; j<x2D; j+=1){
            mat3(x1+i,x2+j) += mat1(i,j);
        }
    }
}

void SubFromResult(Tmat &mat1, Tmat &mat3,
                   int x1,
                   int x2){

    int x1D = mat1.m;
    int x2D = mat1.n;

    for (int i = 0; i<x1D; i+=1){
        for (int j = 0; j<x2D; j+=1){
            mat3(x1+i,x2+j) -= mat1(i,j);
        }
    }
}

Tmat Add(Tmat &mat1, Tmat &mat2,
         int x1, int x1max,
         int x2, int x2max,
         int y1, int y1max,
         int y2, int y2max){

    int x1D = x1max - x1;
    int x2D = x2max - x2;
    int y1D = y1max - y1;
    int y2D = y2max - y2;

    int iMax = std::max({x1D, y1D});
    int jMax = std::max({x2D, y2D});

    Tmat mat3(iMax,jMax);
    for (int i = 0; i<x1D; i+=1){
        for (int j = 0; j<x2D; j+=1){
            mat3(i,j) += mat1(x1+i,x2+j);
        }
    }
    for (int i = 0; i<y1D; i+=1){
        for (int j = 0; j<y2D; j+=1){
            mat3(i,j) += mat2(y1+i,y2+j);
        }
    }

    return mat3;
}

Tmat Sub(Tmat &mat1, Tmat &mat2,
         int x1, int x1max,
         int x2, int x2max,
         int y1, int y1max,
         int y2, int y2max){

    int x1D = x1max - x1;
    int x2D = x2max - x2;
    int y1D = y1max - y1;
    int y2D = y2max - y2;

    int iMax = std::max({x1D, y1D});
    int jMax = std::max({x2D, y2D});

    Tmat mat3(iMax,jMax);
    for (int i = 0; i<x1D; i+=1){
        for (int j = 0; j<x2D; j+=1){
            mat3(i,j) += mat1(x1+i,x2+j);
        }
    }
    for (int i = 0; i<y1D; i+=1){
        for (int j = 0; j<y2D; j+=1){
            mat3(i,j) -= mat2(y1+i,y2+j);
        }
    }

    return mat3;
}

Tmat MultiplicationStrassenTransposedPart2(Tmat &, Tmat &);

void MultiplicationStrassenTransposedPart1(Tmat &mat1, Tmat &mat4, Tmat &mat3,
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
        MultiplicationRecursiveTransposedPart(mat1, mat4, mat3, a1, a2, b1, b2, c1, c2);
    }
    else{
        Tmat matA1B1 = Add(mat1, mat1,
            //A1
                           a1, aP,
                           b1, bP,
            //B1
                           aP, a2,
                           b1, bP);

        Tmat matX1Y1 = Add(mat4, mat4,
            //X1
                           c1, cP,
                           b1, bP,
            //Y1
                           cP, c2,
                           b1, bP);

        Tmat matA2B2 = Add(mat1, mat1,
            //A2
                           a1, aP,
                           bP, b2,
            //B2
                           aP, a2,
                           bP, b2);

        Tmat matX2Y2 = Add(mat4, mat4,
            //X2
                           c1, cP,
                           bP, b2,
            //Y2
                           cP, c2,
                           bP, b2);


        Tmat matA1mB2 = Sub(mat1, mat1,
            //A1
                            a1, aP,
                            b1, bP,
            //B2
                            aP, a2,
                            bP, b2);

        Tmat matX2Y1 = Add(mat4, mat4,
            //X2
                           c1, cP,
                           bP, b2,
            //Y1
                           cP, c2,
                           b1, bP);


        Tmat matA1 = Slice(mat1,
            //A1
                           a1, aP,
                           b1, bP);

        Tmat matX1mX2 = Sub(mat4, mat4,
            //X1
                            c1, cP,
                            b1, bP,
            //X2
                            c1, cP,
                            bP, b2);

        Tmat matA2A1 = Add(mat1, mat1,
            //A2
                           a1, aP,
                           bP, b2,
            //A1
                           a1, aP,
                           b1, bP);

        Tmat matX2 = Slice(mat4,
            //X2
                           c1, cP,
                           bP, b2);

        Tmat matB2 = Slice(mat1,
            //B2
                           aP, a2,
                           bP, b2);

        Tmat matY2mY1 = Sub(mat4, mat4,
            //Y2
                            cP, c2,
                            bP, b2,
            //Y1
                            cP, c2,
                            b1, bP);

        Tmat matB1b2 = Add(mat1, mat1,
            //B1
                           aP, a2,
                           b1, bP,
            //B2
                           aP, a2,
                           bP, b2);

        Tmat matY1 = Slice(mat4,
            //Y1
                           cP, c2,
                           b1, bP);

        Tmat matM1 = MultiplicationStrassenTransposedPart2(matA1B1, matX1Y1);
        Tmat matM2 = MultiplicationStrassenTransposedPart2(matA2B2, matX2Y2);
        Tmat matM3 = MultiplicationStrassenTransposedPart2(matA1mB2, matX2Y1);
        Tmat matM4 = MultiplicationStrassenTransposedPart2(matA1, matX1mX2);
        Tmat matM5 = MultiplicationStrassenTransposedPart2(matA2A1, matX2);
        Tmat matM6 = MultiplicationStrassenTransposedPart2(matB2, matY2mY1);
        Tmat matM7 = MultiplicationStrassenTransposedPart2(matB1b2, matY1);

        //A1*
        AddToResult(matM4, mat3, a1, c1);
        AddToResult(matM5, mat3, a1, c1);

        //A2*
        AddToResult(matM2, mat3, a1, cP);
        SubFromResult(matM6, mat3, a1, cP);
        AddToResult(matM3, mat3, a1, cP);
        SubFromResult(matM5, mat3, a1, cP);

        //B1*
        AddToResult(matM1, mat3, aP, c1);
        SubFromResult(matM4, mat3, aP, c1);
        SubFromResult(matM3, mat3, aP, c1);
        SubFromResult(matM7, mat3, aP, c1);

        //B2*
        AddToResult(matM6, mat3, aP, cP);
        AddToResult(matM7, mat3, aP, cP);
    }
}

Tmat MultiplicationStrassenTransposedPart2(Tmat &mat1, Tmat &mat4){
    int a = mat1.m;
    int b = std::min({mat1.n,mat4.n});
    int c = mat4.m;

    Tmat mat3(a,c);
    MultiplicationStrassenTransposedPart1(mat1, mat4, mat3, 0, a, 0, b, 0, c);

    return mat3;
}

Tmat MultiplicationStrassenTransposed(Tmat &mat1, Tmat &mat2){
    if (DimensionCheckFailed(mat1,mat2)){
        std::exit(-1);
    }
    Tmat mat4 = Transpose(mat2);
    return MultiplicationStrassenTransposedPart2(mat1, mat4);
}
