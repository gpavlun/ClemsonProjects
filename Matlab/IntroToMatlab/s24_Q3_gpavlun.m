%gregory pavlunenko ENGR1410 2/16/24
clc
clear
TripData=readtable("Qz3Data.xlsx");
codes=table2cell(TripData(:,1));
cost=table2array(TripData(:,2));
Start=listdlg("PromptString","select airport code","ListString",codes,"selectionmode","single");
fprintf('Your flight from %s will cost $%0.2f.\n\n',codes{Start,1},cost(Start,1))

TripData=readtable("Qz3Data.xlsx");
Start=listdlg("PromptString","select airport code","ListString",TripData.code,"selectionmode","single");
fprintf('Your flight from %s will cost $%0.2f.\n\n',Tripdata.Code(Start),Tripdata.cost(Start))