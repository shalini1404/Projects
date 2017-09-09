Xtrain = importdata('kmeans_data\attr.txt');               %read text file of train data
Ytrain =  importdata('kmeans_data\label.txt');             %store labels in ytrain
m = size(Xtrain,1);
tic
k=6;
for t=1:10
    ind = (randperm(size(Xtrain,1),k))';                        
    mu = Xtrain(ind,:);
    init_mu = mu;
    %diff = 0;
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
    if(t==1)
        best_mu = init_mu;
        best_j = J_c;
    else
        if(best_j>J_c)
            best_mu = init_mu;
            best_j = J_c;
        end
    end
end

best_mu;
best_j
toc
%next part plotting
diff = 0;
%J_c = 0;
flag = true;

accuracy = zeros(60,1);
class = find_class(Xtrain,best_mu);
mu = find_mu(best_mu,class,Xtrain);
J_mat = zeros(60,1);
J_c = findcost(Xtrain,mu,class)
iter  = 0;
for i=1:60
    iter = iter+1;
    class = find_class(Xtrain,mu);
    mu = find_mu(mu,class,Xtrain);
    new_j =  findcost(Xtrain,mu,class)
    diff = J_c - new_j
    if(diff<(10^(-4)))                     %checking convergence criteria
        flag=false;
    end
    J_c=new_j;
    J_mat(i)=J_c;
    pred_class = predict_class(class,k,Ytrain,m);
    accuracy(i) = sum(pred_class==Ytrain)/m*100;
end
figure();
hold on;
iterr = [1:60];
plot(iterr, J_mat, 'LineWidth', 0.8);               %plot points
xlabel('iterations');
ylabel('cost');
title('plot for cost vs iterations')
hold off;
figure();
hold on;
plot(iterr, accuracy, 'LineWidth', 0.8);               %plot points
xlabel('iterations');
ylabel('cost');
title('plot for accuracy vs iterations')
hold off;