#ifndef SOLUTION_H
#define SOLUTION_H//本来写成头文件了，但是感觉没必要，干脆写成一个文件了

#include<iostream>
#include<vector>
#include<cmath>
#include<cstdint>


namespace heattransfer {
    using std::vector;
    using std::abs;
    /**
     *
     * @date  2024.4.1
     * @brief 传热学第七版习题４－６，张老师微信作业第八次第四题的解
     * @warning 请注意温度的单位，开尔文和摄氏度，本程序中所有温度都为开尔文表示
     */
    class Solution_4_6 {
    public:
        static constexpr double default_wall_thick_ = 0.3; ///墙壁的厚度
        static constexpr double default_wall_lamda_ = 36.4; ///墙壁的导热率
        static constexpr double default_h_1_ = 60.0; ///左侧的表面传热系数
        static constexpr double default_h_2_ = 300.0; ///右侧的表面传热系数
        static constexpr double default_tf_1_ = 25.0 + 273.0; ///左侧流体温度
        static constexpr double default_tf_2_ = 215.0 + 273.0; ///右侧流体温度
        static constexpr double default_temp_oringin_ = 20.0 + 273.0; ///初始温度,书上为T0
        static constexpr double default_qv_ = 200000.0; ///内热源
        static constexpr double default_EPS_ = 0.0000000001; ///控制终止时的误差大小
        static constexpr unsigned int default_point_size_ = 11; ///默认情况下划分的点位数量
        static constexpr unsigned int maximum_iterations_ = 100000000; //最大迭代次数

        Solution_4_6() {
            temp_ = new double[default_point_size_];
            temp_[0] = 401.07 + 273.0; ///计算器手搓
            for (unsigned int i = 1; i < point_size_ - 1; i++)
                temp_[i] = default_temp_oringin_;
            temp_[point_size_ - 1] = 339.78 + 273.0; ///手搓
        }

        /**
         * @warning 请注意参数输入顺序，构造函数是用clion生成的，我也不知道为什么顺序会这样
         */
        Solution_4_6(const double eps, const double tf2, const double qv, const double tf1, const double h2,
                     const double h1, const double wallLamda,
                     const double wallThick, const unsigned int pointSize) : EPS_(eps), tf_2_(tf2), qv_(qv), tf_1_(tf1),
                                                                             h_2_(h2),
                                                                             h_1_(h1), wall_lamda_(wallLamda),
                                                                             wall_thick_(wallThick),
                                                                             point_size_(pointSize) {
            for (unsigned int i = 1; i < pointSize - 1; i++)
                temp_[i] = default_temp_oringin_;
            temp_[pointSize - 1] = tf2;
        };


        double* GetAnswer();

        double* GetFinalAnswer() {
            double delta_x = wall_thick_ / (point_size_ - 1);
            for (unsigned int j = 0; j < UINT32_MAX; j++) {
                for (unsigned int i = 1; i < point_size_ - 1; i++) {
                    double eps = (temp_[i - 1] +
                                  temp_[i + 1] +
                                  qv_ * delta_x * delta_x / wall_lamda_) / 2
                                 - temp_[i];

                    if (eps < EPS_ && eps > EPS_negative_) //当小于最小误差时，趋向于稳定，直接退出
                        return temp_;
                    temp_[i] += eps;
                }
            }

            return temp_;
        }

        /**
         * @brief 将最终结果输出到控制台
         */
        void PrintAnswer(double* temp) const {
            using namespace std;
            ios::sync_with_stdio(false);
            cout.tie(nullptr);
            for (unsigned int i = 0; i < point_size_; i++)//应该写成迭代循环的，这样太丑了
                cout << i << ": " << temp[i] - 273.0 << '\n';
        }

    private:
        bool is_default = true; ///这个标识符号也没啥用
        unsigned int point_size_ = default_point_size_;
        double wall_thick_ = default_wall_thick_; ///墙壁的厚度
        double wall_lamda_ = default_wall_lamda_; ///墙壁的导热率
        double h_1_ = default_h_1_; ///左侧的表面传热系数
        double h_2_ = default_h_2_; ///右侧的表面传热系数
        double tf_1_ = default_tf_1_; ///左侧流体温度
        double tf_2_ = default_tf_2_; ///右侧流体温度
        double qv_ = default_qv_; ///内热源
        double EPS_ = default_EPS_; ///终止误差
        double EPS_negative_ = -default_EPS_;
        double* temp_ = new double[default_point_size_];
        // std::unique_ptr<> 想改成智能指针，不会写
        // std::vector<double[]> result;
    };
};


#endif //SOLUTION_H
