function c=plot_hyp(X,Y,H)

figure();
hold on;
plot(X(:,2), Y, 'o');               %plot data points
plot(X(:,2),H, 'Linewidth', 1.5)    %plot hypothesis
xlabel('X');
ylabel('Y');

