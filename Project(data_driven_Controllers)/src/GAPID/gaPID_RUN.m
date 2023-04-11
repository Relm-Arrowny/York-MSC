%GAPID optimiation 

clear all, close all, clc

% setup the simulation 
dt = 5;
popsize = 38;
MaxGenerations = 368; 
timeRange = 750;
Toff = 145
Tstep = -25
TTarget = Toff+Tstep;
opt = stepDataOptions('InputOffset',Toff,'StepAmplitude',Tstep);
s = tf('s');

% load transfer functions models
load data\LTIMODELS.mat;
%select model 
G = ss250100  % model list: ss100175, ss150250, ss250400, ss400310, ss280220, ss250100

%Generate random values for PID
population = rand(popsize,3);
%Set the GA going
options = optimoptions(@ga,'PopulationSize',popsize,'MaxGenerations',MaxGenerations,'InitialPopulation',population,'MaxStallGenerations', 15, 'OutputFcn',@myfun);
[x,fval,exitflag,output,population,scores] = ga(@(K)pidGA(G,dt,K,timeRange, Tstep, Toff),3,-eye(3),zeros(3,1),[],[],[],[],[],options);

%==================================================================================================================================
%the rest is for showing the data
load history.mat
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
    %ylim([Toff,TTarget+20]);
    ylim([TTarget-20,Toff,]);

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
    subplot(3,1,1), hold on
    plot(t,y,'LineWidth',1+.1*gen,'Color',[(MaxGenerations-gen)/MaxGenerations 0 gen/MaxGenerations],'LineWidth',1.2);
    %ylim([Toff,TTarget+20]);
    ylim([TTarget-20,Toff,]);
    
    
    box on, grid on
    subplot(3,1,2), hold on
    CTRLtf = K/(1+K*G);
    u = lsim(K,TTarget-y,t);
    plot(t,u,'LineWidth',1+.1*gen,'Color',[(MaxGenerations-gen)/MaxGenerations 0 gen/MaxGenerations],'LineWidth',1.2);
    %ylim([-1 2])
    box on, grid on
    subplot(3,1,3), hold on
    Q = 1;
    R = .001;
    J = dt*cumsum(Q*(1-y(:)).^2 + R*u(:).^2);
    plot(t,J,'LineWidth',1+.1*gen,'Color',[(MaxGenerations-gen)/MaxGenerations 0 gen/MaxGenerations],'LineWidth',1.2);
end
box on, grid on
set(gcf,'Position',[100 100 550 350])
set(gcf,'PaperPositionMode','auto')