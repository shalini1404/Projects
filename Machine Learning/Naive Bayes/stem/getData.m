function [Y,doc]=getData(filein)
filein=string(filein);
m=size(filein,1);
f1=strings([m,2]);
for i=1:m
   f1(i,:)=strsplit(filein(i),'\t'); 
end
Y=f1(:,1);
doc=cell(1,m);
for i=1:m
    doc{i}=strsplit(strtrim(f1(i,2)));
end
