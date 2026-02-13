%Gregory Pavlunenko ENGR1410 1/24/2024
clc
clear
%% data entry

g=9.8;%m/s^2
d1=4.7;%m
d2=3.2;%m
SW=790;%N/m^3
MW=.58;%kg/mol

%% calculations

Vcub=(d1)*((d2)^2);
Vin=Vcub*60963.83;
Moles=(SW*Vcub)/(MW*g);
