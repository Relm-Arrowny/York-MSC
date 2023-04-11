%Setup plant
% These are commented out as I do the loading from setT.m but can be
% uncomment if one only want to create MPC but not test it.
%load LTIMODELSOPlus.mat;
%plant = [ss100175, ss150250, ss250400, ss400310_2, ss300200_2, ss250100_2]
%names = ["mpcsss100175", "mpcsss150250", "mpcsss250400", "mpcsss400310", "mpcsss280220", "mpcsss250100"]
%Create an MPC controller with one second sampling time, 20 steps prediction horizon and 5 steps control horizon.
% 
% mpcobj = mpc(plant,ts,P,M,W,MV,OV,DV) specifies the following controller properties. If any of these values are omitted or empty, the default values apply.
% 
% P sets the PredictionHorizon property.
% 
% M sets the ControlHorizon property.
% 
% W sets the Weights property.
% 
% MV sets the ManipulatedVariables property.
% 
% OV sets the OutputVariables property.
% 
% DV sets the DisturbanceVariables property.

for i = 1:length(plant)
    mpcS = mpc(plant(i),5,12,6);
    mpcS.MV(1).Type = 0:100;
    mpcS.MV(1).RateMin = -100;
    mpcS.MV(1).RateMax = 100;
    eval(sprintf('%s  = mpcS', names(i)))
end