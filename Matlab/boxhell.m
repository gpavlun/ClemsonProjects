clc;clear;
v=0;
for f=1:15
    y=10;
    x=10+50*v;
    for c=1:10
        dialog('Position',[x,y,150,150])
        y=y+50;
        x=x+50;
    end
    v=v+1;
end

%% randmoe

for c=1:250
    x=100*randi([0,12]);
    y=100*randi([0,5]);
    z=50*randi([0,5]);
    v=50*randi([0,5]);
    dialog('Position',[x,y,z,v])
end
