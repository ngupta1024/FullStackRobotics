#include <eigen3/Eigen/Dense>
#include <iostream>


template<typename RobotState, typename ControlInput>
class VehicleModel
{
public:
    VehicleModel()
    {
    }

    virtual ~VehicleModel()=default;

    virtual RobotState Kinematics_DT(const RobotState& currState, const ControlInput& ctrl)=0;
    virtual RobotState Kinematics_CT(const RobotState& currState, const ControlInput& ctrl)=0;

    double m_DT=0;
};

//state of the robot is [x, x_dot]
//ctrl of the robot is [x_ddot]
class PointRobot1d: public virtual VehicleModel<Eigen::Vector2d, double>
{
public:
    PointRobot1d()    
    {
        m_DT=0.1;
    }

    Eigen::Vector2d Kinematics_DT(const Eigen::Vector2d& currState, const double& ctrl) override
	{
        Eigen::Vector2d nextState;
        // s = s_0+ ut+ 1/2at2 
        nextState[0] = currState[0] + m_DT*currState[1] + 0.5*ctrl*std::pow(m_DT,2);
        // v = u+at
        nextState[1] = currState[1] + ctrl*m_DT;
        return nextState;
	}
    
    Eigen::Vector2d Kinematics_CT(const Eigen::Vector2d& currState, const double& ctrl) override
	{
        Eigen::Vector2d stateDot;
        // s_dot = u 
        stateDot[0] = currState[1];
        // v_dot = a
        stateDot[1] = ctrl;
        return stateDot;
	}

};

//state of the robot is [x , y, x_dot, y_dot]
//ctrl of the robot is [x_ddot, y_ddot]
class PointRobot2d: public virtual VehicleModel<Eigen::Vector4d, Eigen::Vector2d>
{
public:
    PointRobot2d()    
    {
        m_DT=0.01;
    }

    Eigen::Vector4d Kinematics_DT(const Eigen::Vector4d& currState, const Eigen::Vector2d& ctrl) override
	{
        //TODO: easy to implement so leaving incomplete right now
        Eigen::Vector4d nextState=currState;
        return nextState;
	}

    Eigen::Vector4d Kinematics_CT(const Eigen::Vector4d& currState, const Eigen::Vector2d& ctrl) override
	{
        //TODO: easy to implement so leaving incomplete right now
        Eigen::Vector4d stateDot=currState;
        return stateDot;
	}
};

//state of the robot is [x,y,theta] where theta is the steering wheel direction
//ctrl of the robot is [vel, ang_vel]
class NonHolonomicPointRobot2d: public virtual VehicleModel<Eigen::Vector3d, Eigen::Vector2d>
{
public:
    NonHolonomicPointRobot2d()
    {
        m_DT=0.001;
    }

    Eigen::Vector3d Kinematics_DT(const Eigen::Vector3d& currState, const Eigen::Vector2d& ctrl) override
    {
        //x= x_0+ vcos(theta)
        //y= y_0+ vsin(theta)
        //theta= theta_0 + ang_vel*dt
        return Eigen::Vector3d{currState[0]+ctrl[0]*std::cos(currState[2])*m_DT, 
                        currState[1]+ctrl[0]*std::sin(currState[2])*m_DT,
                        currState[2]+ctrl[1]*m_DT};
    }

    Eigen::Vector3d Kinematics_CT(const Eigen::Vector3d& currState, const Eigen::Vector2d& ctrl) override
    {
        //x_dot = vcos(theta)
        //y_dot = vsin(theta)
        //theta_dot = ang_vel
        return Eigen::Vector3d{ctrl[0]*std::cos(currState[2]),
                               ctrl[0]*std::sin(currState[2]),
                               ctrl[1]};
    }

    Eigen::Vector3d KinematicsOverTime(const Eigen::Vector3d& currState, const Eigen::Vector2d& ctrl, double time)
    {
        Eigen::Vector3d state = currState;
        for (double i=0; (i*10)/10-(time*10)/10<=1e-4; i+=m_DT)
        {
            state = Kinematics_DT(state, ctrl);
        }
        return state;
    }
};

