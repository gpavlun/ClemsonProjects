%Gregory Pavlunenko ENGR1410 222 2/2/24
function[wt,time]=ReviewFnE1_gpavlun(Pin,eff,H,mass)
g=9.8;
wt=mass*2.205
Roundedwt=round(wt)
time=(mass*g*H)/(Pin*eff);
end