% Gregory Pavlunenko
% C25220578
% MATLAB 5
clear;clc;close all;

a = 3;
b = 4.204;
n = 400;
w = logspace(a,b,n);

K = -20;
A = -4;
B = 3;
C = 2;
D = 3;

h = (K*(w).^A).*((1000+w).^B).*((4000+w).^C).*((16000+w).^D);

fprintf("the value of K is %0.0f\n",K);
fprintf("the value of A is %0.0f\n",A);
fprintf("the value of B is %0.0f\n",B);
fprintf("the value of C is %0.0f\n",C);
fprintf("the value of D is %0.0f\n",D);

hmag = 20*log10(abs(h));
hphase = unwrap(angle(h));

figure();
hold on;

p1 = semilogx(w,hmag,'LineStyle','-','color',[0,0,0.8]);

hold off;
axis([10^(a),10^b,372,390]);
title('Plot 1: Bode Plot');
xlabel('\omega');
ylabel('Magnitude of X(j\omega) in dB');
legend(p1,'v(t)','Location','northeast');

min1 = 0.2;
min2 = -0.2;
max1 = 20;
max2 = -20;

lower1 = (K*(max2).^A).*((1000+max2).^B).*((4000+max2).^C).*((16000+max2).^D);
lower2 = (K*(min2).^A).*((1000+min2).^B).*((4000+min2).^C).*((16000+min2).^D);

upper1 = (K*(min1).^A).*((1000+min1).^B).*((4000+min1).^C).*((16000+min1).^D);
upper2 = (K*(max1).^A).*((1000+max1).^B).*((4000+max1).^C).*((16000+max1).^D);

Rolloff1 = lower2/lower1;
Rolloff2 = upper2/upper1;

lower = 0.01;
upper = 100;

fprintf("upper roll-off ratio %0.2f\n",upper);
fprintf("lower roll-off ratio %0.2f\n",lower);