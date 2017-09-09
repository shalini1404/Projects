tic
ftrain=importdata('nb_data\r8-train-all-terms.txt');     %read text file of train data
m1=size(ftrain,1);                                       %number of documents in training data
[YTrain, docTrain]=getData(ftrain);                      %get label of document and text of document in two different matrices
uniqY=unique(YTrain);                                    %matrix of unique labels
tYTrain=sort(YTrain);                                    %sorted matrix of labels
phi=zeros(1,size(uniqY,1));                              %initialize phi
for i=1:size(uniqY,1)
    phi(i)=(nnz(ismember(tYTrain, uniqY(i))))/m1;        %calculte phi for each y value
end
phi=log(phi);
phi=phi';
dict=unique([docTrain{:}]);                              %dictionary of words in training data

%Test data
ftest=importdata('nb_data\r8-test-all-terms.txt');     %read text file of test data
m2=size(ftest,1);                                      %number of documents in test data
[YTest, docTest]=getData(ftest);                       %get label of document and text of document in two different matrices
dict2=unique([docTest{:}]);
dict=union(dict,dict2);                                 
dictsize=size(dict,2);                                  %union of dictionary of training and test data

%form an array of all the words in training data with corresponding document number
arr_wrds=findArr(docTrain,m1);
%design a matrix X where X(i,j) reprents no. of occurences of jth word of dictionary in ith document
X=zeros(m1,dictsize);
X=findX(X,docTrain,arr_wrds,dict);

%calculate log of prob matrix probWord where probWord(i,j) is log of probability
%of jth word of dictionary given ith label
probWord=zeros(size(uniqY,1),dictsize);
for i=1:size(uniqY)
    index=find(ismember(YTrain, uniqY(i)));
    temp=X(index,:);
    probWord(i,:)=log((sum(temp)+1)./(sum(temp(:))+dictsize));
    
end
Htrain=findClass(X,probWord,uniqY,phi);
accuracyTrain=((sum(Htrain==YTrain))/m1)*100            %training accuracy
%pause

%design a matrix Xtest where X(i,j) reprents no. of occurences of jth word of dictionary in ith test document
%form an array of all the words in training data with corresponding document number
arr_test=findArr(docTest,m2);
Xtest=zeros(m2,dictsize);
Xtest=findX(Xtest,docTest,arr_test,dict);

Htest=findClass(Xtest,probWord,uniqY,phi);
accuracyTest=((sum(Htest==YTest))/m2)*100               %test accuracy
%pause
%random prediction of test set
Hrand=randi(8,m2,1);
Hrand=uniqY(Hrand);
random_accuracy=((sum(Hrand==YTest))/m2)*100            %random accuracy

%majority prediction of test set
majo=mode(YTrain);
Hmajo(1:m2,1)=majo;
majority_accurcy=((sum(Hmajo==YTest))/m2)*100           %majority class accuracy

improvementOverRand=accuracyTest-random_accuracy        %improvement over random accuracy
improvementOverMajo=accuracyTest-majority_accurcy       %improvement over majority accuracy
%pause
%confusion Matrix Formation
ConfusionMat=confusionMatrix(YTest,Htest)               %computing confusion matrix
%read confusion matrix and ans questions%
toc