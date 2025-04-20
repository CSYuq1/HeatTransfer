/**
 *
 * @date  2024.4.1
 * @brief 传热学第七版习题４－６，张老师微信作业第八次第四题的解
 * @warning 请注意温度的单位，开尔文和摄氏度，本程序中所有温度都为开尔文表示
 */
#include<iostream>
#include<vector>
#include<cmath>
#include<cstdint>

using std::vector;
using std::abs;

constexpr double       wall_thick_         = 0.3;           ///墙壁的厚度
constexpr double       wall_lamda_         = 36.4;          ///墙壁的导热率
constexpr double       h_1_                = 60.0;          ///左侧的表面传热系数
constexpr double       h_2_                = 300.0;         ///右侧的表面传热系数
constexpr double       tf_1_               = 25.0 + 273.0;  ///左侧流体温度
constexpr double       tf_2_               = 215.0 + 273.0; ///右侧流体温度
constexpr double       temp_oringin_       = 20.0 + 273.0;  ///初始温度,书上为T0
constexpr double       qv_                 = 200000.0;      ///内热源
constexpr double       EPS_                = 0.0000000001;  ///控制终止时的误差大小
constexpr unsigned int point_size_         = 11;            ///默认情况下划分的点位数量
constexpr unsigned int maximum_iterations_ = 100000;        //最大迭代次数
double*                temp_               = new double[point_size_];

void PrintAnswer(double* temp) {
    using namespace std;
    ios::sync_with_stdio(false);
    cout.tie(nullptr);
    for (unsigned int i = 0; i < point_size_; i++) //应该写成迭代循环的，这样太丑了
        cout << i << ": " << temp[i] - 273.0 << '\n';
}

int main() {
    temp_    = new double[point_size_];
    temp_[0] = 401.07 + 273.0; ///计算器手搓
    for (unsigned int i = 1; i < point_size_ - 1; i++)
        temp_[i]        = temp_oringin_;
    temp_[point_size_ - 1] = 339.78 + 273.0; ///手搓


    double delta_x = wall_thick_ / (point_size_ - 1);
    for (unsigned int j = 0; j < UINT32_MAX; j++) {
        for (unsigned int i = 1; i < point_size_ - 1; i++) {
            double eps = (temp_[i - 1] +
                          temp_[i + 1] +
                          qv_ * delta_x * delta_x / wall_lamda_) / 2
                         - temp_[i];

            if (eps < EPS_) //当小于最小误差时，趋向于稳定，直接退出
                goto end;
            temp_[i] += eps;
        }
    }
end:
    PrintAnswer(temp_);
    return 0;
}
