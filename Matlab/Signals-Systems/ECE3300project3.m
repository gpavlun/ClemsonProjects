% Gregory Pavlunenko
% C25220578
% MATLAB 3
clear;clc;close all;

title1 = "";
for c=1:4
    b = 0.01;
    t_1 = -1 : b : 8;
    x_1 = ((1)*((t_1>0)&(t_1<=1)) + (2)*((t_1>1)&(t_1<=2)) + (1)*((t_1>2)&(t_1<=3)) + (-1)*((t_1>4)&(t_1<=5)) + (-2)*((t_1>5)&(t_1<=6)) + (-1)*((t_1>6)&(t_1<=7)));
    
    if c==1
        A = 8;
    elseif c==2
        A = 4;
    elseif c==3
        A = 2;
    elseif c==4
        A = 1;
    end

    t_2 = -1 : b : 11;
    h_1 = (A*exp(-A*t_2)).*((t_2>0)&(t_2<=10));
    t_3 = t_1(1)+t_2(1) : b: t_1(end)+t_2(end);
    con = conv(x_1,h_1).*b;
    
    figure();
    plot([-10,10],[0,0],'LineStyle','-','Color',[0,0,0],'LineWidth',1);
    plot([0,0],[-10,10],'LineStyle','-','Color',[0,0,0],'LineWidth',1);
    hold on;
    p1 = plot(t_3,con,'LineStyle','-','Color',[0,0,0.8],'LineWidth',2);
    hold off;
    axis([-2,19,-3,3]);
    title1 = sprintf('Plot 1a: A = %0.0f convolution',A);
    title(title1);
    xlabel('t');
    ylabel('[x*h](t)');
 
    t_1 = -2 : b : 19;
    x_1 = ((1)*((t_1>0)&(t_1<=1)) + (2)*((t_1>1)&(t_1<=2)) + (1)*((t_1>2)&(t_1<=3)) + (-1)*((t_1>4)&(t_1<=5)) + (-2)*((t_1>5)&(t_1<=6)) + (-1)*((t_1>6)&(t_1<=7)));   
    Ex = sum(abs(x_1).^2).*b;
    MSE = sum(abs(x_1-con).^2).*b;
    Percentage = MSE/Ex * 100;

    fprintf("For A = %0.0f\n", A);
    fprintf("\t MSExy : %0.2f\n",MSE);
    fprintf("\t Energyx : %0.2f\n",Ex);
    fprintf("\t MSE Percentage : %0.2f\n\n",Percentage);
end
