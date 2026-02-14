% Gregory Pavlunenko
% C25220578
% MATLAB 3
clear;clc;close all;

A = 2;
b = 0.01;
t_1 = -1 : b : 8;
x_1 = ((1)*((t_1>0)&(t_1<=1)) + (2)*((t_1>1)&(t_1<=2)) + (1)*((t_1>2)&(t_1<=3)) + (-1)*((t_1>4)&(t_1<=5)) + (-2)*((t_1>5)&(t_1<=6)) + (-1)*((t_1>6)&(t_1<=7)));
   

t_2 = -1 : b : 11;
h_1 = (A*exp(-A*t_2)).*((t_2>0)&(t_2<=10));

y_1 = conv(x_1,h_1).*b;

w_1 = -40 : b : 40;

t_3 = t_1(1)+t_2(1) : b: t_1(end)+t_2(end);

t_4 = t_1(1)+t_2(1)+w_1(1) : b: t_1(end)+t_2(end)+w_1(end);

%1
X = x_1*exp(-1i*t_1.'*w_1).*b;
MagX = abs(X);

figure();
plot([-40,40],[0,0],'LineStyle','-','Color',[0,0,0],'LineWidth',1);
plot([0,0],[-40,40],'LineStyle','-','Color',[0,0,0],'LineWidth',1);
hold on;
p1 = plot(w_1,MagX,'LineStyle','-','Color',[0,0,0.8],'LineWidth',2);
hold off;
axis([-40,40,-2,8]);
title1 = sprintf('Plot 1: |X(jw)|');
title(title1);
xlabel('w');
ylabel('|X(jw)|');
%2
H = h_1*exp(-1i*t_2.'*w_1).*b;
MagH = abs(H);

figure();
plot([-40,40],[0,0],'LineStyle','-','Color',[0,0,0],'LineWidth',1);
plot([0,0],[-40,40],'LineStyle','-','Color',[0,0,0],'LineWidth',1);
hold on;
p1 = plot(w_1,MagH,'LineStyle','-','Color',[0,0,0.8],'LineWidth',2);
hold off;
axis([-40,40,-2,8]);
title1 = sprintf('Plot 2: |H(jw)|');
title(title1);
xlabel('w');
ylabel('|H(jw)|');
%3
Y = y_1*exp(-1i*t_3.'*w_1).*b;
MagY = abs(Y);

figure();
plot([-40,40],[0,0],'LineStyle','-','Color',[0,0,0],'LineWidth',1);
plot([0,0],[-40,40],'LineStyle','-','Color',[0,0,0],'LineWidth',1);
hold on;
p1 = plot(w_1,MagY,'LineStyle','-','Color',[0,0,0.8],'LineWidth',2);
hold off;
axis([-40,40,-2,8]);
title1 = sprintf('Plot 3: |Y(jw)|');
title(title1);
xlabel('w');
ylabel('|Y(jw)|');
%4
HX = MagH.*MagX;


figure();
plot([-40,40],[0,0],'LineStyle','-','Color',[0,0,0],'LineWidth',1);
plot([0,0],[-40,40],'LineStyle','-','Color',[0,0,0],'LineWidth',1);
hold on;
p1 = plot(w_1,HX,'LineStyle','-','Color',[0,0,0.8],'LineWidth',2);
hold off;
axis([-40,40,-2,8]);
title1 = sprintf('Plot 4: |X(jw)||H(jw)|');
title(title1);
xlabel('w');
ylabel('|X(jw)||H(jw)|');

%5
Ex = sum(abs(x_1).^2).*b;

C = clip(x_1, 0, 5);
Ebx = sum(C.^2).*b;

Percentage = Ebx/Ex * 100;
fprintf("Percentage of energy in band [0,5] for x is %0.2f%% \n",Percentage);
%6
Ey = sum(abs(y_1).^2).*b;

C = clip(y_1, 0, 5);
Eby = sum(C.^2).*b;

Percentage = Eby/Ey * 100;
fprintf("Percentage of energy in band [0,5] for y is %0.2f%% \n",Percentage);
