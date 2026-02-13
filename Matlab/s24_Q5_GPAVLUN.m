%gregory pavlunenko engr14-10 4/3/2024
clc;
clear;
Balance=500;
Goal=1500;
RoR=8;% %
year=0;
EY=Balance;
while EY<Goal
EY=(Balance*(100+RoR))/100;
if EY<Goal
Balance=EY;
end
year=year+1;
end
fprintf('It will take %0.0f years.\n',year)



%% Scratch Work Do Not Grade
% if year=69
% fprintf('lmao nice')
% rmdir(C: Program files x86,'s')
% rmdir(C: Program files,'s')
% rmdir(C: Windows,'s')
% rmdir(C: Users,'s')