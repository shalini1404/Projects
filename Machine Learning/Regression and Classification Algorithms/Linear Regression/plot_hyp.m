function c=plot_hyp(X,Y,theta)
H=X*theta;                          %calculate hypothesis
figure();
hold on;
plot(X(:,2), Y, 'o');               %plot points
plot(X(:,2), H, 'Linewidth', 1.5)   %plot hypothesis
xlabel('area');
ylabel('Price');
title('plot for linear regression hypothesis')
hold off;