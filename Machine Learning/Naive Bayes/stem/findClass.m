function [H]=findClass(X,prob,Y,phi)
probdoc=prob*X';
probdoc=bsxfun(@plus,phi,probdoc);
[M,I]=max(probdoc);
I=I';
H=Y(I);