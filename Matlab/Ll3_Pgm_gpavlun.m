%Gregory Pavlunenko ENGR1410
%The point of this lab is to create a script and function that will plot
%experimental data
%VariableList
%atp=attempts
%BushDid911=looping variable
%Data=Data
%Information=Information
%k=intermediary
%n=listselection
%t#=loop
clc;clear;close all;
Information=readtable("Cooling Data.xlsx","sheet","Information");%data reading
Data=readmatrix("Cooling Data.xlsx","sheet","Data");
BushDid911=0;
atp=1;
while BushDid911==0
if atp==1
Plot='';
atp=2;
while isempty(Plot)
Plot=questdlg('What type of plot do you want to create?','Plot','Summary','Detail','Detail');%dialog  for atp#1
if isempty(Plot)
warning('valid selection not made!')
end
end
else
Plot='';
while isempty(Plot)
Plot=questdlg('What type of plot do you want to create?','Plot','Summary','Detail','Stop','Stop');%dialog for atp#1+n
if strcmpi(Plot,'Stop')
BushDid911=2;
end
end
end
if strcmpi(Plot,"summary")%summary plots
L3_Fn_gpavlun(Data,table2array(Information))
title('Summary Plot')
legend(Information{:,1});
elseif strcmpi(Plot,"detail") %detail plots
n=listdlg('PromptString','Pick a Material','ListString',table2array(Information(:,1)),'SelectionMode','single');
if isempty(n)
error('zoinks scoob!')%error if selecting nothing
end
L3_Fn_gpavlun(Data(n*2-1:n*2,:),table2array(Information(n,:)))
title(Information{n,1})
k=Information{n,2};%pOlYfIt
style=k{1};
C=polyfit(Data(n*2-1,2:end),log(Data(n*2,2:end)),1);
m=C(1);
b=exp(C(2));
tpf=0:10;
Vpf=b*exp(m*tpf);
hold on; 
plot(tpf,Vpf,'color',style(1));
z=Data(n*2,5);
X=sprintf('%0.2fe^{%0.2ft}',b,m);%plot trendline
text(1.5,z+10,X,'color',style(1),'fontsize',9,'edgecolor',style(1),'linestyle',':','linewidth',1.5,'BackgroundColor','w');
hold off;
end
end
