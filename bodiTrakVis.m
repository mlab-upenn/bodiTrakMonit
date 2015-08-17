clear all;
%close all;
names={'achin'; 'hao'};
pose={'front'; 'back'; 'left'; 'right'};
trials=5;
filename={};
pathanme
for i=1:trials
    tempfilename=sprintf('%s_%s_%d.txt',names{i},pose{i},i);
end
clc;
load('paritosh_back_1.txt');
rawdata=paritosh_back_1;
rawdata_avg=mean(paritosh_back_1);
frame=rawdata(1,:);
frame= reshape(frame,16,16);
frame=frame';
neg_frame=-frame;
figure
subplot(2,1,1)
image(frame);
colormap(jet(256));

%meshgrid
[X Y]=meshgrid(1:16);
subplot(2,1,2);
surf(X,Y,neg_frame)

%2d interpolation, cubic splines
[Xq Yq]=meshgrid(1:0.1:16);
neg_frame_q=interp2(X,Y,neg_frame,Xq,Yq);
frame_q=-1*neg_frame_q;
figure
subplot(2,1,1)
image(frame_q);
colormap(jet(256));
subplot(2,1,2);
surf(Xq,Yq,neg_frame_q);

%contour plot
figure
contourf(frame_q)