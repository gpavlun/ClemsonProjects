clear
clc
%Gregory Pavlunenko ENGR1410 222 2/2/24
%% variable creation
M=[6,34,15];
LABELS={'SetA','SetB','SetC'};
POW=90;%power watts
n=60;%eff
H=[150,80,120];
%% Built-In Function Review
RDM=[randi(75,[3,4])];
M(1,end-1)=8;
Z=150*exp(-M+7)
B=M;
A=RDM(:,1);
C=RDM(:,end);
P=(-B+sqrt((B.^3)+(0.5)*A.*C))./(A*B);
rowTotal=[sum(RDM(1,:));sum(RDM(2,:));sum(RDM(3,:))];
RDMAvg=mean(mean(RDM));
F=min(rowTotal);
G=find(F);
J=LABELS(1,G);
Area=((RDM(:,1).^2)*.914634);
%% weight and time
function[w,t]=ReviewFnE1_gpavlun(POW,n,H,M)
t=t
end


