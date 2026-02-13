clc
clear
c=0;
while c==0
y='';
y=input('loop how many times?(25 recommended)','s');
if isnan(str2double(y))
    fprintf('try again\n')
else
    clc
    c=1;
    y=str2double(y);
end
end

for x=1:y                                         
    for c=1:x
        fprintf('\t')
    end
    fprintf('  ______\n')
    for c=1:x
        fprintf('\t')
    end
    fprintf(' /|_||_\\`.__\n')
    for c=1:x
        fprintf('\t')
    end
    fprintf('(   _    _ _\\\n')
    for c=1:x
        fprintf('\t')   
    end
    fprintf('=`-(_)--(_)-''\n')
    for n=1:(y*5)
        fprintf('-')
    end
    pause(.1)
    clc
end






