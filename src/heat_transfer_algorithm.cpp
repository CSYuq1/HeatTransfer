//
// Created by 19003 on 24-3-31.
//

#include<iostream>
#include"heat_transfer_algorithm.h"
using namespace heattransfer;
inline double GetFo(const double time,const double a/*热扩散率*/,const double wall_thickness ) {
    return a*time/wall_thickness/wall_thickness;
}

