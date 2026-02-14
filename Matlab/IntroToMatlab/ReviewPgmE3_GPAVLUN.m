%gregory pavlunenko engr1410 4/12/2024
clc;clear;close all;
%% data entry
load R3Data.mat
%% cooling temperature
again='yes';
while strcmpi(again,'yes')
Choice='';
while isempty(Choice)
Choice=listdlg('PromptString','selecta fluid','SelectionMode','single','ListString',Data(1,1:end));
if isempty(Choice)
    warning('make a choice')
end
end
c=0;
while c==0
    t0=input('input initial temp\n');
    ta=input('input ambient temp\n');
    if ta<=t0&&ta<=35&&ta>=5
        c=1;
    elseif ~(ta<=35&&ta>=5)
        warning('ambient outside of viable range 5-35')
    end
end
k=Data(2,Choice);
T=ta+(t0-ta)*exp(-time*k{1,1});
fprintf('%s has temp %0.1f deg C after 5.0 seconds.\n',Data{1,Choice},T)
again=questdlg('Calculate for another fluid?','go again','yes','no','no');
end
%% magic square
[r,c]=size(M);
n=1;
for z1=1:1:c
    if sum(M(z1,:))==sum(M(1,:))
        rows(1,z1)=1;
    else
        rows(1,z1)=0;
        warning('not magical')
    end
end
for z2=1:1:r
    if sum(M(:,z2))==sum(M(:,1))&&sum(M(:,z2))==sum(M(1,:))
        cols(1,z2)=1;
    else
        cols(1,z2)=0;
        warning('not magical')
    end
end
[CAOut]=ReviewFnE3_GPAVLUN(CAIn);
%% funct

        







