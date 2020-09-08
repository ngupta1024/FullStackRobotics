#include <eigen3/Eigen/Dense>
#include <iostream>
#include "libVehicleModel.cpp"

int main()
{
    NonHolonomicPointRobot2d robot;
    Eigen::Vector3d currState{0,0, 0};
    double ang_vel = 1;
    double vel = 10;
    double radius = vel/ang_vel;
    Eigen::Vector2d ctrl{vel, ang_vel};
    Eigen::Vector3d nextState= robot.KinematicsOverTime(currState, ctrl, (2*M_PI*radius)/vel);
    std::cout<<nextState<<std::endl;
    return 0;
}
