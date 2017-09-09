function c=calcost(x,y,theta)
m=size(x,1);
H=x*theta;              %calculate hypothesius
diff=y-H;
c=sum(diff.^2)/(2*m);   %calculate cost
end