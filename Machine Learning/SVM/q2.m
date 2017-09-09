Xtrain=importdata('svm\traindata.txt');     %import training data
Ytrain=importdata('svm\trainlabels.txt');   %import label of training data
Xtest=importdata('svm\testdata.txt');       %import test data
Ytest=importdata('svm\testlabels.txt');     %import label of test data

tindex=find(Ytrain==2);                     %find index of training label y=2
oindex=find(Ytrain==1);                     %find index of training label y=1
Ytrain(tindex)=-1;
sizetrain=size(Ytrain,1);
b=ones(sizetrain,1);                        %b is the vector of all ones
%Q matrix for calculating alpha
Q1=Ytrain*Ytrain';                          
Q2=Xtrain*Xtrain';
Q=-1/2*(Q1.*Q2);
C=500;
%calculating alpha for linear kernel
cvx_begin
    variable alpa(sizetrain);
    maximize(alpa'*Q*alpa+b'*alpa);
    subject to
      0 <= alpa <= C
      alpa'*Ytrain == 0
cvx_end
support_vectors=find(1<alpa)                                %support vectors for gaussian kernels
%calculate w, intercept b for linear kernel
[w,intercept_b]=find_wb(alpa,Ytrain,Xtrain);

tindex_test=find(Ytest==2);
Ytest(tindex_test)=-1;
test_accuracy=accuracy_fun(Xtest,w,intercept_b,Ytest)         %test accuracy


%gaussian Kernel starts
gaus_k=zeros(sizetrain,sizetrain);
gamma=2.5;
%calculate gaussian kernel matrix
for i=1:sizetrain
    for j=1:sizetrain
        gaus_k(i,j)=exp(-gamma*((norm(Xtrain(i,:)-Xtrain(j,:)))^2));
    end
end
Q_gaus=-1/2*(Q1.*gaus_k);       %Q matrix for finding alpha
%alpha claculation for gaussian kernel
cvx_begin
    variable alpa_gaus(sizetrain);
    maximize(alpa_gaus'*Q_gaus*alpa_gaus+b'*alpa_gaus);
    subject to
      0 <= alpa_gaus <= C
      alpa_gaus'*Ytrain == 0
cvx_end
support_vectors_gaus=find(1<alpa_gaus)      %support vectors for gaussian kernels
%gauss_accuracy=gaus_acc(gaus_k,alpa_gaus, Xtrain,Ytrain,Ytrain,Xtrain)
gauss_accuracy=gaus_acc(gaus_k,alpa_gaus, Xtrain,Ytrain,Ytest,Xtest) %gaussian accuracy

