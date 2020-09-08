clear all;
close all;
disp('Running...')

function outstate = nonholoRobotKin(state, ctrl)
   dt=0.001;
   outstate = [state(1)+ctrl(1)*cos(state(3))*dt;
               state(2)+ctrl(1)*sin(state(3))*dt;
               state(3)+ctrl(2)*dt];
endfunction

function outstate = nonholoRobotKinMotion(state, ctrl, time)
    dt=0.001;
    allStates=[];
    for i=0:dt:time
        state=nonholoRobotKin(state,ctrl);
        allStates(end+1,:)=state';
    endfor
    plot(allStates(:,1), allStates(:,2));
    hold on;
    axis("equal");
    outstate=state;
endfunction

state = nonholoRobotKinMotion([0;0;0],[1;1],2*pi/1)
