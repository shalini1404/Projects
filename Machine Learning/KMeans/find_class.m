function class = find_class(Xtrain,mu)
    m = size(Xtrain,1);
    c = size(mu,1);
    class = zeros(m,1);
    for i=1:m
        for j=1:c
            tmp_class = (norm(Xtrain(i,:)-mu(j,:)))^2;
            if(j==1)
                min_class = tmp_class;
                min_ind = 1;
            else
                if(min_class>tmp_class)
                    min_class = tmp_class;
                    min_ind = j;
                end    
            end
        end
        class(i) = min_ind;
    end