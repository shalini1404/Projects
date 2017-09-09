function [M]=calCM(Y,H,x)
m=size(Y,1);
equalInd=find(Y==x);
yequal=Y(equalInd);
hequal=H(equalInd);
truepositive=sum(yequal==hequal);
falsenegative=(size(yequal,1))-truepositive;
sameInd=find(H==x);
falsepositive=(size(sameInd,1))-truepositive;
truenegative=m-(truepositive+falsenegative+falsepositive);
M=[truepositive,falsenegative;falsepositive,truenegative];