function [arr]=findArr(doc,m1)
k=0;
arr=strings([(size([doc{:}],2)),2]);
for i=1:m1
    for j=1:size(doc{i},2)
        arr(k+1,:)=[doc{i}(j), i];
        k=k+1;
    end
end
[values, order] = sort(arr(:,1));              %sort array of words with respect to frst column
arr = arr(order,:);