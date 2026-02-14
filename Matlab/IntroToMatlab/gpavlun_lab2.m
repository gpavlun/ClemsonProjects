% Gregory Pavlunenko ENGR 1410-222
%The point of this is to create a program that will take a code and then
%compare it to a user input to lock or unlock a safe. Pretty cool.
%% VARIABLE LIST
%Range - max integer value
%Status - Status of lock on safe
%Volt_Max - maximum voltage of the dial
%attempt - number of times closing dialog box
%Attached - Wether or not arduino is attached
%Combo - correct combination
%User - User input combination
%r & c - size of the combination
%Button - wether or not button is pressed
%Dial - voltage of the dial
%n - index of user
%Incorrect - Vector of incorrect values
%IncInd - Incorrect index
%t# - all for loops defined this way
%% code
clc;clear;
%% Variables
%Range=60;
Status='Locked';
Volt_Max=4.5;
%% Attached
Attached='';
attempt=0; %counting the attempts
while (~((strcmpi(Attached,'yes'))||(strcmpi(Attached,'no'))))&&attempt<3
    Attached=questdlg('Is an Arduino attached?','Attached?','Yes','No','No');
    if isempty(Attached)
        attempt=attempt+1;        
    end
end
if attempt==3&&isempty(Attached)
    error("Selection not made!")
end
%% Arduino
if strcmpi(Attached,'Yes')
    a=arduino();
end
%% Safe Rules
fprintf('Safe Rules\n\tCombination length: 4 - 6 numbers\n\tRange: 1 - %0.0f\n\n',Range)
Combo=input('Enter a combination as a single row vector');
[r,c]=size(Combo);% c will be used a lot from now on
if (r>1||r<1)||(c>6||c<4)%sorting various input errors
    error('Incorrect combination dimensions!')
else
    for t1=1:1:c
        if Combo(1,t1)>Range||Combo(1,t1)<1||floor(Combo(1,t1))~=Combo(1,t1)
            error('Combination value outside of range or not an integer!')
        end
    end
end
Status='Locked';
%% Unlocking
while strcmpi(Status,'Locked')
n=1;
for t2=1:1:c
    Button=0;
    while Button==0%detects if button is pushed
        if strcmpi(Attached,'yes')
            Button=readDigitalPin(a,'D2');
        else
            Button=ButtonSim;
        end
        if Button==1
              if strcmpi(Attached,'yes')%assigns value from voltage
                  Dial=readVoltage(a,'A0');
              else
                  Dial=DialSim;
              end
             User(1,n)=floor((Range*Dial)/Volt_Max)+1;%converts voltage to usable value
             n=n+1;
             pause(.25)
       end
    end
end
IncInd=1;
Incorrect='';
for t3=1:1:c
    if User(1,t3)~=Combo(1,t3)%compares codes
        Incorrect(1,IncInd)=t3;
        IncInd=IncInd+1;
    end
end
if isempty(Incorrect)%unlock successful
    Status='Unlocked';
    if strcmpi(Attached,'Yes')
        writeDigitalPin(a,'D3',1)
    end
else
    warning('Incorrect combination. %0.0f value(s) are incorrect.',length(Incorrect))
end
end
Status
Incorrect
% Final Comments: I wrote my original submission for this at like 11pm and
% I didn't read the instructions very well so I had a ton of extra stuff
% that was not ideal. Since I realized that the original code was beyond
% saving, I rewrote the entire thing in like 30 minutes after reading the
% directions for real and it worked first try in the matlab grader. I am
% very proud of this code because it is by far the prettiest thing I've
% ever written.



