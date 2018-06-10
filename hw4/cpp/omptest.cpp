// Author: HUNG, JUI-LUNG <jjoe0303@gmail.com>
// Filename: omptest.cpp
// Last modified: 2018-06-10 22:02:17
// g++ -g -Wall -fopenmp -o omptest omptest.cpp

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <vector>
#include <omp.h>
#include <chrono>
#include <fstream>

using namespace std;

vector<vector<int> > matrix1;
vector<vector<int> > matrix2;

int n1, n2, n3, n4;
int thread_count;
int n;
ofstream myfile1;
ofstream myfile2;
ofstream myfile3;
ofstream myfile4;
ofstream myfile5;
ofstream myfile6;
ofstream myfile7;
ofstream myfile8;
ofstream myfile9;

void matrix_add(vector<vector<int> > &matrixa, vector<vector<int> > &matrixb,
                vector<vector<int> > &matrixc)
{
    for (int i = 0; i < n1 / 2; i++) {
        for (int j = 0; j < n4 / 2; j++) {
            matrixc[i][j] = matrixa[i][j] + matrixb[i][j];
        }
    }
}

void matrix_sub(vector<vector<int> > &matrixa, vector<vector<int> > &matrixb,
                vector<vector<int> > &matrixc)
{
    for (int i = 0; i < n1 / 2; i++) {
        for (int j = 0; j < n4 / 2; j++) {
            matrixc[i][j] = matrixa[i][j] - matrixb[i][j];
        }
    }
}

void matrix_mul(vector<vector<int> > &matrixa, vector<vector<int> > &matrixb,
                vector<vector<int> > &matrixc)
{
    int i, j, k;
    #pragma omp parallel for num_threads(thread_count)\
    default(none) private(i,j,k) shared(n1,n2,n4,matrixa,matrixb,matrixc)
    for (i = 0; i < n1 / 2; i++) {
        for (j = 0; j < n4 / 2; ++j) {
            matrixc[i][j] = 0;
            for (k = 0; k < n2 / 2; ++k) {
                matrixc[i][j] += matrixa[i][k] * matrixb[k][j];
            }
        }
    }
}

