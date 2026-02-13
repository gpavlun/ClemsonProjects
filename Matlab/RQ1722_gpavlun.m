DartTosses=readtable('DartTosses.xlsx','Sheet','Darts');
x=table2array(DartTosses(:,2));
y=table2array(DartTosses(:,3));
z=table2array(DartTosses(:,1));
DartDistances=[((x.^2)+(y.^2)).^(1/2)];
maxname=z{find(DartDistances==max(DartDistances)),1};
minname=z{find(DartDistances==min(DartDistances)),1};

Bullseye=sprintf('%s is closest to the bullseye and %s is farthest from the bullseye.',minname,maxname);