Xtrain = importdata('kmeans_data\attr.txt');               %read text file of train data
Ytrain =  importdata('kmeans_data\label.txt');             %store labels in ytrain
tic
k=6;
ind = (randperm(size(Xtrain,1),k))';                        %correct this
mu = Xtrain(ind,:);
diff = 0;
%J_c = 0;
flag = true;

class = find_class(Xtrain,mu);
mu = find_mu(mu,class,Xtrain);

J_c = findcost(Xtrain,mu,class)
iter  = 0;
while(flag)
    iter = iter+1;
    class = find_class(Xtrain,mu);
    mu = find_mu(mu,class,Xtrain);
    new_j =  findcost(Xtrain,mu,class)
    diff = J_c - new_j
    if(diff<(10^(-4)))                     %checking convergence criteria
        flag=false;
    end
    J_c=new_j;
end
toc