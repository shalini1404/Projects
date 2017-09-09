function c=lin_bound(mu1, mu2,sigma,phi)
tempx=2*(mu1'-mu2')*inv(sigma);                   %calculating coefficient of x for linear boundary
tempint=log((phi)/(1-phi))+((mu1'*inv(sigma)*mu1)-(mu2'*inv(sigma)*mu2));  %calculating intercept term for linear boundary
x1=linspace(-3,3,10);
x2=(tempint-x1*(tempx(1)))/(tempx(2));             %calculating x2 for corresponding x1(linear equation)
plot(x1,x2, 'm', 'Linewidth', 1.5);                %plot linear boundary
pause