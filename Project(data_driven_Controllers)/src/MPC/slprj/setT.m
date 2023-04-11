clear all, close all, clc
%preSet names for controler 
names = ["mpcsss100175", "mpcsss150250", "mpcsss250400", "mpcsss400310", "mpcsss280220", "mpcsss250100"]
load ..\..\LTIMODELS.mat;
% set the set end temperature for datat generation 
tempRange = [100,175, 250, 400, 280, 250, 120]
tstepSize = 5
stepwait = 500

sys = stack(1,ss100175,ss150250, ss250400, ss400310, ss280220, ss250100)
sys.SamplingGrid = struct('FreeMove',[1;2;3;4;5;6]);

createMPC
for i = 1:length(tempRange)-1
    
    plantSwitch = i
    v = [tempRange(i)] 
    tset = repelem(v,75)
    if tempRange(i+1)>tempRange(i)
        tset = [tset, tempRange(i):tstepSize:tempRange(i+1)]
    else
        tset = [tset, tempRange(i):-tstepSize:tempRange(i+1)]
    end
    
    Ts = stepwait*length(tset())
    eval(sprintf('mpcobj = %s', names(i)))    
    simJob = sim('basic')
    eval(sprintf('data%s = simJob', names(i)))
end 
% 
% i = 4
% 
% plantSwitch = 4
% v = [380]
% 
% tset = repelem(v,75)
% tset = [tset, 380:-5:310]
% stepwait = 500
% Ts = stepwait*length(tset())
% eval(sprintf('mpcobj = %s', names(i)))
% %mpcobj = mpcSs100175
% 
% sim('basic')