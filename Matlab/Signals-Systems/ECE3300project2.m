% Gregory Pavlunenko
% C25220578
% MATLAB 2
clear;clc;close all;

% in order for this to graph from -1 to 17, you cannot represent all of the
% pulses at a length of time T where T is equal to 2. In order to correct
% this, I have doubled to length that the signal is generated to account
% for the necessary additional time.

% an email was sent out confirming my correction, thanks

%1.0

datasignal = [0,1,0,1,1,1,1,0,0,0,1,1,1,0,0,1];

a = -1;
b = length(datasignal) + 1;
b = b*2-1;

ii = 0.01;
t = a : ii : b;

A = 2;
T = 2;

% 1.1

xNRZ = 0;
for c = 1:length(datasignal)
    if(datasignal(c))==0
        xNRZ = xNRZ + T.*((t>(A*(c-1))) & (t<=((A*(c-1))+2)) );
    else 
        xNRZ = xNRZ + -T.*((t>(A*(c-1))) & (t<=((A*(c-1))+2)) );
    end
end

figure();
plot([a,b],[0,0],'LineStyle','-','Color',[0,0,0],'LineWidth',1);
hold on;
p1 = plot(t,xNRZ,'LineStyle','-','Color',[0,0,0.8],'LineWidth',2);
hold off;
axis([a,b,-3,3]);
title('Plot 1.1: NRZ signal');
xlabel('t');
ylabel('y(t)');
legend(p1,'y(t)',...
'Location','northeast');

%1.2

xRZ = 0;
for c = 1:length(datasignal)
    if(datasignal(c))==0
        xRZ = xRZ + T.*( (t>((A)*(c-1))) & (t<=(((A)*(c-1))+1)) );
    else 
        xRZ = xRZ + -T.*( (t>((A)*(c-1))) & (t<=(((A)*(c-1))+1)) );
    end
end

figure();
plot([a,b],[0,0],'LineStyle','-','Color',[0,0,0],'LineWidth',1);
hold on;
p1 = plot(t,xRZ,'LineStyle','-','Color',[0,0,0.8],'LineWidth',2);
hold off;
axis([a,b,-3,3]);
title('Plot 1.2: RZ signal');
xlabel('t');
ylabel('v(t)');
legend(p1,'v(t)',...
'Location','northeast');

%1.3

xBP = 0;
for c = 1:length(datasignal)
    if(datasignal(c))==0
        xBP = xBP + T.*( (t>(A*(c-1))) & (t<=((A*(c-1))+1)) )... 
        + -T.*( (t>(A*(c-1))+1) & (t<=((A*(c-1))+2)) );      
    else 
        xBP = xBP + -T.*( (t>(A*(c-1))) & (t<=((A*(c-1))+1)) )...
        + T.*( (t>(A*(c-1))+1) & (t<=((A*(c-1))+2)) );
    end
end

figure();
plot([a,b],[0,0],'LineStyle','-','Color',[0,0,0],'LineWidth',1);
hold on;
p1 = plot(t,xBP,'LineStyle','-','Color',[0,0,0.8],'LineWidth',2);
hold off;
axis([a,b,-3,3]);
title('Plot 1.3: bi-phase signal');
xlabel('t');
ylabel('w(t)');
legend(p1,'w(t)',...
'Location','northeast');

%2.4

Ey = sum(abs(xNRZ).^2).*ii;
fprintf("Energy of y(t) = %0.0f\n",Ey);

Ev = sum(abs(xRZ).^2).*ii;
fprintf("Energy of v(t) = %0.0f\n",Ev);

Ew = sum(abs(xBP).^2).*ii;
fprintf("Energy of w(t) = %0.0f\n",Ew);

fprintf("description:\n\t The y(t) signal and the w(t) signal have the\n" ...
    + "same energy since they neither of them have to return to zero\n"...
    + "for each rise and fall. w(t) may have double the pulses, but each\n"...
    + "pulse is half as powerful. v(t) on the other hand is half the\n"...
    + "energy of them both due to its pulses being half the length for a\n"...
    + "return to zero\n\n")

%2.5

Ryv = sum(xNRZ.*conj(xRZ)).*ii;
Pyv = mean(corrcoef(xNRZ,xRZ),"all");
fprintf("Correlation of y(t), v(t) = %0.0f\n",Ryv);
fprintf("Correlation Coefficient = %0.3f\n",Pyv);

Ryw = sum(xNRZ.*conj(xBP)).*ii;
Pyw = mean(corrcoef(xNRZ,xBP),"all");
fprintf("Correlation of y(t), w(t) = %0.0f\n",Ryw);
fprintf("Correlation Coefficient = %0.3f\n",Pyw);

Rvw = sum(xRZ.*conj(xBP)).*ii;
Pvw = mean(corrcoef(xRZ,xBP),"all");
fprintf("Correlation of v(t), w(t) = %0.0f\n",Rvw);
fprintf("Correlation Coefficient = %0.3f\n",Pvw);


fprintf("description:\n\t y(t) and v(t) are similar to each other due to\n"...
    + "Their similar energy levels. They line up with each other half of\n"...
    + "of the time, so they are pretty similar. The rising edges and\n"...
    + "falling edges line up very well in this regard. y(t) and w(t)\n"...
    + "have almost no matching rising or falling edges, which leads to\n"...
    + "two very different and uncorrelated graphs, despite having the\n"...
    + "same energy. Visually from the graphs you can see tha v(t) lines\n"...
    + "up with w(t) much more frequently, which happens when half of the\n"...
    + "when the digit is a 0.\n\n");

%2.6

MSEyv = sum(abs(xNRZ-xRZ).^2).*ii;
MSEyw = sum(abs(xNRZ-xBP).^2).*ii;
MSEvw = sum(abs(xRZ-xBP).^2).*ii;

fprintf("MSE between y and v = %0.0f\n",MSEyv);
fprintf("MSE between y and w = %0.0f\n",MSEyw);
fprintf("MSE between v and w = %0.0f\n",MSEvw);
fprintf("description:\n\t The MSE is giving essentially the same result\n"...
    + "as the correlation, with the large MSE numbers meaning more\n"...
    + "difference. The explaination for that was given above, but the\n"...
    + "value in this regard is trying to approach 0 whereas the\n"...
    + "correlation coefficient is approaching 1\n\n");
