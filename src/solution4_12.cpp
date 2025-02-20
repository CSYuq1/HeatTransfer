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
#include <cstdint>

//#include"heat_transfer_algorithm.h"


namespace heattransfer {
    inline double GetFo(double time, double a, double wall_thickness) {
    return a * time / wall_thickness / wall_thickness;
}
    class Solution4_12 {
    public:
        const double wall_thick_ = 0.019; ///墙壁厚度
        const double origin_temp_ = 20.0 + 273.0; ///初始温度
        const double glue_need_temp_ = 150.0 + 273.0; ///胶固化所需要的温度
        const double plastic_lamda_ = 0.156; ///塑料导热系数
        const double plastic_alpha_ = 0.00000008; /// 塑料热传导率
        const double q_ = 500.0; ///加热版热流密度
        const double delta_time_ = 0.001;
        const unsigned int max_point_num_ = wall_thick_ / (sqrt(2 * plastic_alpha_))+1; ///最大节点数量，根据稳定性条件写不等式求出
        unsigned int point_num_ = max_point_num_;


        const double delta_x_ = wall_thick_ / (point_num_ - 1); ///端点之间的距离
        const double Fo = heattransfer::GetFo(delta_time_, plastic_alpha_, delta_x_);

        /**
         *
         * @param point_num 自定义节点数量以满足稳定性条件，太大了会自动赋值为符合节点数量的最大值
         */
        void set_point_num(unsigned int point_num) {
            point_num_ = point_num < max_point_num_ ? point_num : max_point_num_;
        }

        Solution4_12() {
            temp_now_ = new double[point_num_];
            temp_last_ = new double[point_num_];

            for (unsigned int i = 0; i < point_num_; i++)
                temp_last_[i] = temp_now_[i] = origin_temp_; //初始化节点温度

            std::swap(temp_now_, temp_last_); //初始化后，初始节点变成了下一次迭代的“last”
        }

        unsigned int GetTime() {
            return GetTime(glue_need_temp_);
        }

        /**
         *
         * @param need_temp 胶水需要的温度
         * @return 到达温度所需时间，-1表示Fo不满足稳定性条件
         */
        unsigned int GetTime(const double need_temp) {

            if (Fo > 1 / 2.0) return -1; //不满足稳定性条件返回-1，表示异常

            const unsigned int edge = point_num_ - 1;
            //这两个const 是为了代码好阅读，编译器优化的时候应该会优化掉，不会影响性能
            const unsigned int center = 0;
            for (unsigned int time = 0; time < UINT32_MAX; time++) {

                temp_now_[edge] = 2 * Fo * (temp_last_[edge - 1] + q_ * delta_x_ / plastic_lamda_) + (1 - 2 * Fo) *
                                  temp_last_[edge]; //更新加热的那一边


                for (unsigned int i = edge - 1; i > center; i--) //更新中间的那一堆节点
                    temp_now_[i] = Fo * (temp_last_[i - 1] + temp_last_[i + 1]) + (1 - 2 * Fo) * temp_last_[i];

                temp_now_[center] = 2 * Fo * temp_last_[center + 1] + (1 - 2 * Fo) * temp_last_[center];//更新胶水所在的节点


                if (temp_now_[center] > need_temp) return time * delta_time_;
               // std::cout << temp_now_[center] << '\n'; //调试时使用
                std::swap(temp_now_, temp_last_);
            }
            return -1; //程序正常运行，不会执行到这一步
        }

    private :
        double* temp_now_;
        //两个动态数组来交替代表不同的时间状态
        double* temp_last_;
    };
}
