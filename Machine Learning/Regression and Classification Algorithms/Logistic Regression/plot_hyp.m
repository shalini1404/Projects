function c=plot_hyp(X,Y,theta)
figure();
hold on;
yones=find(Y==1);                   %find index for y=1
yzeros=find(Y==0);                  %find index for y=0
plot(X(yones,2), X(yones,3), '+');  %plot points for y=1
plot(X(yzeros,2), X(yzeros,3), 'o'); %plot points for y=0
legend('y=1', 'y=0');
%getting x2 and corresponding x3 for equation: theta'*X=0 
x_21=min(X(:,2))-1;
x_22=max(X(:,2))+1;
x_31=(-1/theta(3))*(theta(1)+(theta(2)*x_21));
x_32=(-1/theta(3))*(theta(1)+(theta(2)*x_22));
plot([x_21;x_22], [x_31;x_32], 'k', 'Linewidth', 1.5); %plotting x2,x3 for getting linear boundary
xlabel('X1');
ylabel('X2');
hold off;
