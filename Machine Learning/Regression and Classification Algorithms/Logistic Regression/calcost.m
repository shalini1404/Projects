function c=calcost(x,y,theta)
m=size(x,1);                    %calculating number of training examples
H=1./(1+exp(-x*theta));         %calculating hypothesis
H1=log(H);
c1=y'*H1;                       %cost for y=1
H2=log(1-H);
c2=(1-y)'*H2;                   %cost for y=0
c=-(c1+c2)/m;                   %total cost
end