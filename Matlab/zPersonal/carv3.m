
clc
clear
fprintf('  ______      \n')%('      ______  ')
fprintf(' /|_||_\\''.__ \n')%(' __.''/_||_|\\ ')
fprintf('(   _    _ _\\\n')%('/_ _    _   )')
fprintf('=''-(_)--(_)-''\n')%('''-(_)--(_)-''=')
x=0;
y=0;
d=1;
k=0;
value=0;
figure('color','w','name','Car Game','Position',[500,300,300,100])
text(-.05,.5,0,'Press arrows to move, backspace to quit.')
axis off
while value~=8
    k = waitforbuttonpress;
    value=double(get(gcf,'CurrentCharacter'));
    if value==29&&x<=25
        d=1;
        x=x+1;
    elseif value==28&&x>=0
        d=-1;
        x=x-1;
    elseif value==31&&d==-1&&y<5
        y=y+1;
    elseif value==30&&d==-1&&y>0
        y=y-1;
    elseif value==31&&d==1&&y<5
        y=y+1;
    elseif value==30&&d==1&&y>0
        y=y-1;
    end
    clc
    for c=1:y
        fprintf('\n')
    end
    if d==-1
        for c=1:x
            fprintf('\t')
        end
        fprintf('     ______\n')
        for c=1:x
            fprintf('\t')
        end
        fprintf(' __.''/_||_|\\ \n')
        for c=1:x
            fprintf('\t')
        end
        fprintf('/_ _    _   )\n')
        for c=1:x
            fprintf('\t')   
        end
        fprintf('''-(_)--(_)-''=\n')
    else
        for c=1:x
            fprintf('\t')
        end
        fprintf('  ______      \n')
        for c=1:x
            fprintf('\t')
        end
        fprintf(' /|_||_\\''.__ \n')
        for c=1:x
            fprintf('\t')
        end
        fprintf('(   _    _ _\\\n')
        for c=1:x
            fprintf('\t')   
        end
        fprintf('=''-(_)--(_)-''\n')
    end
end
close all
%cameron joseph myers
