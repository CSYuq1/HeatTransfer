//
// Created by 19003 on 24-3-31.
//

#ifndef ALGORITHMS_H
#define ALGORITHMS_H
#include<cmath>
using std::cin,std::cout,std::ios;

/*!
 * @author yanyuqi
 * @date 2024.3.31
 * @brief 传热学
 */
namespace heattransfer {
    /*!
     *  @return 傅里叶级数
     */
    static inline double GetFo(double time, double a, double wall_thickness);

    static inline double GetLP(double temp_left, double temp_center, double lamda, double delta_x, double delta_y,
                               double area);

    static inline double GetRP(double temp_right, double temp_center, double lamda, double delta_x, double deltay);

    static inline double GetTP(double temp_front, double temp_center, double lamda, double delta_x, double deltay);

    static inline double GetBP(double temp_back, double temp_center, double lamda, double delta_x, double deltay);

    static inline double GetAny(double temp_in, double temp_center, double lamda, double delta_x, double delta_y,
                                double area);
}

#endif //ALGORITHMS_H
