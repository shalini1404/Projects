function [accuracy]=accuracy_fun(X,w,intercept_b,Y)
h=(X*w)+intercept_b;        %w_transpose x + b
ho_index=find(h>=0);
ht_index=find(h<0);
h(ho_index)=1;
h(ht_index)=-1;
m=size(Y,1);
accuracy=((sum(h==Y))/m)*100;   %accuracy of linear kernel