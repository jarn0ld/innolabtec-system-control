#ifndef POINT_3D_H
#define POINT_3D_H
#include "action_param_iface.h"

class point_3d : public action_param_iface<point_3d>
{
    double x;
    double y;
    double z;

public:
    point_3d();
    point_3d(double,double,double);

    point_3d getParam();
    inline double getX(){return x;}
    inline double getY(){return y;}
    inline double getZ(){return z;}
};

#endif // POINT_3D_H
