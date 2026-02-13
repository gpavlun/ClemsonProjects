%% function
function L3_Fn_gpavlun(Data,Information)
%plot data
figure;
[r,c]=size(Data);
color=1;
for t1=2:2:r
hold on;
plot(Data(t1-1,:),Data(t1,:),Information{color,2});
hold off;
color=color+1;
end
x=sprintf(['Temperature difference (\\DeltaT) [' char(176) 'C]']);
grid on;
axis([0,10,0,100])
ylabel(x)
xlabel('Time (t) [min]')

