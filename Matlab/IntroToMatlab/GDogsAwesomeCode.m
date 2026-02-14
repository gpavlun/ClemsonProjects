%Gregory Pavlunenko ENGR1410 2/29/2024
%this pile of junk is designed to measure the temperature and light level of a green house. It will turn on a warning light if the temp is bad and print out all of the data in the command line and an excel file 
clc
clear
%% variablelist
name='GH_Environment Log.xlsx';
day=0.1;%voltage where night switches to day
dtmax=30;%max day temp degC
dtmin=18;%min day temp degC
ntmax=24;%max nigt temp degC
ntmin=14;%min nigt temp degC
WarnLight=0;%you know what this is
%Light - used to measure light sensor voltage
%Temp - Temp sensor voltage converted to deg C
%Attached - wether or not arduino is attached
%% arduino test
Attached=questdlg('Is an Arduino attached?','Attached?','Yes','No','No');%dlg box
if 1==isempty(Attached)%user hit x
    error('Selection not made!')
elseif 1==strcmp(Attached,'Yes')%user hit yes
        a=arduino();
        TempVolt=readVoltage(a,'A0');%reads arduino and pulls data from there
        Light=readVoltage(a,'A1');
        Temp=(TempVolt-0.5)*100;
        WarnLight=0;
        time='NA';
            if Light>day%following code checks conditions from arduino
                if ~(Temp>=dtmin&&Temp<=dtmax)
                    warning('temp out of range')
                    WarnLight=1;
                end
            elseif Light<=day
                   if ~(Temp>=ntmin&&Temp<=ntmax)
                      warning('temp out of range')
                      WarnLight=1;
                   end
            end
            writeDigitalPin(a,'D2',WarnLight)
elseif 1==strcmp(Attached,'No')%user hit no in dlg
       TempVolt=TempSim;%pulls data from sim function
       Light=LightSim;
       Temp=(TempVolt-.5)*100;
       if Light>day%checks for condtionals
            if ~(Temp>=dtmin&&Temp<=dtmax)
               %warning('temp out of range')
               WarnLight=1;
            end
      elseif Light<=day
             if ~(Temp>=ntmin&&Temp<=ntmax)
                %warning('temp out of range')
                WarnLight=1;
             end
       end
end

if Light>day%name changes for output
    NNN='daytime';
else
    NNN='nighttime';
end
if 0==WarnLight
    SSS='in range';
else
    SSS='out of range';
end
fprintf('Light Voltage: %0.2f V (%s)\nTemperature: %0.1f C\nThese conditions are %s.',Light,NNN,Temp,SSS)%output

Date_Time=datetime('now');
Temp_DegC=Temp;
Illum_V=Light;

T=table(Date_Time,Temp_DegC,Illum_V,WarnLight);
writetable(T,name,'Sheet','Log','writemode','append');%adds new line to exel file with data
%% given functions
function [T_fn]=TempSim()
global Attached_ref
global T_ref
global TESTFLAG_T
  
if isempty(T_ref) || strcmpi(Attached_ref,'yes')
    T_fn=rand*0.25+0.6;
else
    T_fn=T_ref;
    TESTFLAG_T=1; % TESTFLAG_T is used to verify that the code does not
    % contain clear, which would delete the T_ref provided in the test
end
end
function [L_fn]=LightSim()
global Attached_ref
global L_ref
global TESTFLAG_L
  
if isempty(L_ref) || strcmpi(Attached_ref,'yes')
    L_fn=rand*0.1+randi([0 1])*rand*5;
else
    L_fn=L_ref;
    TESTFLAG_L=1; % TESTFLAG_L is used to verify that the code does not
    % contain clear, which would delete the L_ref provided in the test
end
end