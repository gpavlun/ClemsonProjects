%% turn based combat sim
clc
clear
c=0;
EH=100;
PH=100;
fprintf('You are walking through the woods\n       ^  ^  ^   ^      ___I_      ^  ^   ^  ^  ^   ^  ^\n      /|\\/|\\/|\\ /|\\    /\\-_--\\    /|\\/|\\ /|\\/|\\/|\\ /|\\/|\n      /|\\/|\\/|\\ /|\\   /  \\_-__\\   /|\\/|\\ /|\\/|\\/|\\ /|\\/|\\\n      /|\\/|\\/|\\ /|\\   |[]| [] |   /|\\/|\\ /|\\/|\\/|\\ /|\\/|\\\n')
while c==0
    cont='';
    cont=input('continue?(y/n)','s');
    if ~(strcmpi(cont,'y')||strcmpi(cont,'n'))
        c=0;
    else
        c=1;
    end
end
if strcmpi(cont,'n')
    error('player is a wuss')
end
pause(1)
clc
fprintf('AN ENEMY HAS APPEARED!!!\n')
fprintf('ENEMY HEALTH = %0.0f\t\tYOUR HEALTH = %0.0f\n',EH,PH)
fprintf('                 ___\n                |o o|\n              ___\\ /___\n              |       |\n              ||\\   /||\n              || \\ / ||\n       <=====]()0/ \\ ()\n                |/ \\|\n                || ||\n               _|| ||_\n')
pause(.5)
while EH>0&&PH>0
fprintf('ENEMY USED ''ATTACK''')
EA=randi([1,10]);
PH=PH-EA;
pause(1)
clc
fprintf('AN ENEMY HAS APPEARED!!!\n')
fprintf('ENEMY HEALTH = %0.0f\t\tYOUR HEALTH = %0.0f\n',EH,PH)
fprintf('                 ___\n                |o o|\n              ___\\ /___\n              |       |\n              ||\\   /||\n              || \\ / ||\n       <=====]()0/ \\ ()\n                |/ \\|\n                || ||\n               _|| ||_\n')
c=0;
while c==0
    cont='';
    cont=input('what do you want to do?\nATTACK(1)      FLEE(2)','s');
    if isnan(str2double(cont))
        c=0;
    else
        cont=str2double(cont);
        if ~(cont==1||cont==2)
            c=0;
        else
            c=1;
        end
    end
end
if cont==2
    error('player is a wuss')
end
clc
fprintf('AN ENEMY HAS APPEARED!!!\n')
fprintf('ENEMY HEALTH = %0.0f\t\tYOUR HEALTH = %0.0f\n',EH,PH)
fprintf('                 ___\n                |o o|\n              ___\\ /___\n              |       |\n              ||\\   /||\n              || \\ / ||\n       <=====]()0/ \\ ()\n                |/ \\|\n                || ||\n               _|| ||_\n')
fprintf('You used ATTACK')
PD=randi([5,15]);
EH=EH-PD;
pause(1)
clc
fprintf('AN ENEMY HAS APPEARED!!!\n')
fprintf('ENEMY HEALTH = %0.0f\t\tYOUR HEALTH = %0.0f\n',EH,PH)
fprintf('                 ___\n                |o o|\n              ___\\ /___\n              |       |\n              ||\\   /||\n              || \\ / ||\n       <=====]()0/ \\ ()\n                |/ \\|\n                || ||\n               _|| ||_\n')
pause(1)
end
clc
if PH>0
    fprintf('You Won!')
else
    fprintf('You died:(')
end
    

