%math game
clc
clear
x=0;
c=0;
c2=0;
mode=0;
while c2==0
    mode='';
    mode=input('pick mode:\ntimes tables(1)\nadd/subtract(2)\nfull(3)\n','s');
    if ~(strcmp(mode,'1')||strcmp(mode,'2')||strcmp(mode,'3'))
        c2=0;
    else
        mode=str2num(mode);
        if mode==1||mode==2||mode==3
            c2=1;
        end
    end
end
if mode==3
while x==0
    x=0;
    c=0;
    n1=randi([1,9]);
    n2=randi([1,9]);
    op=randi([1,4]);
    if op==1
        s=sprintf('\n%0.0f + %0.0f = ',n1,n2);
        while c==0
            a='';
            a=input(s,'s');
            if isnan(str2double(a))
                c=0;
            else
                c=1;
            end
        end
        a=str2double(a);
        if a~=n1+n2
            fprintf('you suck\n')
        else
            fprintf('good job!\n')
        end
    elseif op==2
        s=sprintf('\n%0.0f - %0.0f = ',n1,n2);
        while c==0
            a='';
            a=input(s,'s');
            if isnan(str2double(a))
                c=0;
            else
                c=1;
            end
        end
        a=str2double(a);
        if a~=n1-n2
            fprintf('you suck\n')
        else
            fprintf('good job!\n')
        end
    elseif op==3
        s=sprintf('\n%0.0f * %0.0f = ',n1,n2);
        while c==0
            a='';
            a=input(s,'s');
            if isnan(str2double(a))
                c=0;
            else
                c=1;
            end
        end
        a=str2double(a);
        if a~=n1*n2
            fprintf('you suck\n')
        else
            fprintf('good job!\n')
        end
    else
        s=sprintf('\n%0.0f / %0.0f = ',n1,n2);
        while c==0
            a='';
            a=input(s,'s');
            if isnan(str2double(a))
                c=0;
            else
                c=1;
            end
        end
        a=str2double(a);
        if a~=n1/n2
            fprintf('you suck\n')
        else
            fprintf('good job!\n')
        end
    end
    b='';
    while ~(strcmpi(b,'y')||strcmpi(b,'n')||strcmpi(b,'yes')||strcmpi(b,'no')||strcmpi(b,'1')||strcmpi(b,'2'))
        b='';
        b=input('go again?(y/n)','s');
        if strcmpi(b,'n')||strcmpi(b,'no')||strcmp(b,'2')
            x=1;
        else
            x=0;
        end
    end
end
elseif mode==1
        while x==0
    x=0;
    c=0;
    n1=randi([1,9]);
    n2=randi([1,9]);
    op=3;
    if op==1
        s=sprintf('\n%0.0f + %0.0f = ',n1,n2);
        while c==0
            a='';
            a=input(s,'s');
            if isnan(str2double(a))
                c=0;
            else
                c=1;
            end
        end
        a=str2double(a);
        if a~=n1+n2
            fprintf('you suck\n')
        else
            fprintf('good job!\n')
        end
    elseif op==2
        s=sprintf('\n%0.0f - %0.0f = ',n1,n2);
        while c==0
            a='';
            a=input(s,'s');
            if isnan(str2double(a))
                c=0;
            else
                c=1;
            end
        end
        a=str2double(a);
        if a~=n1-n2
            fprintf('you suck\n')
        else
            fprintf('good job!\n')
        end
    elseif op==3
        s=sprintf('\n%0.0f * %0.0f = ',n1,n2);
        while c==0
            a='';
            a=input(s,'s');
            if isnan(str2double(a))
                c=0;
            else
                c=1;
            end
        end
        a=str2double(a);
        if a~=n1*n2
            fprintf('you suck\n')
        else
            fprintf('good job!\n')
        end
    else
        s=sprintf('\n%0.0f / %0.0f = ',n1,n2);
        while c==0
            a='';
            a=input(s,'s');
            if isnan(str2double(a))
                c=0;
            else
                c=1;
            end
        end
        a=str2double(a);
        if a~=n1/n2
            fprintf('you suck\n')
        else
            fprintf('good job!\n')
        end
    end
    b='';
    while ~(strcmpi(b,'y')||strcmpi(b,'n')||strcmpi(b,'yes')||strcmpi(b,'no')||strcmpi(b,'1')||strcmpi(b,'2'))
        b='';
        b=input('go again?(y/n)','s');
        if strcmpi(b,'n')||strcmpi(b,'no')||strcmp(b,'2')
            x=1;
        else
            x=0;
        end
    end
        end
else
while x==0
    x=0;
    c=0;
    n1=randi([1,9]);
    n2=randi([1,9]);
    op=randi([1,2]);
    if op==1
        s=sprintf('\n%0.0f + %0.0f = ',n1,n2);
        while c==0
            a='';
            a=input(s,'s');
            if isnan(str2double(a))
                c=0;
            else
                c=1;
            end
        end
        a=str2double(a);
        if a~=n1+n2
            fprintf('you suck\n')
        else
            fprintf('good job!\n')
        end
    elseif op==2
        s=sprintf('\n%0.0f - %0.0f = ',n1,n2);
        while c==0
            a='';
            a=input(s,'s');
            if isnan(str2double(a))
                c=0;
            else
                c=1;
            end
        end
        a=str2double(a);
        if a~=n1-n2
            fprintf('you suck\n')
        else
            fprintf('good job!\n')
        end
    elseif op==3
        s=sprintf('\n%0.0f * %0.0f = ',n1,n2);
        while c==0
            a='';
            a=input(s,'s');
            if isnan(str2double(a))
                c=0;
            else
                c=1;
            end
        end
        a=str2double(a);
        if a~=n1*n2
            fprintf('you suck\n')
        else
            fprintf('good job!\n')
        end
    else
        s=sprintf('\n%0.0f / %0.0f = ',n1,n2);
        while c==0
            a='';
            a=input(s,'s');
            if isnan(str2double(a))
                c=0;
            else
                c=1;
            end
        end
        a=str2double(a);
        if a~=n1/n2
            fprintf('you suck\n')
        else
            fprintf('good job!\n')
        end
    end
    b='';
    while ~(strcmpi(b,'y')||strcmpi(b,'n')||strcmpi(b,'yes')||strcmpi(b,'no')||strcmpi(b,'1')||strcmpi(b,'2'))
        b='';
        b=input('go again?(y/n)','s');
        if strcmpi(b,'n')||strcmpi(b,'no')||strcmp(b,'2')
            x=1;
        else
            x=0;
        end
    end
end
end
        
