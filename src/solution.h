//
// Created by 19003 on 2024/4/1.
//

#ifndef SOLUTION_H
#define SOLUTION_H

#include"heat_transfer_algorithm.h"

namespace heattransfer {
    /**
     *暂时烂尾中
     * @brief 传热学第七版课本例题４－２的解
     * 可以调用构造函数来初始化变量,以适应应不同数值
     */
    class Solution_4_2 {
    public:
        /*
         * 课本中那些毫无意义的变量命名不符合现代c++命名规范
         */
        double trb_; ///右侧边界面温度
        double tlb_; ///左侧边界面温度
        double ttb_; ///顶部边界面温度
        double tbb_; ///底部边界面温度

        double EPS_; ///控制迭代过程终止的误差

        unsigned int iterator_time_; ///迭代次数对应课本中的IT
        unsigned int max_iterator_time_; ///最大迭代次数,对应课本中的K

        unsigned int x_grids_number_; ///x方向的网格数量,对应课本中的N
        unsigned int y_grids_number_; ///y方向上的网格划分,对应课本中的M
    };

    /**
     *
     * @date  2024.4.1
     * @brief 传热学第七版习题４－６，张老师微信作业第八次第四题的解
     * @warning 请注意温度的单位，开尔文和摄氏度，本程序中所有温度都为开尔文表示
     */
    class Solution_4_6 {
    public:
        const double default_wall_thick_ = 0.3; ///墙壁的厚度
        const double default_wall_lamda_ = 36.4; ///墙壁的导热率
        const double default_h_1_ = 60; ///左侧的表面传热系数
        const double default_h_2_ = 300; ///右侧的表面传热系数
        const double default_tf_1_ = 25 + 273; ///左侧流体温度
        const double default_tf_2_ = 215 + 273; ///右侧流体温度
        const double default_qv_ = 200000; ///内热源
        const double default_EPS=0.01;///控制终止时的误差大小
        /**
         *@brief 在题目信息改变时，就可以调用构造函数自定义数据
         */
        Solution_4_6(double wall_thick, double wall_lamda, double h_1, double h_2, double tf_1, double tf_2, double qv)
            : wall_thick_(wall_thick),
              wall_lamda_(wall_lamda),
              h_1_(h_1),
              h_2_(h_2),
              tf_1_(tf_1),
              tf_2_(tf_2),
              qv_(qv) {
            is_default = false; //标记调用了构造函数，使用自定义方法
        }

        Solution_4_6() = default;

        int print_answer();

    private:
        bool is_default = true;
        double wall_thick_ = default_wall_thick_; ///墙壁的厚度
        double wall_lamda_ = default_wall_lamda_; ///墙壁的导热率
        double h_1_ = default_h_1_; ///左侧的表面传热系数
        double h_2_ = default_h_2_; ///右侧的表面传热系数
        double tf_1_ = default_tf_1_; ///左侧流体温度
        double tf_2_ = default_tf_2_; ///右侧流体温度
        double qv_ = default_qv_; ///内热源
        double EPS=default_EPS;///终止误差
    };
};


#endif //SOLUTION_H
