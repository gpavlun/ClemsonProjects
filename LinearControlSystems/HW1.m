clc
clear

a = -2;
w = 12;


xlim = 3;
step = 0.01;
range = xlim/step + 1;

t = 0:step:xlim;

V1(1:range) = 1;
V2(1:range) = 0;
for c=1:range
    V2(c) = 1 - exp(a*t(c))*cos(w*t(c));
end
V3(1:range) = 0;
for c=1:range
    V3(c) = 1 - exp(a*t(c));
end
V4(1:range) = 0;
for c=1:range
    V4(c) = 1 + exp(a*t(c));
end

figure();
%plot([0,3],[0,0],'LineStyle','-','Color',[0,0,0],'LineWidth',1);

hold on;
p1 = plot(t,V1,'LineStyle','-','Color','k','LineWidth',2);
p2 = plot(t,V2,'LineStyle','-','Color','r','LineWidth',2);
p3 = plot(t,V3,'LineStyle','--','Color','b','LineWidth',2);
p4 = plot(t,V4,'LineStyle','--','Color','b','LineWidth',2);


hold off;

axis([0,3,0,2]);
title('HW 1');
xlabel('Time (s)');
ylabel('Output (V)');
legend([p1,p2],'reference','output',...
'Location','northeast');
