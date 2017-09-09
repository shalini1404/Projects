X=load('q2x.dat');                               %read data for x values
Y=load('q2y.dat');                               %read data for y values
m=size(X,1);                                     %total number no of training examples
X=[ones(m,1) X];                                 %adding x0 to X matrix
X(:,2)=(X(:,2)-mean(X(:,2)))/sqrt(var(X(:,2)));  %normalizing the data
X(:,3)=(X(:,3)-mean(X(:,3)))/sqrt(var(X(:,3)));  %normalizing the data
theta=zeros(3,1);                                %initializing theta
cost=calcost(X,Y,theta);                         %calculate error cost at initial theta
flag=true;
c=0;
%calculating cost using newton's method
while flag
    c=c+1;
    H=1./(1+exp(-X*theta));                     %calculating hypothesis
    delJ=(X'*(H-Y))/m;                          %calculating del cost
    Hess=zeros(3,3);
    %calculating Hessian for newton's method
    for i=1:m
        Hess=Hess+(H(i)*(1-H(i))*(X(i,:))'*(X(i,:)));  
    end
    Hess=Hess/m;
    theta=theta-((inv(Hess))*delJ);             %calculating theta in each iteration
    new_cost=calcost(X,Y,theta);                %calculating new cost with new theta                 
    diff_cost=(cost-new_cost);
    if(diff_cost<(10^(-7)))                     %checking convergence criteria
        flag=false;
    end
    cost=new_cost;
end
theta
pause
plot_hyp(X,Y,theta);                            %plot data and decision boundary
