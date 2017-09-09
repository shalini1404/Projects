X=load('q4x.dat');                               %read data for x values
Y=importdata('q4y.dat');                         %read data for y values
m=size(X,1);                                     %total number no of training examples

X(:,1)=(X(:,1)-mean(X(:,1)))/sqrt(var(X(:,1)));  %normalizing the data
X(:,2)=(X(:,2)-mean(X(:,2)))/sqrt(var(X(:,2)));  %normalizing the data
%calculating phi
phi=0;
for i=1:m
    if(strcmp(Y(i),'Canada'))
        phi=phi+1;
    end
end
phi=phi/m
pause
%calculating mu1, mu2
mu1=zeros(2,1);
yones=find(ismember(Y, 'Alaska'));               %finding index for Alaska 
yzeros=find(ismember(Y, 'Canada'));              %finding index for Canada

%calculating mu1 for Alaska
mu1=sum(X(yones,:))/size((X(yones,1)),1);        
mu1=mu1'
pause

%calculating mu2 for Canada
mu2=zeros(2,1);
mu2=sum(X(yzeros,:))/size((X(yzeros,1)),1);   
mu2=mu2'
pause

%calculating sigma when sigma1=sigma2
sigma=zeros(2,2);                                
for i=1:m
    if(strcmp(Y(i),'Alaska'))
        sigma=sigma+((X(i,:)'-mu1)*(X(i,:)'-mu1)');
    else
        sigma=sigma+(X(i,:)'-mu2)*(X(i,:)'-mu2)';
    end
end
sigma=sigma./m
pause

%plotting figure
figure();
hold on;
plot_hyp(X,yones, yzeros);                        %plot points on graph
pause

%calculating linear equation
lin_bound(mu1, mu2,sigma,phi);

%calculating sigma1 for alaska
sigma1=zeros(2,2);                 
n=0;
for i=1:m
    if(strcmp(Y(i),'Alaska'))
        sigma1=sigma1+((X(i,:)'-mu1)*(X(i,:)'-mu1)');
        n=n+1;
    end
end
sigma1=sigma1/n
pause

%calculating sigma2 for Canada
sigma2=zeros(2,2);
n=0;
for i=1:m
    if(strcmp(Y(i),'Canada'))
        sigma2=sigma2+((X(i,:)'-mu2)*(X(i,:)'-mu2)');
        n=n+1;
    end
end
sigma2=sigma2/n
pause

%quadratic equation for quadratic boundary
quad_bound(mu1,mu2,sigma1,sigma2,phi);