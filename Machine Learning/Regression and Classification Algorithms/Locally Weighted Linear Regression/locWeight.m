function c=locWeight(X,Y,tau)
m=size(X,1);                        %calculting total traing example
%calculting weight,theta and corresponding estimated value for each training example
for i=1:m
    W=calWeight(X(i,:),X,tau);      %weight matrix for each point
    theta=(pinv(X'*W*X))*(X'*W*Y);  %theta
    H(i)=X(i,:)*theta;              %estimated value
end
%ploting hypothesis for given tau value
[temp,I] = sort(X(:,2));
XX=X(I,:);
YY=Y(I);
HH=H(I);
plot_hyp(XX,YY,HH);