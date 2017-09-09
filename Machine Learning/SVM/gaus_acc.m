function acc=gaus_acc(k,alpa,X,Y,Ytest,Xtest)
wt_temp=alpa.*Y;
sizetrain=size(Y,1);
sizetest=size(Ytest,1);
gamma=2.5;
gaus_k=zeros(sizetest,sizetrain);
%calculating xx_t between training and test data
for i=1:sizetest
    for j=1:sizetrain
        gaus_k(i,j)=exp(-gamma*((norm(Xtest(i,:)-X(j,:)))^2));
    end
end
wt_x=gaus_k*wt_temp;        %w_transpose x calculation 
wtb_x=k'*wt_temp;
%calculating b
alpa_ind=find((0<alpa)&(alpa<499));
tindex=find(Y==-1);
oindex=find(Y==1);
tindex=intersect(tindex,alpa_ind);
oindex=intersect(oindex,alpa_ind);
intercept_b=-1/2*(max(wtb_x(tindex))+min(wtb_x(oindex)));
h=wt_x+intercept_b;             %calculating w_transpose x + b
ho_index=find(h>=0);
ht_index=find(h<0);
h(ho_index)=1;
h(ht_index)=-1;
acc=((sum(h==Ytest))/sizetest)*100; %accuracy of gaussian kernel