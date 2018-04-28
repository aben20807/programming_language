#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
using namespace std;

bool is_prime(int n, int f)
{
    if (n == 2 || n == 3)
        return true;
    if (n % 2 == 0 || n % f == 0 || n == 1)
        return false;
    if (n < f * f)
        return true;
    else
        return is_prime(n, f+2);
}

int main()
{
    int n;
    while (scanf("%d", &n)) {
        const clock_t t1 = clock();
        for (int i = 1; i < n; i+=2){
            for (int j = 1; j <= i; j+=2){
                if (n == i+j && is_prime(i, 3) && is_prime(j, 3)){
                    printf("%d %d\n", i, j);
                    goto out1;
                }
            }
        }
    out1:
        printf("%.2lf (s)\n\n", float(clock() - t1) / CLOCKS_PER_SEC);
        const clock_t t2 = clock();
        for (int i = 1; i < n; i+=2){
            int j = n - i;
            if (is_prime(i, 3) && is_prime(j, 3)){
                printf("%d %d\n", i, j);
                goto out2;
            }
        }
    out2:
        printf("%.2lf (s)\n\n", float(clock() - t2) / CLOCKS_PER_SEC);
    }
    return 0;
}
