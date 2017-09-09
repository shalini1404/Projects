function new_j = findcost(Xtrain,mu,class)
    new_j_mat = Xtrain - mu(class,:);
    new_j = sum(sum(new_j_mat.^2,2));