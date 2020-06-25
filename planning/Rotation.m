classdef Rotation
    methods(Static=true)

        function rotMat= RotationZ(angle_rad)
                 rotMat = [cos(angle_rad), -sin(angle_rad), 0;
                           sin(angle_rad), cos(angle_rad),  0;
                                0       ,        0      ,  1];
        end
    endmethods
endclassdef