void print_ans(vector<vector<int>> ans)
{
    for (int i = 0; i < n1; i++) {
        for (int j = 0; j < n4; ++j) {
            printf("%s%d", (j == 0) ? "" : " ", ans[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void f_origin_t1()
{
    int tmp = n;
    thread_count = 1;
    while (tmp--) {
        int i, j, k;
        vector<vector<int> > ans(n1, vector<int>(n4, 0));
        chrono::steady_clock::time_point t1 = std::chrono::steady_clock::now();
        #pragma omp parallel for num_threads(thread_count)\
        default(none) private(i,j,k) shared(n1,n2,n4,matrix1,matrix2,ans)
        for (i = 0; i < n1; i++) {
            for (j = 0; j < n4; ++j) {
                for (k = 0; k < n2; ++k) {
                    ans[i][j] += matrix1[i][k] * matrix2[k][j];
                }
            }
        }
        chrono::steady_clock::time_point t2 = std::chrono::steady_clock::now();
        myfile1 << chrono::duration_cast<chrono::nanoseconds>(t2 - t1).count();
        if (tmp != 0) myfile1 << ", ";
        // print_ans(ans);
    }
    myfile1 << "\n";
}

void f_origin_t2()
{
    int tmp = n;
    thread_count = 2;
    while (tmp--) {
        int i, j, k;
        vector<vector<int> > ans(n1, vector<int>(n4, 0));
        chrono::steady_clock::time_point t1 = std::chrono::steady_clock::now();
        #pragma omp parallel for num_threads(thread_count)\
        default(none) private(i,j,k) shared(n1,n2,n4,matrix1,matrix2,ans)
        for (i = 0; i < n1; i++) {
            for (j = 0; j < n4; ++j) {
                for (k = 0; k < n2; ++k) {
                    ans[i][j] += matrix1[i][k] * matrix2[k][j];
                }
            }
        }
        chrono::steady_clock::time_point t2 = std::chrono::steady_clock::now();
        myfile2 << chrono::duration_cast<chrono::nanoseconds>(t2 - t1).count();
        if (tmp != 0) myfile2 << ", ";
        // print_ans(ans);
    }
    myfile2 << "\n";
}

void f_origin_t4()
{
    int tmp = n;
    thread_count = 4;
    while (tmp--) {
        int i, j, k;
        vector<vector<int> > ans(n1, vector<int>(n4, 0));
        chrono::steady_clock::time_point t1 = std::chrono::steady_clock::now();
        #pragma omp parallel for num_threads(thread_count)\
        default(none) private(i,j,k) shared(n1,n2,n4,matrix1,matrix2,ans)
        for (i = 0; i < n1; i++) {
            for (j = 0; j < n4; ++j) {
                for (k = 0; k < n2; ++k) {
                    ans[i][j] += matrix1[i][k] * matrix2[k][j];
                }
            }
        }
        chrono::steady_clock::time_point t2 = std::chrono::steady_clock::now();
        myfile3 << chrono::duration_cast<chrono::nanoseconds>(t2 - t1).count();
        if (tmp != 0) myfile3 << ", ";
        // print_ans(ans);
    }
    myfile3 << "\n";
}

void f_strassen_t1()
{
    int tmp = n;
    thread_count = 1;
    while (tmp--) {
        int i, j;
        vector<vector<int> > ans(n1, vector<int>(n4, 0));
        vector<vector<int> > a11(n1 / 2, vector<int>(n4 / 2, 0));
        vector<vector<int> > a12(n1 / 2, vector<int>(n4 / 2, 0));
        vector<vector<int> > a21(n1 / 2, vector<int>(n4 / 2, 0));
        vector<vector<int> > a22(n1 / 2, vector<int>(n4 / 2, 0));
        vector<vector<int> > b11(n1 / 2, vector<int>(n4 / 2, 0));
        vector<vector<int> > b12(n1 / 2, vector<int>(n4 / 2, 0));
        vector<vector<int> > b21(n1 / 2, vector<int>(n4 / 2, 0));
        vector<vector<int> > b22(n1 / 2, vector<int>(n4 / 2, 0));
        vector<vector<int> > p1(n1 / 2, vector<int>(n4 / 2, 0));
        vector<vector<int> > p2(n1 / 2, vector<int>(n4 / 2, 0));
        vector<vector<int> > p3(n1 / 2, vector<int>(n4 / 2, 0));
        vector<vector<int> > p4(n1 / 2, vector<int>(n4 / 2, 0));
        vector<vector<int> > p5(n1 / 2, vector<int>(n4 / 2, 0));
        vector<vector<int> > p6(n1 / 2, vector<int>(n4 / 2, 0));
        vector<vector<int> > p7(n1 / 2, vector<int>(n4 / 2, 0));
        vector<vector<int> > c1(n1 / 2, vector<int>(n4 / 2, 0));
        vector<vector<int> > c2(n1 / 2, vector<int>(n4 / 2, 0));
        vector<vector<int> > c3(n1 / 2, vector<int>(n4 / 2, 0));
        vector<vector<int> > c4(n1 / 2, vector<int>(n4 / 2, 0));
        vector<vector<int> > aa(n1 / 2, vector<int>(n4 / 2, 0));
        vector<vector<int> > bb(n1 / 2, vector<int>(n4 / 2, 0));
        chrono::steady_clock::time_point t1 = std::chrono::steady_clock::now();
        #pragma omp parallel for num_threads(thread_count)\
        default(none) private(i,j) shared(n1,n4,a11,a12,a21,a22,b11,b12,b21,b22,matrix1,matrix2)
        for (i = 0; i < n1 / 2; i++) {
            for (j = 0; j < n4 / 2; j++) {
                a11[i][j] = matrix1[i][j];
                a12[i][j] = matrix1[i][j + n4 / 2];
                a21[i][j] = matrix1[i + n1 / 2][j];
                a22[i][j] = matrix1[i + n1 / 2][j + n4 / 2];
                b11[i][j] = matrix2[i][j];
                b12[i][j] = matrix2[i][j + n4 / 2];
                b21[i][j] = matrix2[i + n1 / 2][j];
                b22[i][j] = matrix2[i + n1 / 2][j + n4 / 2];
            }
        }
        //p1
        matrix_add(a11, a22, aa);
        matrix_add(b11, b22, bb);
        matrix_mul(aa, bb, p1);
        //p2
        matrix_add(a21, a22, aa);
        matrix_mul(aa, b11, p2);
        //p3
        matrix_sub(b12, b22, bb);
        matrix_mul(a11, bb, p3);
        //p4
        matrix_sub(b21, b11, bb);
        matrix_mul(a22, bb, p4);
        //p5
        matrix_add(a11, a12, aa);
        matrix_mul(aa, b22, p5);
        //p6
        matrix_sub(a21, a11, aa);
        matrix_add(b11, b12, bb);
        matrix_mul(aa, bb, p6);
        //p7
        matrix_sub(a12, a22, aa);
        matrix_add(b21, b22, bb);
        matrix_mul(aa, bb, p7);
        //c1
        matrix_add(p1, p4, aa);
        matrix_sub(p7, p5, bb);
        matrix_add(aa, bb, c1);
        //c2
        matrix_add(p3, p5, c2);
        //c3
        matrix_add(p2, p4, c3);
        //c4
        matrix_sub(p1, p2, aa);
        matrix_add(p3, p6, bb);
        matrix_add(aa, bb, c4);
        #pragma omp parallel for num_threads(thread_count)\
        default(none) private(i,j) shared(n1,n4,c1,c2,c3,c4,ans)
        for (i = 0; i < n1 / 2; i++) {
            for (j = 0; j < n4 / 2; j++) {
                ans[i][j] = c1[i][j];
                ans[i][j + n4 / 2] = c2[i][j];
                ans[i + n1 / 2][j] = c3[i][j];
                ans[i + n1 / 2][j + n4 / 2] = c4[i][j];
            }
        }
        chrono::steady_clock::time_point t2 = std::chrono::steady_clock::now();
        myfile4 << chrono::duration_cast<chrono::nanoseconds>(t2 - t1).count();
        if (tmp != 0) myfile4 << ", ";
        // print_ans(ans);
    }
    myfile4 << "\n";
}



void f_strassen_t2()
{
    int tmp = n;
    thread_count = 2;
    while (tmp--) {
        int i, j;
        vector<vector<int> > ans(n1, vector<int>(n4, 0));
        vector<vector<int> > a11(n1 / 2, vector<int>(n4 / 2, 0));
        vector<vector<int> > a12(n1 / 2, vector<int>(n4 / 2, 0));
        vector<vector<int> > a21(n1 / 2, vector<int>(n4 / 2, 0));
        vector<vector<int> > a22(n1 / 2, vector<int>(n4 / 2, 0));
        vector<vector<int> > b11(n1 / 2, vector<int>(n4 / 2, 0));
        vector<vector<int> > b12(n1 / 2, vector<int>(n4 / 2, 0));
        vector<vector<int> > b21(n1 / 2, vector<int>(n4 / 2, 0));
        vector<vector<int> > b22(n1 / 2, vector<int>(n4 / 2, 0));
        vector<vector<int> > p1(n1 / 2, vector<int>(n4 / 2, 0));
        vector<vector<int> > p2(n1 / 2, vector<int>(n4 / 2, 0));
        vector<vector<int> > p3(n1 / 2, vector<int>(n4 / 2, 0));
        vector<vector<int> > p4(n1 / 2, vector<int>(n4 / 2, 0));
        vector<vector<int> > p5(n1 / 2, vector<int>(n4 / 2, 0));
        vector<vector<int> > p6(n1 / 2, vector<int>(n4 / 2, 0));
        vector<vector<int> > p7(n1 / 2, vector<int>(n4 / 2, 0));
        vector<vector<int> > c1(n1 / 2, vector<int>(n4 / 2, 0));
        vector<vector<int> > c2(n1 / 2, vector<int>(n4 / 2, 0));
        vector<vector<int> > c3(n1 / 2, vector<int>(n4 / 2, 0));
        vector<vector<int> > c4(n1 / 2, vector<int>(n4 / 2, 0));
        vector<vector<int> > aa(n1 / 2, vector<int>(n4 / 2, 0));
        vector<vector<int> > bb(n1 / 2, vector<int>(n4 / 2, 0));
        chrono::steady_clock::time_point t1 = std::chrono::steady_clock::now();
        #pragma omp parallel for num_threads(thread_count)\
        default(none) private(i,j) shared(n1,n4,a11,a12,a21,a22,b11,b12,b21,b22,matrix1,matrix2)
        for (i = 0; i < n1 / 2; i++) {
            for (j = 0; j < n4 / 2; j++) {
                a11[i][j] = matrix1[i][j];
                a12[i][j] = matrix1[i][j + n4 / 2];
                a21[i][j] = matrix1[i + n1 / 2][j];
                a22[i][j] = matrix1[i + n1 / 2][j + n4 / 2];
                b11[i][j] = matrix2[i][j];
                b12[i][j] = matrix2[i][j + n4 / 2];
                b21[i][j] = matrix2[i + n1 / 2][j];
                b22[i][j] = matrix2[i + n1 / 2][j + n4 / 2];
            }
        }
        //p1
        matrix_add(a11, a22, aa);
        matrix_add(b11, b22, bb);
        matrix_mul(aa, bb, p1);
        //p2
        matrix_add(a21, a22, aa);
        matrix_mul(aa, b11, p2);
        //p3
        matrix_sub(b12, b22, bb);
        matrix_mul(a11, bb, p3);
        //p4
        matrix_sub(b21, b11, bb);
        matrix_mul(a22, bb, p4);
        //p5
        matrix_add(a11, a12, aa);
        matrix_mul(aa, b22, p5);
        //p6
        matrix_sub(a21, a11, aa);
        matrix_add(b11, b12, bb);
        matrix_mul(aa, bb, p6);
        //p7
        matrix_sub(a12, a22, aa);
        matrix_add(b21, b22, bb);
        matrix_mul(aa, bb, p7);
        //c1
        matrix_add(p1, p4, aa);
        matrix_sub(p7, p5, bb);
        matrix_add(aa, bb, c1);
        //c2
        matrix_add(p3, p5, c2);
        //c3
        matrix_add(p2, p4, c3);
        //c4
        matrix_sub(p1, p2, aa);
        matrix_add(p3, p6, bb);
        matrix_add(aa, bb, c4);
        #pragma omp parallel for num_threads(thread_count)\
        default(none) private(i,j) shared(n1,n4,c1,c2,c3,c4,ans)
        for (i = 0; i < n1 / 2; i++) {
            for (j = 0; j < n4 / 2; j++) {
                ans[i][j] = c1[i][j];
                ans[i][j + n4 / 2] = c2[i][j];
                ans[i + n1 / 2][j] = c3[i][j];
                ans[i + n1 / 2][j + n4 / 2] = c4[i][j];
            }
        }
        chrono::steady_clock::time_point t2 = std::chrono::steady_clock::now();
        myfile5 << chrono::duration_cast<chrono::nanoseconds>(t2 - t1).count();
        if (tmp != 0) myfile5 << ", ";
        // print_ans(ans);
    }
    myfile5 << "\n";
}

void f_strassen_t4()
{
    int tmp = n;
    thread_count = 4;
    while (tmp--) {
        int i, j;
        vector<vector<int> > ans(n1, vector<int>(n4, 0));
        vector<vector<int> > a11(n1 / 2, vector<int>(n4 / 2, 0));
        vector<vector<int> > a12(n1 / 2, vector<int>(n4 / 2, 0));
        vector<vector<int> > a21(n1 / 2, vector<int>(n4 / 2, 0));
        vector<vector<int> > a22(n1 / 2, vector<int>(n4 / 2, 0));
        vector<vector<int> > b11(n1 / 2, vector<int>(n4 / 2, 0));
        vector<vector<int> > b12(n1 / 2, vector<int>(n4 / 2, 0));
        vector<vector<int> > b21(n1 / 2, vector<int>(n4 / 2, 0));
        vector<vector<int> > b22(n1 / 2, vector<int>(n4 / 2, 0));
        vector<vector<int> > p1(n1 / 2, vector<int>(n4 / 2, 0));
        vector<vector<int> > p2(n1 / 2, vector<int>(n4 / 2, 0));
        vector<vector<int> > p3(n1 / 2, vector<int>(n4 / 2, 0));
        vector<vector<int> > p4(n1 / 2, vector<int>(n4 / 2, 0));
        vector<vector<int> > p5(n1 / 2, vector<int>(n4 / 2, 0));
        vector<vector<int> > p6(n1 / 2, vector<int>(n4 / 2, 0));
        vector<vector<int> > p7(n1 / 2, vector<int>(n4 / 2, 0));
        vector<vector<int> > c1(n1 / 2, vector<int>(n4 / 2, 0));
        vector<vector<int> > c2(n1 / 2, vector<int>(n4 / 2, 0));
        vector<vector<int> > c3(n1 / 2, vector<int>(n4 / 2, 0));
        vector<vector<int> > c4(n1 / 2, vector<int>(n4 / 2, 0));
        vector<vector<int> > aa(n1 / 2, vector<int>(n4 / 2, 0));
        vector<vector<int> > bb(n1 / 2, vector<int>(n4 / 2, 0));
        chrono::steady_clock::time_point t1 = std::chrono::steady_clock::now();
        #pragma omp parallel for num_threads(thread_count)\
        default(none) private(i,j) shared(n1,n4,a11,a12,a21,a22,b11,b12,b21,b22,matrix1,matrix2)
        for (i = 0; i < n1 / 2; i++) {
            for (j = 0; j < n4 / 2; j++) {
                a11[i][j] = matrix1[i][j];
                a12[i][j] = matrix1[i][j + n4 / 2];
                a21[i][j] = matrix1[i + n1 / 2][j];
                a22[i][j] = matrix1[i + n1 / 2][j + n4 / 2];
                b11[i][j] = matrix2[i][j];
                b12[i][j] = matrix2[i][j + n4 / 2];
                b21[i][j] = matrix2[i + n1 / 2][j];
                b22[i][j] = matrix2[i + n1 / 2][j + n4 / 2];
            }
        }
        //p1
        matrix_add(a11, a22, aa);
        matrix_add(b11, b22, bb);
        matrix_mul(aa, bb, p1);
        //p2
        matrix_add(a21, a22, aa);
        matrix_mul(aa, b11, p2);
        //p3
        matrix_sub(b12, b22, bb);
        matrix_mul(a11, bb, p3);
        //p4
        matrix_sub(b21, b11, bb);
        matrix_mul(a22, bb, p4);
        //p5
        matrix_add(a11, a12, aa);
        matrix_mul(aa, b22, p5);
        //p6
        matrix_sub(a21, a11, aa);
        matrix_add(b11, b12, bb);
        matrix_mul(aa, bb, p6);
        //p7
        matrix_sub(a12, a22, aa);
        matrix_add(b21, b22, bb);
        matrix_mul(aa, bb, p7);
        //c1
        matrix_add(p1, p4, aa);
        matrix_sub(p7, p5, bb);
        matrix_add(aa, bb, c1);
        //c2
        matrix_add(p3, p5, c2);
        //c3
        matrix_add(p2, p4, c3);
        //c4
        matrix_sub(p1, p2, aa);
        matrix_add(p3, p6, bb);
        matrix_add(aa, bb, c4);
        #pragma omp parallel for num_threads(thread_count)\
        default(none) private(i,j) shared(n1,n4,c1,c2,c3,c4,ans)
        for (i = 0; i < n1 / 2; i++) {
            for (j = 0; j < n4 / 2; j++) {
                ans[i][j] = c1[i][j];
                ans[i][j + n4 / 2] = c2[i][j];
                ans[i + n1 / 2][j] = c3[i][j];
                ans[i + n1 / 2][j + n4 / 2] = c4[i][j];
            }
        }
        chrono::steady_clock::time_point t2 = std::chrono::steady_clock::now();
        myfile6 << chrono::duration_cast<chrono::nanoseconds>(t2 - t1).count();
        if (tmp != 0) myfile6 << ", ";
        // print_ans(ans);
    }
    myfile6 << "\n";
}

void f_cache_t1()
{
    int tmp = n;
    thread_count = 1;
    while (tmp--) {
        int i, j, k;
        vector<vector<int> > ans(n1, vector<int>(n4, 0));
        vector<vector<int> > matrix2_tr(n1, vector<int>(n4, 0));
        for (i = 0; i < n3; ++i) {
            for (j = 0; j < n4; ++j) {
                matrix2_tr[i][j] = matrix2[j][i];
            }
        }
        chrono::steady_clock::time_point t1 = std::chrono::steady_clock::now();
        #pragma omp parallel for num_threads(thread_count)\
        default(none) private(i,j,k) shared(n1,n2,n4,matrix1,matrix2_tr,ans)
        for (i = 0; i < n1; i++) {
            for (j = 0; j < n2; ++j) {
                for (k = 0; k < n2; ++k) {
                    ans[i][j] += matrix1[i][k] * matrix2_tr[j][k];
                }
            }
        }
        chrono::steady_clock::time_point t2 = std::chrono::steady_clock::now();
        myfile7 << chrono::duration_cast<chrono::nanoseconds>(t2 - t1).count();
        if (tmp != 0) myfile7 << ", ";
        // print_ans(ans);
    }
    myfile7 << "\n";
}

void f_cache_t2()
{
    int tmp = n;
    thread_count = 2;
    while (tmp--) {
        int i, j, k;
        vector<vector<int> > ans(n1, vector<int>(n4, 0));
        vector<vector<int> > matrix2_tr(n1, vector<int>(n4, 0));
        for (i = 0; i < n3; ++i) {
            for (j = 0; j < n4; ++j) {
                matrix2_tr[i][j] = matrix2[j][i];
            }
        }
        chrono::steady_clock::time_point t1 = std::chrono::steady_clock::now();
        #pragma omp parallel for num_threads(thread_count)\
        default(none) private(i,j,k) shared(n1,n2,n4,matrix1,matrix2_tr,ans)
        for (i = 0; i < n1; i++) {
            for (j = 0; j < n2; ++j) {
                for (k = 0; k < n2; ++k) {
                    ans[i][j] += matrix1[i][k] * matrix2_tr[j][k];
                }
            }
        }
        chrono::steady_clock::time_point t2 = std::chrono::steady_clock::now();
        myfile8 << chrono::duration_cast<chrono::nanoseconds>(t2 - t1).count();
        if (tmp != 0) myfile8 << ", ";
        // print_ans(ans);
    }
    myfile8 << "\n";
}

void f_cache_t4()
{
    int tmp = n;
    thread_count = 4;
    while (tmp--) {
        int i, j, k;
        vector<vector<int> > ans(n1, vector<int>(n4, 0));
        vector<vector<int> > matrix2_tr(n1, vector<int>(n4, 0));
        for (i = 0; i < n3; ++i) {
            for (j = 0; j < n4; ++j) {
                matrix2_tr[i][j] = matrix2[j][i];
            }
        }
        chrono::steady_clock::time_point t1 = std::chrono::steady_clock::now();
        #pragma omp parallel for num_threads(thread_count)\
        default(none) private(i,j,k) shared(n1,n2,n4,matrix1,matrix2_tr,ans)
        for (i = 0; i < n1; i++) {
            for (j = 0; j < n2; ++j) {
                for (k = 0; k < n2; ++k) {
                    ans[i][j] += matrix1[i][k] * matrix2_tr[j][k];
                }
            }
        }
        chrono::steady_clock::time_point t2 = std::chrono::steady_clock::now();
        myfile9 << chrono::duration_cast<chrono::nanoseconds>(t2 - t1).count();
        if (tmp != 0) myfile9 << ", ";
        // print_ans(ans);
    }
    myfile9 << "\n";
}

int main(int argc, char* argv[])
{
    n = 100;
    int mat;
    matrix1.clear();
    matrix2.clear();
    scanf("%d %d", &n1, &n2);
    for (int i = 0; i < n1; ++i) {
        vector<int> row1;
        for (int j = 0; j < n2; ++j) {
            scanf("%d", &mat);
            row1.push_back(mat);
        }
        matrix1.push_back(row1);
    }
    scanf("%d %d", &n3, &n4);
    for (int i = 0; i < n3; ++i) {
        vector<int> row2;
        for (int j = 0; j < n4; ++j) {
            scanf("%d", &mat);
            row2.push_back(mat);
        }
        matrix2.push_back(row2);
    }
    myfile1.open("o1.csv", ios::app);
    myfile2.open("o2.csv", ios::app);
    myfile3.open("o3.csv", ios::app);
    myfile4.open("o4.csv", ios::app);
    myfile5.open("o5.csv", ios::app);
    myfile6.open("o6.csv", ios::app);
    myfile7.open("o7.csv", ios::app);
    myfile8.open("o8.csv", ios::app);
    myfile9.open("o9.csv", ios::app);
    f_origin_t1(); // o1
    f_origin_t2(); // o2
    f_origin_t4(); // o3
    f_strassen_t1(); // o4
    f_strassen_t2(); // o5
    f_strassen_t4(); // o6
    f_cache_t1(); // o7
    f_cache_t2(); // o8
    f_cache_t4(); // o9
    myfile1.close();
    myfile2.close();
    myfile3.close();
    myfile4.close();
    myfile5.close();
    myfile6.close();
    myfile7.close();
    myfile8.close();
    myfile9.close();
}
