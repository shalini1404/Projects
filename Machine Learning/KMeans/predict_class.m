function [pred_class] =predict_class(class,k,Y,m)
pred_class = zeros(m,1);
    for i=1:k
        indxx = find(class==i);
        pred_class(indxx,1) = mode(Y(indxx)); 
    end
