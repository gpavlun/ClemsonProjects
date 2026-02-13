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