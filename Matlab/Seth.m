clc
clear
close all

load('S24Arrays.mat');
[Ch, tf] = listdlg('PromptString','please pick something','ListString',PError(:,1),'SelectionMode','single');





diff = 1;
x=1;
while diff >= PError{Ch,2}
    xnew = x-((x^3+3)/(3*x^2));
    diff = 100*abs((xnew-x)/x);
    x = xnew
end
%% 2
clc
m=[1 2 3;1 2 3;1 2 3];
mean(m')