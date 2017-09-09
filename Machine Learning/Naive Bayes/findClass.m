function [H]=findClass(X,prob,Y,phi)
probdoc=prob*X';                    %total probability of each word of document given y
probdoc=bsxfun(@plus,phi,probdoc);  %total probability of (x,y) for all combination of classes
[M,I]=max(probdoc);                 %find index of class with max probability for each document
I=I';
H=Y(I);                             %predict label for each document