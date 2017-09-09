function [Y,doc]=getData(filein)
filein=string(filein);          %convert each document to string
m=size(filein,1);               
f1=strings([m,2]);             
for i=1:m
   f1(i,:)=strsplit(filein(i),'\t'); %split the document into labels, text
end
Y=f1(:,1);                              %labels stored in Y
doc=cell(1,m);
for i=1:m
    doc{i}=strsplit(strtrim(f1(i,2)));  %text stored in doc
end
