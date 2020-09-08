function outstate = nonholoRobotKin(state, ctrl)
   %outstate = [state(1)+ctrl(1)*cos(state(3))*0.01;
   %         state(2)+ctrl(1)*cos(state(3))*0.01;
   %         state(3)+ctrl(2)*0.01];
   outstate=state;
end

function outstate = nonholoRobotKinMotion(state, ctrl, time)
    %for i=0:0.01:time
    %   state=nonholoRobotKin(state,ctrl);
    %end
    outstate=state;
end

%state = nonholoRobotKinMotion([0;0;0],[10;10],2*pi/10)
