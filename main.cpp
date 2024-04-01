//
// Created by 19003 on 2024/4/1.
//

#include <iostream>
#include <iomanip>
#include<cmath>
using namespace std;

int main() {
    int I, J, M, N, K, IT;
    float t[40][30], tt[40][30];
    float TTB, TLB, TRB, TBB, T0;
    float EPS;

    M = 8;
    N = 6;
    K = 10000;
    EPS = 0.01;
    TTB = 50;
    TLB = 200;
    TRB = 50;
    TBB = 50;
    T0 = 20;

    for (I = 1; I <= M + 1; I++)
        t[I][1] = TBB, t[I][N + 1] = TTB;

    for (J = 1; J <= N + 1; J++)
        t[1][J] = TLB, t[M + 1][J] = TRB;

    for (I = 2; I <= M; I++)
        for (J = 2; J <= N; J++)
            t[I][J] = T0;

    IT = 0;

    iter10:
        for (I = 2; I <= M; I++)
            for (J = 2; J <= N; J++)
                tt[I][J] = t[I][J], t[I][J] = 0.25 * (t[I - 1][J] + t[I + 1][J] + t[I][J - 1] + t[I][J + 1]);

    if (IT >= K) goto iter20;

    IT++;
    for (I = 2; I <= M; I++)
        for (J = 2; J <= N; J++)
            if (std::abs(tt[I][J] - t[I][J]) > EPS) goto iter10;

    iter20:
        cout << "迭代次数: " << IT << endl;

    for (J = 1; J <= N + 1; J++) {
        for (I = 1; I <= M + 1; I++)
            cout << setw(7) << setprecision(4) << t[I][J];
        cout << endl;
    }
    return 0;
}
