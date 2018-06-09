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

void print_ans(vector<vector<int>> ans)
{
    for (int i = 0; i < n1; i++) {
        for (int j = 0; j < n4; ++j) {
            printf("%s%d", (j == 0)? "": " ", ans[i][j]);
        }
        printf("\n");
    }
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
    f_origin_t1();
    f_origin_t2();
    f_origin_t4();
    myfile1.close();
    myfile2.close();
    myfile3.close();
}
