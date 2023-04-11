clear all, close all, clc
load LTIMODELSOPlus.mat;
%preSet names for controler 
plant = [ss100175, ss150250, ss250400, ss400310_2, ss300200_2, ss250100_2]
names = ["mpcsss100175", "mpcsss150250", "mpcsss250400", "mpcsss400310", "mpcsss280220", "mpcsss250100"]

% set the set end temperature for datat generation 
tempRange = [120, 170, 250, 400, 310, 220, 120]
%tempRange = [120, 170, 250]

tstepSize = 10
stepwait = 1000
%buffer for the transfer function to settle, buffer = stepwait*Tint
Tint = 4

%load the model in a list so we can perfrom gain scheduling 
sys = stack(1,ss100175,ss150250, ss250400, ss400310_2, ss300200_2, ss250100_2)
sys.SamplingGrid = struct('FreeMove',[1;2;3;4;5;6]);

% this will create all 6 MPC with the model
createMPC
dataY = []
dataT = []
dataST = []
for i = 1:length(tempRange)-1
    %setup cryostat and time steps
    plantSwitch = i
    v = [tempRange(i)] 
    tset = repelem(v,Tint)
    if tempRange(i+1)>tempRange(i)
        tset = [tset, tempRange(i):tstepSize:tempRange(i+1)]
    else
        tset = [tset, tempRange(i):-tstepSize:tempRange(i+1)]
    end
    numOfStep = stepwait/tstepSize
    Ts = stepwait*length(tset())
    %switch plant
    eval(sprintf('mpcobj = %s', names(i)))    
    simJob = sim('MPCFULLMODEL')
    
%      for k = Tint+1:length(tset)
%          temp = repelem(tset(k), numOfStep)
%          temp = temp.';
%          dataST = cat(1,dataST,temp)
%      end
%      
    %cleanUp buffer
    cleanUp = (Tint+6)*numOfStep

    dataT = cat(1,dataT,simJob.Temperature(cleanUp:end))
    dataY = cat(1,dataY,simJob.tout(cleanUp:end))
    
    dataST = cat(1,dataST,simJob.setPoint((cleanUp:end),2))
   
end 
%write out data
csvwrite(join(["data", tstepSize , "mpc",".csv"]), dataY, dataST, dataT)
