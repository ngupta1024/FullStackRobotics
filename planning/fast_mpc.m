function fast_mpc()
    # state of the robot will be in the world frame
    tricycle= Tricycle_Model();
    currState=zeros(7,1);
    currCtrl = zeros(3,1);
    nextState = tricycle.kinematics_tricycle(currState, currCtrl);
    %nextState = dynamics_tricycle(currState, currCtrl);
    nextState
end

fast_mpc();
