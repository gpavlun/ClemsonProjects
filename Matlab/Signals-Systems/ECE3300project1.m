% Gregory Pavlunenko
% C25220578
% MATLAB 1
clear;clc;close all;
% note: C is my native programming language, so some operations done here
%       may be somewhat round about due to a lack of familiarity with
%       MATLAB's abilities

% 1a
year = 1975 : 2023;
rank = [50,50,19,6,50,50,1,8,11,50,50,17,12,9,12,9,18,50,23,50,50,50,...
    50,50,50,16,50,50,22,50,21,50,21,50,24,50,22,11,8,15,2,1,4,1,2,3,...
    14,13,20];
values = [25,10,1];
for c = 1:length(values)
    fprintf("Years in top %0.0f:\n",values(c));
    fprintf("\t%0.0f\n",year(rank<=values(c)));
    if values(c)==1
        fprintf("Percentage of years in %0.0fst = %0.2f \n\n",values(c),(length(year(rank<=values(c)))) / length(year) * 100);
    else
        fprintf("Percentage of years in top %0.0f = %0.2f \n\n",values(c),(length(year(rank<=values(c)))) / length(year) * 100);
    end
end
% 1b
wins = [8,11,12,9,9,8,10,10,10,10,9,9,9,9,8,9,9,10,11,11,10,14,14,12,15,14,10,10,11,9];
rankedyear = year(rank~=50);
index = 1;
for c = 1:length(year)
    if year(c) == rankedyear(index)
        rankedrank(index) = rank(c);
        index = index + 1;
    end
end
averagerank = mean(rankedrank);
averagewins = mean(wins);
index = 1;
for c = 1:length(rankedyear)
    if rankedrank(c) <= 10 && wins(c) < 10
        top10less10(index) = rankedyear(c);
        index = index + 1;
    end
end
index = 1;
for c = 1:length(rankedyear)
    if rankedrank(c) > 10 && wins(c) >= 10
        top10more10(index) = rankedyear(c);
        index = index + 1;
    end
end

%2a

t_1 = -10 : 0.01 : 10;
x_1 = (2.^(t_1+1)).*((t_1>=-4)&(t_1<-1)) + ((t_1>=-1)&(t_1<1)) + (2.^(1-t_1)).*((t_1>=1)&(t_1<4));

t_2 = t_1 + 1;
x_2 = -3 * x_1;

figure();
plot([-10,10],[0,0],'LineStyle','-','Color',[0,0,0],'LineWidth',1);
hold on;
p1 = plot(t_1,x_1,'LineStyle','-','Color',[0,0,0.8],'LineWidth',2);
p2 = plot(t_2,x_2,'LineStyle','--','Color',[0,0.8,0],'LineWidth',2);
hold off;
axis([-6,6,-4,4]);
title('Plot 2a: Amplitude Scaling and Time Shifting');
xlabel('t');
ylabel('x(t)');
legend([p1,p2],'x(t)','-3x(t-1)',...
'Location','northeast');

% 2b
x_2 = x_1.^2;
t_2 = t_1;

figure();
plot([-10,10],[0,0],'LineStyle','-','Color',[0,0,0],'LineWidth',1);
hold on;
p1 = plot(t_1,x_1,'LineStyle','-','Color',[0,0,0.8],'LineWidth',2);
p2 = plot(t_2,x_2,'LineStyle','--','Color',[0,0.8,0],'LineWidth',2);
hold off;
axis([-6,6,-4,4]);
title('Plot 2b: Squaring');
xlabel('t');
ylabel('x(t)');
legend([p1,p2],'x(t)','x(t)^2',...
'Location','northeast');

% 2c
even = 0.5*(x_1 + x_1(end:-1:1));
odd  = 0.5*(x_1 - x_1(end:-1:1));
t_2 = t_1 + 1;

figure();
plot([-10,10],[0,0],'LineStyle','-','Color',[0,0,0],'LineWidth',1);
hold on;
p1 = plot(t_2,even,'LineStyle','-','Color',[0,0,0.8],'LineWidth',2);
hold off;
axis([-6,6,-2,2]);
title('Plot 3c.1: Even');
xlabel('t');
ylabel('x(t)');
legend(p1,'Ev{x(t-1)}',...
'Location','northeast');

figure();
plot([-10,10],[0,0],'LineStyle','-','Color',[0,0,0],'LineWidth',1);
hold on;
p1 = plot(t_2,odd,'LineStyle','-','Color',[0,0,0.8],'LineWidth',2);
hold off;
axis([-6,6,-2,2]);
title('Plot 3c.2: Odd');
xlabel('t');
ylabel('x(t)');
legend(p1,'Od{x(t-1)}',...
'Location','northeast');

%3a

y = diff(x_1) / (0.01);
t_2 = t_1(2:end);

figure();
plot([-10,10],[0,0],'LineStyle','-','Color',[0,0,0],'LineWidth',1);
hold on;
p1 = plot(t_2,y,'LineStyle','-','Color',[0,0,0.8],'LineWidth',2);
hold off;
axis([-4,4,-2,2]);
title('Plot 3a: Derivative Signal');
xlabel('t');
ylabel('x(t)');
legend(p1,'y(t) = d/dt (x(t))',...
'Location','northeast');

%3b

z = cumsum(x_1)*0.01;
t_2 = t_1;

figure();
plot([-10,10],[0,0],'LineStyle','-','Color',[0,0,0],'LineWidth',1);
hold on;
p1 = plot(t_2,z,'LineStyle','-','Color',[0,0,0.8],'LineWidth',2);
hold off;
axis([-4,4,-1,5]);
title('Plot 3a: Integral Signal');
xlabel('t');
ylabel('x(t)');
legend(p1,'z(t) = integral (x(t))',...
'Location','northeast');
