function [w,intercept_b]=find_wb(alpa,Y,X)
wtemp=alpa.*Y;
%calculating w
w=X'*wtemp;
btemp=X*w;
%calculating b
alpa_ind=find((0<alpa)&(alpa<499));
tindex=find(Y==-1);
oindex=find(Y==1);
tindex=intersect(tindex,alpa_ind);
oindex=intersect(oindex,alpa_ind);
intercept_b=-1/2*(max(btemp(tindex))+min(btemp(oindex)));