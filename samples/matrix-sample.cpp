//
// Created by root on 18-3-29.
//
#include <linear-algebra/matrixbase.h>
#include <linear-algebra/matrix.h>
#include <cstdio>
#include <cstdlib>

typedef float dataType;
#define rows 5
#define column 5
#define random(x) (rand()%x)
void displayM(sgbot::la::MatrixBase& matrix){
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < column; ++j) {
            printf("%f ,",matrix(i,j));
        }
        printf("\n");
    }
}
void initialM(sgbot::la::MatrixBase& matrix){
//    matrix(0,0) = 1.f;
//    matrix(0,1) = 1.f;
//    matrix(0,2) = 3.f;
//    matrix(0,3) = 1.f;
//    matrix(0,4) = 1.f;
//
//
//    matrix(1,0) = 2.f;
//    matrix(1,1) = 3.f;
//    matrix(1,2) = 4.f;
//    matrix(1,3) = 2.f;
//
//    matrix(2,0) = 5.f;
//    matrix(2,1) = 2.f;
//    matrix(2,2) = 5.f;
//    matrix(2,3) = 1.f;
//
//    matrix(3,0) = 2.f;
//    matrix(3,1) = 3.f;
//    matrix(3,2) = 3.f;
//    matrix(3,3) = 5.f;
    srand((int)time(0));
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < column; ++j) {
            matrix(i,j) = random(10);
        }
    }
}
int main(int argc,char* argv[]){
/*
    sgbot::la::MatrixBase matrix(rows,column);
    printf("initial matrix\n");
    initialM(matrix);
    displayM(matrix);

    printf("matrix inverse\n");
    clock_t begin_time = clock();
    sgbot::la::MatrixBase matrix_return = matrix.inverse();
    clock_t end_time = clock();
    displayM(matrix_return);
    double duration = static_cast<double>(end_time - begin_time) ;
    std::cout <<"inverse time = " << duration << std::endl;

    begin_time = clock();
    printf("matrix determinant = ");
    double determinant = matrix.determinant();
    printf("%lf\n",determinant);
    end_time = clock();
    duration = static_cast<double>(end_time - begin_time) ;
    std::cout << "determinant time = "<< duration<<std::endl;
*/

    sgbot::la::Matrix<double, 3, 3> a;
    a(2, 2) = 1.3f;
    
    std::cout << a;

    std::cout << a(2, 2) << std::endl;

    sgbot::la::Matrix<double, 3, 3> b = a;

    std::cout << b;
//
//    matrix+=matrix;
//    displayM(matrix);
//    matrix-=matrix;
//    displayM(matrix);
}
