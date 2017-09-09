function c=quad_bound(mu1,mu2,sigma1,sigma2,phi)
insig1=inv(sigma1);
insig2=inv(sigma2);
a=insig1(1,1)-insig2(1,1);                                  %calculating coefficient for x1^2
b=insig1(2,2)-insig2(2,2);                                  %calculating coefficient for x2^2
c=insig1(1,2)-insig2(1,2)+insig1(2,1)-insig2(2,1);          %calculating coefficient for x1*x2
l=2*mu1'*(insig1);
m=2*mu2'*(insig2);
d=m(1)-l(1);                                                %calculating coefficient for x1
e=m(2)-l(2);                                                %calculating coefficient for x2
f=(log(det(sigma1)/det(sigma2))-(2*log((1-phi)/(phi)))-(mu2'*(insig2)*mu2)+(mu1'*(insig1)*mu1)); %calculating intercept term
%eqation for boundary is: a*x1^2+b*x2^2+c*x1*x2+d*x1+e*x2+f
x11=linspace(-3,3,15);
x22=(-((c*x11)+e)-(sqrt(((c*x11+e).^2)-(4*b*((a*(x11.^2))+(d*x11)+f)))))/(2*b); %calculating x2 for corresponding x1
plot(x11,x22, 'g', 'Linewidth', 1.5);                       %plotting points for quadratic boundary
