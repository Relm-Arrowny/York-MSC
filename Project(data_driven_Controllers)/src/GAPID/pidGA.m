%Function perform the PID simulation and calculation the cost
function J = pidGA(G,dt,parms,timeRange, Tstep, Toff)
%Setup PID in close loop feedback
s = tf('s');
K = parms(1) + parms(2)/s + parms(3)*s/(1+timeRange*s);
Loop = series(K,G);
ClosedLoop = feedback(Loop,1);
% define time range
t = 0:dt:timeRange;
%set the target temperature
TargetT = Tstep+Toff
%set the starting temperature
opt = stepDataOptions('InputOffset',Toff,'StepAmplitude',Tstep);
%generate the 
[y,t] = step(ClosedLoop,t, opt);

% Calucate the error function
Q = 1000;
R = 1;
To = 0.1
Tint = 20

%===================================================================================
% CF0 / No overshoot and No undershoot
%  for k = 1:numel(y) % indices
%      tempT =  y(k)-TargetT;%abs(TargetT - y(k));
%      if k<Tint
%           erro(k) = 0
%      elseif tempT<-To
%          error(k) = exp(-tempT)*Q
%      elseif  tempT > To 
%             error(k) = exp(tempT)*R;
%      else
%          error(k) = abs(tempT);
%      end
%  end 
% 
% J = dt*sum(error(:))
% 

%CF2 /standard
u = lsim(K,TargetT-y,t);
J = dt*sum(Q*(TargetT-y(:)).^2 + R*u(:).^2)

step(ClosedLoop,t, opt)
h = findobj(gcf,'type','line');
set(h,'linewidth',2);
drawnow