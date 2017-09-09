function c=plot_hyp(X,yones,yzeros)
plot(X(yones,1), X(yones,2), '+');      %plot points for Alaska
plot(X(yzeros,1), X(yzeros,2), 'o');    %plot points for Canada
legend('Alaska', 'Canada');
xlabel('X1');
ylabel('X2');