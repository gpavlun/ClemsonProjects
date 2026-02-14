%% Variables to be used
% Inputs
% Range - upper value of numbers on the dial

% Intermediate Variables
% Button - variable that stores button state 0 (unpressed) or 1 (pressed)
% Dial - variable that stores voltage from potentiometer 

% Outputs
% Status - status of safe after combination has been entered - either Locked or Unlocked
% Incorrect - vector containing index values of any incorrectly entered combination values

%% Inputs
% Test Case 1
Range = 10;
%Combo = [1,5,8,10] % Original combination
%Voltage: 0, 2.3, 3.1, 4.4 % to be entered one at a time 
% Entered vector should contain [1,6,7,10] 
% Test case output:
%Warning: Incorrect combination. 2 value(s) are incorrect. 
%Voltage: 0, 1.5, 3.5, 4.4  % to be entered one at a time
% Entered vector should contain [1,4,8,10]
% Test case output:
%Warning: Incorrect combination. 1 value(s) are incorrect.
%Voltage: 0, 1.9, 3.5, 4.4 % to be entered one at a time
% Entered vector should contain [1,5,8,10]
% Test case output:
%Status='Unlocked'


%% Program
% Start writing your program here

clc;clear;close all;
Attached='';
atp=0;
Range=60;
Status='locked';
Volt_Max=4.5;
while isempty(Attached)&&atp<=2
Attached=questdlg('Is an Arduino Attached?','Attached?','Yes','No','No');
atp=atp+1;
end
if isempty(Attached)
    error("Selection not made!")
end
fprintf('Safe Rules\n\tCombination length: 4 - 6 numbers\n\tRange: 1 - %0.0f\n\n',Range)
x1=input('enter the combination as a single row vector\n');
[r,c]=size(x1);
if r>1||(c~=4&&c~=5&&c~=6)
    error('Incorrect combination dimensions!')
end
for l5=1:c
    if x1(1,l5)>Range||x1(1,l5)<1||round(x1(1,l5))~=x1(1,l5)
        error('Combination value outside of range or not an integer!')
    end
end

Status='Locked';

if strcmpi(Attached,'yes')
    a=arduino();
   
    while strcmpi(Status,'Locked')
        for l22=1:length(x1)
            co=0;
            while co==0
                co=0;
            Button=readDigitalPin(a,'D2');
            if Button==1
                Dial=Readvoltage(a,'A0');
                combo(1,l22)=floor(((Dial*Range)/4.5))+1;
                pause(.25)
                co=1;
            end
            end
        end
        Incorrect=0;
        for l20=1:length(combo)
            if x1(1,l20)~=combo(1,l20)
                Incorrect(1,l20)=1;
            end
        end
        if Incorrect==0
            Incorrect='';
            Status='Unlocked';
        else
            warning('Incorrect combination. %0.0f value(s) are incorrect.',length(Incorrect))
        end
    end
   
elseif strcmpi(Attachted,'no')
    % simulation shit
    
    while strcmpi(Status,'Locked')
        for l22=1:length(x1)
            co=0;
            while co==0
                co=0;
            Button=ButtonSim;
            if Button==1
                Dial=DialSim;
                combo(1,l22)=floor(((Dial*Range)/4.5))+1;
                pause(.25)
                co=1;
            end
            end
        end
        Incorrect=0;
        for l20=1:length(combo)
            if x1(1,l20)~=combo(1,l20)
            Incorrect(1,l20)=1;
            end
        end
        if Incorrect==0
            Incorrect='';
            Status='Unlocked';
        else
            warning('Incorrect combination. %0.0f value(s) are incorrect.',length(Incorrect))
        end
    end
end
if strcmpi(Attached,'yes')
if strcmpi(Status,'Unlocked')
    writeDigitalPin(a,'D3',1)
else
    writeDigitalPin(a,'D3',0)
end
end