//
// Created by yuqi on 24-4-6.

#include<algorithm>
#include<iostream>
#include "../../../../../usr/include/stdint.h"

#include"heat_transfer_algorithm.h"


/**
 *
 * @author yanyuqi
 * @date 2024.4.6
 * @brief 例题4——12的题解 ，张老师微信作业第九次
 */
inline double GetFo(double time, double a,double wall_thickness) {
    return a*time/wall_thickness/wall_thickness;
}
class Solution4_12 {
public:
    const double wall_thick_ = 0.019; ///墙壁厚度
    const double origin_temp_ = 20.0 + 273; ///初始温度
    const double glue_need_temp_ = 150.0 + 273.0; ///胶固化所需要的温度
    const double plastic_lamda_ = 0.156; ///塑料导热系数
    const double plastic_alpha_ = 0.000000008; /// 塑料热传导率
    const double q_ = 500.0; ///加热版热流密度
    const unsigned int point_num_ = 1000; ///节点数量
    const double delta_x_ = wall_thick_ / (point_num_ - 1); ///端点之间的距离

    Solution4_12() {
        temp_now_ = new double[point_num_];
        temp_last_ = new double[point_num_];

        for (unsigned int i = 0; i < point_num_; i++)
            temp_now_[i] = origin_temp_; //初始化节点温度

        std::swap(temp_now_, temp_last_); //初始化后，初始节点变成了下一次迭代的“last”
    }

    unsigned int GetTime() {
        return GetTime(glue_need_temp_);
    }

    /**
     *
     * @param need_temp 胶水需要的温度
     * @return 到达温宿所需时间
     */
    unsigned int GetTime(double need_temp) {
        /**
         * @warning Fo需要满足稳定性条件，所以这个是错误的
         */
        double Fo = heattransfer::GetFo(1.0, plastic_alpha_, delta_x_);
        const double Fo_need_plus_ = plastic_alpha_ / delta_x_ / delta_x_; //每次迭代时累加，减少乘法次数，加速获得FO的速度

        for (unsigned int time = 0; time < UINT32_MAX; time++) {
            const unsigned int edge = point_num_ - 1;
            //这两个const 是为了代码好阅读，编译器优化的时候应该会优化掉，不会影响性能
            const unsigned int center = 0;


            temp_now_[edge] = 2 * Fo * (temp_last_[edge - 1] + q_ * delta_x_ / plastic_lamda_) + (1 - 2 * Fo) * temp_last_[center]; ///更新加热的那一边

            for (unsigned int i = edge - 1; i>0;i--) //更新中间的那一堆节点
                temp_now_[i] = Fo * (temp_last_[i - 1] + temp_last_[i + 1]) +(1 - 2 * Fo) * temp_last_[i];

            temp_now_[center] = 2 * Fo * temp_last_[center + 1] +(1 - 2 * Fo) * temp_last_[center]; //更新胶水所在的节点

            if (temp_now_[center] > need_temp) return time;

            std::swap(temp_now_,temp_last_);
            Fo += Fo_need_plus_; //得到下一次循环时的Fo
            //std::cout<<Fo<<'\n';
        }
        return -1; //程序正常运行，不会执行到这一步
    }

private :
    double* temp_now_;
    //两个动态数组来交替代表不同的时间状态
    double* temp_last_;
};
