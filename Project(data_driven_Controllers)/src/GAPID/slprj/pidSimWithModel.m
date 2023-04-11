%clear all, close all, clc
load data\LTIMODELSOPlus.mat;
%preSet names for controler 
plant = [ss100175, ss150250, ss250400, ss400310, ss280220, ss250100]
%plant = [ss100175, BHeating, BHeating, ss400310, bc289220, ss250100]
names = ["CF1PID100175", "CF1PID150250", "CF1PID250400", "CF1PID400310", "CF1PID280220", "CF1PID250100"]
arrayP = [7.1484, 7.6892, 8.7676, 19.2205, 22.9295, 23.2065]
arrayI = [0.0386, 0.0473, 0.0472, 0.0603, 0.0742, 0.0737]
arrayD = [1.5475, 2.6255, 4.0386, 5.0104, 5.3032, 7.9440]



% set the set end temperature for datat generation 
tempRange = [120, 160, 240, 400, 300, 200, 120]
tstepSize = 10
stepwait = 750
modelLoading = 4
sys = stack(1,ss100175,ss150250, ss250400, ss400310_2, ss300200_2, ss250100_2)
sys.SamplingGrid = struct('FreeMove',[1;2;3;4;5;6]);

for i = 1:length(tempRange)-1
    
    plantSwitch = i
    v = [tempRange(i)] 
    tset = repelem(v,modelLoading)
    if tempRange(i+1)>tempRange(i)
        tset = [tset, tempRange(i):tstepSize:tempRange(i+1)]
    else
        tset = [tset, tempRange(i):-tstepSize:tempRange(i+1)]
    end
    
    Ts = stepwait*length(tset())
    %eval(sprintf('mpcobj = %s', names(i)))  
    PG = arrayP(i)
    IG = arrayI(i)
    DG = arrayD(i)
    simJob = sim('GAPIDFULLMODEL')
    eval(sprintf('data%s = simJob', names(i)))
    %csvwrite(join(["datat", tstepSize , names(i),".csv"]), datampcsss100175.tout(74*100:end),datampcsss100175.Temperature(74*100:end))
    %csvwrite(join(["datat", tstepSize , names(i),".csv"]), dataCF1PID100175.tout, dataCF1PID100175.setT, dataCF1PID100175.Temperature)

end 
