//
// Created by yuqi on 24-4-6.
/**
 *
 * @author yanyuqi
 * @date 2024.4.6
 * @version 2024.4.17
 * @brief 例题4——12的题解 ，张老师微信作业第九次
 */
#include<algorithm>
#include<iostream>
#include<cmath>
#include<cstdint>
#include<ranges>

inline double GetFo(double time, double a, double wall_thickness) {
    return a * time / wall_thickness / wall_thickness;
}

//两个动态数组来交替代表不同的时间状态
double*            temp_now_;
double*            temp_last_;
constexpr double   wall_thick_     = 0.019;         ///墙壁厚度
constexpr double   origin_temp_    = 20.0 + 273.0;  ///初始温度
constexpr double   glue_need_temp_ = 150.0 + 273.0; ///胶固化所需要的温度
constexpr double   plastic_lamda_  = 0.156;         ///塑料导热系数
constexpr double   plastic_alpha_  = 0.00000008;    /// 塑料热传导率
constexpr double   q_              = 500.0;         ///加热版热流密度
constexpr double   delta_time_     = 0.001;
constexpr double   need_temp       = 500;
const unsigned int max_point_num_  = wall_thick_ / (sqrt(2 * plastic_alpha_)) + 1; ///最大节点数量，根据稳定性条件写不等式求出
unsigned int       point_num_      = max_point_num_;
const double       delta_x_        = wall_thick_ / (point_num_ - 1); ///端点之间的距离
const double       Fo              = GetFo(delta_time_, plastic_alpha_, delta_x_);

/**
 *
 * @param need_temp 胶水需要的温度
 * @return 到达温度所需时间，-1表示Fo不满足稳定性条件
 */
inline double GetTime(const double need_temp) {
    if (Fo > 1 / 2.0) return -1; //不满足稳定性条件返回-1，表示异常

    const unsigned int     edge   = point_num_ - 1;
    constexpr unsigned int center = 0;

    for (unsigned int time = 0; time < UINT32_MAX; time++) {
        temp_now_[edge] = 2 * Fo * (temp_last_[edge - 1] + q_ * delta_x_ / plastic_lamda_) + (1 - 2 * Fo) * temp_last_[
                              edge];                     //更新加热的那一边
        for (unsigned int i = edge - 1; i > center; i--) //更新中间的那一堆节点
            temp_now_[i]    = Fo * (temp_last_[i - 1] + temp_last_[i + 1]) + (1 - 2 * Fo) * temp_last_[i];

        temp_now_[center] = 2 * Fo * temp_last_[center + 1] + (1 - 2 * Fo) * temp_last_[center]; //更新胶水所在的节点
        if (temp_now_[center] > need_temp) return time * delta_time_;
        std::swap(temp_now_, temp_last_);
    }
    return -1; //程序正常运行，不会执行到这一步
}

int main() {
    //两个动态数组来交替代表不同的时间状态
    temp_now_  = new double[point_num_];
    temp_last_ = new double[point_num_];
    std::ranges::fill_n(temp_now_, point_num_, origin_temp_); //初始化节点温度
    std::ranges::fill_n(temp_last_, point_num_, origin_temp_);

    std::cout << GetTime(500.0) << '\n';
    return 0;
}

