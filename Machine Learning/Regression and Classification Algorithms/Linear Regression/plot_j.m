function c=plot_j(X,Y,theta0, theta1, alpha)
m=size(X,1);
theta=zeros(2,1);                                %initializing theta
cost=calcost(X,Y,theta);                         %calculate error cost at initial theta
flag=true;
%c=0;
while flag
    %c=c+1;
    scatter3(theta(1),theta(2),cost);             %plotting ponts on each iteration
    H=X*theta;                                    %calculting hypothesis at each iteration
    theta=theta+((alpha*(X'*(Y-H)))/m);           %calculating new theta
    new_cost=calcost(X,Y,theta);                 
    diff_cost=(cost-new_cost)
    if(diff_cost<(10^(-5)))                       %checking convergence criteria
        flag=false;
    end
    cost=new_cost;
    
    pause(0.2);
end
scatter3(theta(1),theta(2),cost);
hold off;