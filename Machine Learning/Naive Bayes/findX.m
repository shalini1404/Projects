function [X]=findX(X,doc,arr_wrds,dict)
j=1;
arr_size=(size([doc{:}],2));
%design a matrix X where X(i,j) reprents no. of occurences of jth word of dictionary in ith document
for i=1:arr_size
    while (arr_wrds(i,1)~=dict(j))
        j=j+1;
    end
    a=str2double(arr_wrds(i,2));
    X(a,j)=X(a,j)+1;
end