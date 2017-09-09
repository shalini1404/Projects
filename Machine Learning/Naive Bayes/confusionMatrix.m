function ConfusionMat=confusionMatrix(Y,H)
Yuniq=unique(Y);
m=size(Yuniq,1);
ConfusionMat=zeros(m,m);
for i=1:m
    equalInd=find(Y==Yuniq(i));
    hequal=H(equalInd);
    for j=1:m
        predInd=find(hequal==Yuniq(j));
        ConfusionMat(i,j)=size(predInd,1);
    end
end
%{
ConfMat=cell(1,m);
for i=1:m
    [ConfMat{i}]=calCM(Y,H,Yuniq(i));
    Yuniq(i)
    ConfMat{i}
end
%}