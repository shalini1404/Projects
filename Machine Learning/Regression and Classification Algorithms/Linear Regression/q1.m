X=csvread('q1x.dat');                           %read data for x values
Y=csvread('q1y.dat');                           %read data for y values
m=size(X,1);                                    %total number no of training examples
X=[ones(m,1) X];                                %adding x0 to X matrix
X(:,2)=(X(:,2)-mean(X(:,2)))/sqrt(var(X(:,2))); %normalizing the data

theta=zeros(2,1);                               %initializing theta
cost=calcost(X,Y,theta);                         %calculate error cost at initial theta
flag=true;
%c=0;
while flag
    %c=c+1;
    H=X*theta;                                  %calculting hypothesis at each iteration
    theta=theta+((0.3*(X'*(Y-H)))/m);           %calculating new theta(learning rate 0.3)
    new_cost=calcost(X,Y,theta);                 
    diff_cost=(cost-new_cost);
    if(diff_cost<(10^(-6)))                     %checking convergence criteria
        flag=false;
    end
    cost=new_cost;
end
cost=calcost(X,Y,theta)                         %calculating error cost at final theta
theta                                           %final theta
pause


%plotting data and hypothesis obtained
plot_hyp(X,Y, theta);
pause

%plotting j(theta) in 3d surface

theta0=-5:0.2:15;
theta1=-5:0.2:15;

J=zeros([length(theta0), length(theta1)]);
for i=1:length(theta0)
    for j=1:length(theta1)
        J(i,j)=calcost(X,Y,[theta0(i);theta1(j)]); %calculting J for all combinations of theta1, theta0
    end
end
figure();
mesh(theta0, theta1, J');                           %mesh for parameters and J theta
%view([60 150]);
hold on;
title('plot for alpha=0.3')
plot_j(X,Y,theta0, theta1, 0.3);                    %plot J in each iteration for alpha=0.3 on mesh
pause
hold off;

%plot contours plot
figure();
hold on;
contour(theta0, theta1, J');
title('plot for alpha=0.3')
plot_j(X,Y,theta0, theta1, 0.3);                    %plot J in each iteration for alpha=0.3 on countours
pause
hold off;

%plot contour plots with different learning iteration
figure();
hold on;
contour(theta0, theta1, J');
title('plot for alpha=0.1')
plot_j(X,Y,theta0, theta1, 0.1);                %plot J in each iteration for alpha=0.1 on countours
pause
hold off;

figure();
hold on;
contour(theta0, theta1, J');
title('plot for alpha=0.5')
plot_j(X,Y,theta0, theta1, 0.5);                %plot J in each iteration for alpha=0.5 on countours
pause
hold off;

figure();
hold on;
contour(theta0, theta1, J');
title('plot for alpha=0.9')
plot_j(X,Y,theta0, theta1, 0.9);                %plot J in each iteration for alpha=0.9 on countours
pause
hold off;

figure();
hold on;
contour(theta0, theta1, J');
title('plot for alpha=1.3')
plot_j(X,Y,theta0, theta1, 1.3);                %plot J in each iteration for alpha=1.3 on countours
pause
hold off;

figure();
hold on;
contour(theta0, theta1, J');
title('plot for alpha=2.1')
plot_j(X,Y,theta0, theta1, 2.1);                %plot J in each iteration for alpha=2.1 on countours
pause
hold off;

figure();
hold on;
contour(theta0, theta1, J');
title('plot for alpha=2.5')
plot_j(X,Y,theta0, theta1, 2.5);                %plot J in each iteration for alpha=2.5 on countours
hold off;
