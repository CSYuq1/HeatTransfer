//
// Created by 19003 on 24-3-31.
//

#ifndef ALGORITHMS_H
#define ALGORITHMS_H

/*!
 * @author yanyuqi
 * @date 2024.3.31
 * @brief 传热学
 */
namespace heattransfer {
    /*!
     *  @return 傅里叶级数
     */
     inline double GetFo(double time, double a,double wall_thickness) {
         return a*time/wall_thickness/wall_thickness;
     }


}

#endif //ALGORITHMS_H
