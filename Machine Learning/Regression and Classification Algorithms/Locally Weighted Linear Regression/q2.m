X=csvread('q3x.dat');                           %read data for x values
Y=csvread('q3y.dat');                           %read data for y values
m=size(X,1);                                    %total number no of training examples
X=[ones(m,1) X];                                %adding x0 to X matrix

theta=(pinv(X'*X))*X'* Y                        %calculating theta for linear regression
H=zeros(m,1);                                   %initializing hypothesis
cost=((X*theta)-Y)'*((X*theta)-Y)/(2*m)         %calculating cost for the theta calculated
pause
%plotting data and hypothesis obtained for linear regression
H=X*theta;                                      %calculating hypothesis

plot_hyp(X,Y,H);                                %ploting data and hypothesis
title('plot for unweigted linear regression')
hold off;
pause

%locally weighted regression starts
locWeight(X,Y,0.8);                             %tau=0.8
title('plot for weigted linear regression for tau=0.8')
hold off;
pause
locWeight(X,Y,0.1);                             %tau=0.1
title('plot for weigted linear regression for tau=0.1')
hold off;
pause
locWeight(X,Y,0.3);                             %tau=0.3
title('plot for weigted linear regression for tau=0.3')
hold off;
pause
locWeight(X,Y,2);                               %tau=2
title('plot for weigted linear regression for tau=2')
hold off;
pause
locWeight(X,Y,10);                              %tau=10
title('plot for weigted linear regression for tau=10')
hold off;
