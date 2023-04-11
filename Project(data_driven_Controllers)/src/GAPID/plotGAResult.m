%this is just for ploting
clear all, close all, clc
% set the simulation 
timeRange = 750;
Toff = 350
Tstep = 25
TTarget = Toff+Tstep;
opt = stepDataOptions('InputOffset',Toff,'StepAmplitude',Tstep);
s = tf('s');

% load transfer functions models
load data\LTIMODELS.mat;
G = ss250400


%load history.mat
MaxGenerations = length(history(1,1,:))-2

for k=1:MaxGenerations
    sortedcost(:,k) = sort(cost(:,k));
end

imagesc(log(sortedcost(:,1:MaxGenerations)))
colorbar
set(gcf,'Position',[100 100 600 300])
set(gcf,'PaperPositionMode','auto')

%% plot PID space distribution 
figure
    hold on
    for k=1:MaxGenerations
        for j=1:popsize
            scatter3(history(j,1,k),history(j,2,k),history(j,3,k),15,[(MaxGenerations-k)/MaxGenerations 0.25 k/MaxGenerations],'filled');
        end
    end
      [B,I] = sort(cost(:,MaxGenerations));  
      scatter3(history(I(1),1,MaxGenerations),history(I(1),2,MaxGenerations),history(I(1),3,MaxGenerations),100,[0 0 0],'filled')
        view(69,24)
    box on
    xlabel('P')
    ylabel('I')
    zlabel('D')
set(gcf,'Position',[100 100 350 250])
set(gcf,'PaperPositionMode','auto')

%% Plot Last Generation 
gen = MaxGenerations;
t = 0:dt:timeRange;
s = tf('s');
figure
hold on
for k=1:popsize
    K = history(k,1,gen) + history(k,2,gen)/s + history(k,3,gen)*s/(1+dt*s);
    L = series(K,G);
    CL = feedback(L,1);
    [y,t] = step(CL,t, opt);
    plot(t,y,'LineWidth',1.2);
    ylim([Toff,TTarget+20]);
    %ylim([TTarget-20,Toff,]);

end
box on, grid on
set(gcf,'Position',[100 100 550 250])
set(gcf,'PaperPositionMode','auto')


%% Plot BEST of each Generation
figure
for gen=1:MaxGenerations
    [B,I] = sort(cost(:,gen));
    K = history(I(1),1,gen) + history(I(1),2,gen)/s + history(I(1),3,gen)*s/(1+dt*s);
    pid (gen,:) = [history(I(1),1,gen) history(I(1),2,gen) history(I(1),3,gen)];
    L = series(K,G);
    CL = feedback(L,1);
    [y,t] = step(CL,t, opt);
    hold on
    plot(t,y,'LineWidth',1+.1*gen,'LineWidth',1.2);
    ylim([Toff,TTarget+20]);

end
box on, grid on
set(gcf,'Position',[100 100 550 350])
set(gcf,'PaperPositionMode','auto')