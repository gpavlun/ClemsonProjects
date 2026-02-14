clc
clear
loop=1;
while loop==1
    x='';
while ~(1==strcmpi(x,'*')||1==strcmpi(x,'/')||1==strcmpi(x,'+')||1==strcmpi(x,'-')||1==strcmpi(x,'1')||1==strcmpi(x,'2')||1==strcmpi(x,'3')||1==strcmpi(x,'4')||1==strcmpi(x,'multiply')||1==strcmpi(x,'divide')||1==strcmpi(x,'add')||1==strcmpi(x,'subtract')||1==strcmpi(x,'multiplication')||1==strcmpi(x,'division')||1==strcmpi(x,'addition')||1==strcmpi(x,'subtraction'))
    x='';
    x=input('\nwhat operation would you like to do?\nmultiplication (*) division (/) addition (+) subtraction (-)\n\n','s');
end
if 1==strcmpi(x,'*')||1==strcmpi(x,'1')||1==strcmpi(x,'multiplication')||1==strcmpi(x,'multiply')
    op=1;
elseif 1==strcmpi(x,'/')||1==strcmpi(x,'2')||1==strcmpi(x,'division')||1==strcmpi(x,'divide')
    op=2;
elseif 1==strcmpi(x,'+')||1==strcmpi(x,'3')||1==strcmpi(x,'addition')||1==strcmpi(x,'add')
    op=3;
else
    op=4;
end
n1='';
while 1==isempty(n1)
    n1='';
    n1=input('what is first number?','s');
    n1=str2num(n1);
end
n2='';
if ~(op==2)
while 1==isempty(n2)
    n2='';
    n2=input('what is second number?','s');
    n2=str2num(n2);
end
else
    while 1==isempty(n2)||n2==0
    n2='';
    n2=input('what is second number?','s');
    n2=str2num(n2);
    if n2==0
        warning('divide by 0 error')
    end
    end
end
if op==1
    kl=n1*n2;
    fprintf('%0.0f * %0.0f = %0.0f\n',n1,n2,kl)
elseif op==2
    kl=n1/n2;
    fprintf('%0.0f / %0.0f = %0.0f\n',n1,n2,kl)
elseif op==3
    kl=n1+n2;
    fprintf('%0.0f + %0.0f = %0.0f\n',n1,n2,kl)
else
    kl=n1-n2;
    fprintf('%0.0f - %0.0f = %0.0f\n',n1,n2,kl)
end

y='';
while ~(1==strcmpi(y,'y')||1==strcmpi(y,'yes')||1==strcmpi(y,'n')||1==strcmpi(y,'no'))
    y='';
    y=input('go again?(y/n)','s');
end
if 1==strcmpi(y,'y')||1==strcmpi(y,'yes')
    loop=1;
else
    loop=0;
end
end