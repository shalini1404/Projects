function mu = find_mu(mu,class,Xtrain)
    for i=1:size(mu,1)
        ind_tmp = find(class==i);
        mu(i,:) = (sum(Xtrain(ind_tmp,:),1))/size(ind_tmp,1);
    end