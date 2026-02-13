function [T_fn]=TempSim()
global Attached_ref
global T_ref
global TESTFLAG_T
  
if isempty(T_ref) || strcmpi(Attached_ref,'yes')
    T_fn=rand*0.25+0.6;
else
    T_fn=T_ref;
    TESTFLAG_T=1; % TESTFLAG_T is used to verify that the code does not
    % contain clear, which would delete the T_ref provided in the test
end