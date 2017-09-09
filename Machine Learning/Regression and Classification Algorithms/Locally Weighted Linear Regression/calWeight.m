function W=calWeight(point,X,tau)
m=size(X,1);            %number of training example
W=eye(m);
for i=1:m
    W(i,i)=exp(((point(:,2)-X(i,2))^2)/(-2*(tau^2)));   %calculate weight matrix
end
