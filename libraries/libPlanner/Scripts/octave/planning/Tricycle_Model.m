classdef Tricycle_Model

methods
function TricycleModel= Configuration(this)
    %%% all measurements in SI units

    % in body frame which is centered at rear axle center and x axis pointing in the direction of orientaion of vehicle
    %          x
    %          ^
    %          |
    % y <------|(z out of the plane)
    % all these distances are between point of contact (not center of wheels)
    TricycleModel.Body_FrontWheel = [2.0, 0, 0];
    TricycleModel.Body_LeftWheel = [0, 0.5, 0];
    TricycleModel.Body_RightWheel = [0, 0.5, 0];

    % irrespective of frame
    TricycleModel.LeftWheelRadius = 0.1;
    TricycleModel.RightWheelRadius = 0.1;
    TricycleModel.FrontWheelRadius = 0.1;
    TricycleModel.LeftWheelWidth = 0.05;
    TricycleModel.RightWheelWidth = 0.05;
    TricycleModel.FrontWheelWidth = 0.05;
    TricycleModel.VehicleMass = 100.00; #can be varying as well

    % frictional coefficients & vehicle wear and tear

    % hull points in 2D
end

% Kinematics and dynamics: radius and width of all three wheels matter, obviously their relative positions as well

function nextState = kinematics_tricycle(this, currState, currCtrl)
    % state of the robot: position, velocity, direction, ang vel of rear axle center and current steer angle of front wheel
    % (for 2D: World_X, World_Y, World_Theta_rad, World_Xdot, World_Ydot, World_Omega, Body_SteerAngle_rad)
    % control of the robot: acceleration, ang acceleration (for 2D: World_Xddot, World_Yddot, World_Omegadot)
    currState
    TricycleConfig= this.Configuration();
    World_Theta_rad=currState(3);
    World_Body = Rotation.RotationZ(World_Theta_rad);
    Body_SteerAngle_rad=currState(7);
    % radius of rotation magnitude of front wheel
    if (sin(Body_SteerAngle_rad)!=0)
        radius = TricycleConfig.Body_FrontWheel(1) / sin(Body_SteerAngle_rad);
    end
    % center of rotation in body frame a.k.a radius of rear axle center
    Body_CenterOfRotation = [0, TricycleConfig.Body_FrontWheel(1)/tan(Body_SteerAngle_rad), 0]';
    % center of rotation in world frame
    World_CenterOfRotation = World_Body * Body_CenterOfRotation;
    % xc + Rcos(delta_theta), yc + Rsin(delta_theta)
    nextState=currState;
end

function nextState = dynamics_tricycle(this, currState, currCtrl)
    nextState=currState;
end

end
end
