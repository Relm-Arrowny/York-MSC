%Generate data for differnet PID Gain for different cryostat model
clear all, close all, clc

% set the simulation 
dt = 5;
timeRange = 1000;
Tstep = 10
% load transfer functions models
load data\LTIMODELS.mat;
plant = [ss100175, ss150250, ss250400, ss400310, ss280220, ss250100]
%Pid gain setup
PIDModel =  "SGAPID"  %"NOGAPID" % 

if strcmp(PIDModel,"SGAPID") 
%-------------  PID setting for SGAPID -----------------------
    arrayP = [7.1484, 7.6892, 8.7676, 19.2205, 22.9295, 23.2065]
    arrayI = [0.0386, 0.0473, 0.0472, 0.0603, 0.0742, 0.0737]
    arrayD = [1.5475, 2.6255, 4.0386, 5.0104, 5.3032, 7.9440]
elseif strcmp(PIDModel,"NOGAPID")
    %-------------- PID setting for NOGAPID ------------------------
    arrayP = [5.8234, 6.1841, 6.9672, 23.9853, 41.25, 44.4064]
    arrayI = [0.0112, 0.0161, 0.0115, 0.0781, 0.1571, 0.1598]
    arrayD = [0.1534, 2.466, 1.5029, 6.6923, 8.3848, 9.711]
else
    error("PID not set")
end
%Setup PID in close loop feedback
counter = 0
dataY = []
dataT = []
dataST = []
tempRange = [120, 180, 250, 400, 300, 200, 120]
for i = 1:length(tempRange)-1
        if tempRange(i)>380
            Tstep = -Tstep
        end
    for k = tempRange(i):Tstep:(tempRange(i+1)-Tstep)
        %setup the PID controller and cryostat
        G = plant(i)
        s = tf('s');
        K = arrayP(i) + arrayI(i)/s + arrayP(i)*s/(1+timeRange*s);
        Loop = series(K,G);
        ClosedLoop = feedback(Loop,1);
        % define time range
        t = 0:dt:timeRange;
        opt = stepDataOptions('InputOffset',k,'StepAmplitude',Tstep);
        %generate the data
        [y,t] = step(ClosedLoop,t, opt);
        N=length(t)
        sT=zeros(N,1) + k+Tstep
        %save the all the temperature to a single array/workspace
        dataT = cat(1,dataT,t+timeRange*counter)
        dataY = cat(1,dataY,y)
        dataST = cat(1,dataST,sT)
        plot(t,y) %show plot for checking
        hold on
        counter = counter+1
    end
end