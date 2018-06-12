// Author: HUNG, JUI-LUNG <jjoe0303@gmail.com>
// Filename: omptest.cpp
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
ofstream fout1;
ofstream fout2;
ofstream fout3;
ofstream fout4;
ofstream fout5;
ofstream fout6;
ofstream fout7;
ofstream fout8;
ofstream fout9;

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
        fout1 << chrono::duration_cast<chrono::nanoseconds>(t2 - t1).count();
        if (tmp != 0) fout1 << ", ";
        // print_ans(ans);
    }
    fout1 << "\n";
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
        fout2 << chrono::duration_cast<chrono::nanoseconds>(t2 - t1).count();
        if (tmp != 0) fout2 << ", ";
        // print_ans(ans);
    }
    fout2 << "\n";
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
        fout3 << chrono::duration_cast<chrono::nanoseconds>(t2 - t1).count();
        if (tmp != 0) fout3 << ", ";
        // print_ans(ans);
    }
    fout3 << "\n";
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
        fout4 << chrono::duration_cast<chrono::nanoseconds>(t2 - t1).count();
        if (tmp != 0) fout4 << ", ";
        // print_ans(ans);
    }
    fout4 << "\n";
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
        fout5 << chrono::duration_cast<chrono::nanoseconds>(t2 - t1).count();
        if (tmp != 0) fout5 << ", ";
        // print_ans(ans);
    }
    fout5 << "\n";
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
        fout6 << chrono::duration_cast<chrono::nanoseconds>(t2 - t1).count();
        if (tmp != 0) fout6 << ", ";
        // print_ans(ans);
    }
    fout6 << "\n";
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
        fout7 << chrono::duration_cast<chrono::nanoseconds>(t2 - t1).count();
        if (tmp != 0) fout7 << ", ";
        // print_ans(ans);
    }
    fout7 << "\n";
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
        fout8 << chrono::duration_cast<chrono::nanoseconds>(t2 - t1).count();
        if (tmp != 0) fout8 << ", ";
        // print_ans(ans);
    }
    fout8 << "\n";
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
        fout9 << chrono::duration_cast<chrono::nanoseconds>(t2 - t1).count();
        if (tmp != 0) fout9 << ", ";
        // print_ans(ans);
    }
    fout9 << "\n";
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
    /* A */
    fout1.open("o1.csv", ios::app);
    f_origin_t1();
    fout1.close();

    /* E */
    fout2.open("o2.csv", ios::app);
    f_origin_t2();
    fout2.close();

    /* L */
    fout3.open("o3.csv", ios::app);
    f_origin_t4();
    fout3.close();

    /* G */
    fout4.open("o4.csv", ios::app);
    f_strassen_t1();
    fout4.close();

    /* H */
    fout5.open("o5.csv", ios::app);
    f_strassen_t2();
    fout5.close();

    /* K */
    fout6.open("o6.csv", ios::app);
    f_strassen_t4();
    fout6.close();

    /* B */
    fout7.open("o7.csv", ios::app);
    f_cache_t1();
    fout7.close();

    /* F */
    fout8.open("o8.csv", ios::app);
    f_cache_t2();
    fout8.close();

    /* J */
    fout9.open("o9.csv", ios::app);
    f_cache_t4();
    fout9.close();
}
