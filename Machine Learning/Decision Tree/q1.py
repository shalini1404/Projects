import numpy as np
import time
import math
from statistics import median
from numpy import inf
import bisect
import copy
import pandas as pd
import matplotlib.pyplot as plt


#<--------------------------------------DEFINING structure of each node---------------------------->
class Node:
    def __init__(self):
        self.attr = np.inf
        self.med = 0
        self.child = {}
        self.category = -1
    def append(self, title, child):
        self.child[title] = child
#-------------------------------------------find Data split to right and left------------------------

def findSplitData(X,i,med):
	xzero = np.where(X[:,i]<=med)[0]
	xone = np.where(X[:,i]>med)[0]
	return xzero,xone

#-----------------------------------------------Predicting Correct labels in tree-----------------------------------

def predict(Tnode,X,Y):
	if(Tnode.child=={}):
		return np.count_nonzero(Y[:,0]==Tnode.category)
	else:
		D0 = np.where(X[:,Tnode.attr]<=Tnode.med)[0]
		D1 = np.where(X[:,Tnode.attr]>Tnode.med)[0]
		#findSplitData(X,Tnode.attr,Tnode.med)
		return (predict(Tnode.child['left child'],X[D0],Y[D0])+predict(Tnode.child['right child'],X[D1],Y[D1]))


#------------------------------------------------Finding Median of each attribute----------------------------------


def findMed(X):
	med = np.zeros(X.shape[1])
	for i in range(X.shape[1]):
		if(Xtype[i]=='Continuous'):
			med[i] = np.median(X[:,i])
	return med

#-----------------------------------------------Findimg Median and index of best attribute-----------------------

def findbestattr(X,Y,lst):
	med = findMed(X)
	ConMat0 = np.zeros(X.shape[1], dtype=float)
	ConMat1 = np.zeros(X.shape[1], dtype=float)
	px0 = np.zeros(X.shape[1], dtype=float)
	px1 = np.zeros(X.shape[1], dtype=float)
	for i in range(X.shape[1]):
		if(i not in lst):
			izero = np.where(X[:,i]<=med[i])[0]
			ione = np.where(X[:,i]>med[i])[0]
			y2 = Y[izero]
			y2 = y2[:,0]
			Ycount = np.bincount(y2)
			total = np.sum(Ycount)
			py = [(item/total) for item in Ycount]
			py = [(-item*math.log2(item)) for item in py if item!=0]
			ConMat0[i] = np.sum(py)
			y21 = Y[ione]
			y21 = y21[:,0]
			Ycount1 = np.bincount(y21)
			total3 = np.sum(Ycount1)
			py1 = [(item/total3) for item in Ycount1]
			py1 = [(-item*math.log2(item)) for item in py1 if item!=0]
			ConMat1[i] = np.sum(py1)
			px0[i] = len(izero)/X.shape[0]
			px1[i] = len(ione)/X.shape[0]
		else:
			ConMat0[i] = np.inf
			ConMat1[i] = np.inf
			px0[i] = np.inf
			px1[i] = np.inf
	i1 = np.where(px0==0)[0]
	i2 = np.where(px1==0)[0]
	indd = np.union1d(i1,i2)
	total0 = ConMat0*px0
	total1 = ConMat1*px1
	contt = total0+total1
	contt[indd]=np.inf
	best = contt.argmin()
	bestmed = med[best]
	return best,bestmed

#--------------------------------------------------Choosing best attribute--------------------------------

def chooseBest(Tnode,X,Y,lst):
	y2 = Y[:,0]
	y2 = np.bincount(y2)
	ymax = y2.argmax()
	best,bestmed = findbestattr(X,Y,lst)
	return (best,bestmed,ymax)


#------------------------------------------GROW TREE---------------------------------------------

def GrowTree(Tnode,X,Y,lst):
	global gl
	gl=gl+1
	y2 = Y[:,0]
	check = np.allclose(y2, y2[0])
	if(check):
		Tnode.category = y2[0]
		print("node:",gl)
		return 
	else:
		Tnode.attr,Tnode.med,Tnode.category = chooseBest(Tnode,X,Y,lst)	
		if(Xtype[Tnode.attr] == 'Discrete'):
			lst.append(Tnode.attr)
		print("node:",gl)
		l1 = lst[:]
		l2 = lst[:]
		D0,D1 = findSplitData(X,Tnode.attr,Tnode.med)
		leftchild = Node()
		rightchild = Node()
		Tnode.append('left child', leftchild)
		Tnode.append('right child', rightchild)
		GrowTree(Tnode.child['left child'], X[D0],Y[D0], l1)
		GrowTree(Tnode.child['right child'], X[D1],Y[D1], l2)
		return Tnode


#---------------------------------------------Calculating accuracy at each node-----------------------------	

def calAcc(Tnode,X,Y,X1,Y1,X2,Y2):
	global glb
	glb=glb+1
	if(Tnode.child=={}):
		predTrain[Y[:,1]] = Tnode.category
		predTest[Y1[:,1]] = Tnode.category
		predvalid[Y2[:,1]] = Tnode.category
		acc[glb] = (np.count_nonzero(predTrain==Ytrain[:,0]))/Ytrain.shape[0]*100
		accTest[glb] = (np.count_nonzero(predTest==Ytest[:,0]))/Ytest.shape[0]*100
		accvalid[glb] = (np.count_nonzero(predvalid==Yvalid[:,0]))/Yvalid.shape[0]*100
	else:
		predTrain[Y[:,1]] = Tnode.category
		predTest[Y1[:,1]] = Tnode.category
		predvalid[Y2[:,1]] = Tnode.category
		acc[glb] = (np.count_nonzero(predTrain==Ytrain[:,0]))/Ytrain.shape[0]*100
		accTest[glb] = (np.count_nonzero(predTest==Ytest[:,0]))/Ytest.shape[0]*100
		accvalid[glb] = (np.count_nonzero(predvalid==Yvalid[:,0]))/Yvalid.shape[0]*100
		D0 = np.where(X[:,Tnode.attr]<=Tnode.med)[0]
		D1 = np.where(X[:,Tnode.attr]>Tnode.med)[0]
		Dtest0 = np.where(X1[:,Tnode.attr]<=Tnode.med)[0]
		Dtest1 = np.where(X1[:,Tnode.attr]>Tnode.med)[0]
		Dvalid0 = np.where(X2[:,Tnode.attr]<=Tnode.med)[0]
		Dvalid1 = np.where(X2[:,Tnode.attr]>Tnode.med)[0]
		print("node:",glb)
		calAcc(Tnode.child['left child'], X[D0],Y[D0],X1[Dtest0],Y1[Dtest0],X2[Dvalid0],Y2[Dvalid0])
		calAcc(Tnode.child['right child'], X[D1],Y[D1],X1[Dtest1],Y1[Dtest1],X2[Dvalid1],Y2[Dvalid1])

#------------------------------------------PRUNING--------------------------------------------
def pruning(Tnode,indvalid,indtrain,indtest,prvalid,prtrain,prtest,nnodes):
	Y = Yvalid[np.asarray(np.matrix(indvalid.transpose())),:][0]
	X = Xvalid[np.asarray(np.matrix(indvalid.transpose())),:][0]
	Y2 = Ytrain[np.asarray(np.matrix(indtrain.transpose())),:][0]
	X2 = Xtrain[np.asarray(np.matrix(indtrain.transpose())),:][0]
	Y1 = Ytest[np.asarray(np.matrix(indtest.transpose())),:][0]
	X1 = Xtest[np.asarray(np.matrix(indtest.transpose())),:][0]
	if(Tnode.child == {}):
		return np.count_nonzero(Y[:,0]==Tnode.category),np.count_nonzero(Y2[:,0]==Tnode.category),np.count_nonzero(Y1[:,0]==Tnode.category),1
	else:
		D0 = np.where(X[:,Tnode.attr]<=Tnode.med)[0]
		D1 = np.where(X[:,Tnode.attr]>Tnode.med)[0]
		Dtrain0 = np.where(X2[:,Tnode.attr]<=Tnode.med)[0]
		Dtrain1 = np.where(X2[:,Tnode.attr]>Tnode.med)[0]
		Dtest0 = np.where(X1[:,Tnode.attr]<=Tnode.med)[0]
		Dtest1 = np.where(X1[:,Tnode.attr]>Tnode.med)[0]
		left_ind = Y[D0,1]
		right_ind = Y[D1,1]
		left_ind_train = Y2[Dtrain0,1]
		right_ind_train = Y2[Dtrain1,1]
		left_ind_test = Y1[Dtest0,1]
		right_ind_test = Y1[Dtest1,1]
		left,left_train,left_test,nl = pruning(Tnode.child['left child'],left_ind,left_ind_train, left_ind_test,prvalid,prtrain,prtest,nnodes)
		right,right_train,right_test,nr = pruning(Tnode.child['right child'],right_ind,right_ind_train,right_ind_test,prvalid, prtrain,prtest,nnodes)
		child_total = left+right
		child_train = left_train+right_train
		child_test = left_test+right_test
		myy = np.count_nonzero(Y[:,0]==Tnode.category)
		myy_train = np.count_nonzero(Y2[:,0]==Tnode.category)
		myy_test = np.count_nonzero(Y1[:,0]==Tnode.category)
		nmy = nl+nr+1
		if(myy>child_total):
			p = prvalid[len(prvalid)-1]+(myy-child_total)
			prvalid.append(p)
			p = prtrain[len(prtrain)-1]+(myy_train-child_train)
			prtrain.append(p)
			p = prtest[len(prtest)-1]+(myy_test-child_test)
			prtest.append(p)
			n = nnodes[len(nnodes)-1]-nl-nr
			nnodes.append(n)
			Tnode.child = {}
			return myy,myy_train,myy_test,1
		else:
			return child_total,child_train,child_test,nmy

def pruneTree(root):
	print("Pruning The tree now")
	pvalid = []
	p = predict(root,Xvalid,Yvalid)
	pvalid.append(p)
	ptrain = []
	p = predict(root,Xtrain,Ytrain)
	ptrain.append(p)
	ptest = []
	p = predict(root,Xtest,Ytest)
	ptest.append(p)
	nn = []
	nn.append(90987)
	ivalid = Yvalid[:,1]
	itrain = Ytrain[:,1]
	itest = Ytest[:,1]
	c1,c2,c3,nnod = pruning(root,ivalid,itrain,itest,pvalid,ptrain,ptest,nn)
	pruneValid = c1/Yvalid.shape[0]*100
	pruneTrain = c2/Ytrain.shape[0]*100
	pruneTest = c3/Ytest.shape[0]*100
	pvalid = np.asarray(pvalid)
	ptest = np.asarray(ptest)
	ptrain = np.asarray(ptrain)
	pvalid = pvalid/Yvalid.shape[0]*100
	ptest = ptest/Ytest.shape[0]*100
	ptrain = ptrain/Ytrain.shape[0]*100
	plt.plot(nn, ptrain, 'r-' , label="train_accuracy")
	plt.plot(nn, ptest, 'b-', label="test accuracy") 
	plt.plot(nn, pvalid, 'g-', label="validation accuracy")
	plt.axis([77600, 90990, 80, 102])
	plt.title("Accuracy vs No. of nodes After Pruning")
	plt.xlabel("Number of nodes")
	plt.ylabel("Accuracy in %")
	plt.legend(loc="lower right")
	plt.show()
	return pruneValid,pruneTrain,pruneTest

#-------------------------------------------MAIN CODE------------------------------------------
start_time = time.time()
Xtrain = np.array(pd.read_csv('covType/train.dat', delimiter=',', header=None, skiprows=1))
first_line = pd.read_csv('covType/train.dat', delimiter=',', header=None, nrows=1)
Xtype = [first_line[i][0].split(":")[1] for i in range((first_line).shape[1])]
Xname = [first_line[i][0].split(":")[0] for i in range((first_line).shape[1])]
Ytrain = Xtrain[:,(Xtrain.shape[1]-1)]
Xtrain = Xtrain[:,0:(Xtrain.shape[1]-1)]
ind = [x for x in range(Xtrain.shape[0])]
ind = np.asarray(ind)
Ytrain = np.asarray(np.concatenate((np.asmatrix(Ytrain).transpose(), np.asmatrix(ind).transpose()), axis=1))
root = Node()
gl = 0
root = GrowTree(root,Xtrain,Ytrain,[])
end_time = time.time()
print("time:",end_time-start_time)

#--------------------------------------------test daTA----------------------------------------------------------


Xtest = np.array(pd.read_csv('covType/test.dat', delimiter=',', header=None, skiprows=1))
Ytest = Xtest[:,(Xtest.shape[1]-1)]
Xtest = Xtest[:,0:(Xtest.shape[1]-1)]
indtest = [x for x in range(Xtest.shape[0])]
indtest = np.asarray(indtest)
Ytest = np.asarray(np.concatenate((np.asmatrix(Ytest).transpose(), np.asmatrix(indtest).transpose()), axis=1))
#----------------------------------------validation-------------------------------------------------------------


Xvalid = np.array(pd.read_csv('covType/valid.dat', delimiter=',', header=None, skiprows=1))
Yvalid = Xvalid[:,(Xvalid.shape[1]-1)]
Xvalid = Xvalid[:,0:(Xvalid.shape[1]-1)]
indvalid = [x for x in range(Xvalid.shape[0])]
indvalid = np.asarray(indvalid)
Yvalid = np.asarray(np.concatenate((np.asmatrix(Yvalid).transpose(), np.asmatrix(indvalid).transpose()), axis=1))
predTrain = np.zeros(Ytrain.shape[0])
predTest = np.zeros(Ytest.shape[0])
predvalid = np.zeros(Yvalid.shape[0])


#------------------------------------ACCURACY at each node------------------------------------

acc = [0.0 for x in range(90988)]
accTest = [0.0 for x in range(90988)]
accvalid = [0.0 for x in range(90988)]
start_time = time.time()
glb = 0
calAcc(root,Xtrain,Ytrain,Xtest,Ytest,Xvalid,Yvalid)
end_time = time.time()
print("time:",end_time-start_time)
g = [x for x in range(90988)]


#----------------------------------PLOTTING ACCURACIES---------------------------------------
plt.plot(g, acc, 'r-' , label="train_accuracy:")
plt.plot(g, accTest, 'b-', label="test accuracy") 
plt.plot(g, accvalid, 'g-', label="validation accuracy")
plt.axis([0, 90987, 0, 100])
plt.title("Accuracy vs No. of nodes Before Pruning")
plt.xlabel("Number of nodes")
plt.ylabel("Accuracy in %")
plt.legend(loc="upper left")
plt.show()


#------------------------------------Correct Prediction-------------------------------------
pr = predict(root,Xtrain,Ytrain)
pr = pr/Ytrain.shape[0]*100

pr2 = predict(root,Xtest,Ytest)
pr2 = pr2/Ytest.shape[0]*100

pr3 = predict(root,Xvalid,Yvalid)
pr3 = pr3/Yvalid.shape[0]*100
print("Accuracies train, test, validation:",pr,pr2,pr3)
#---------------------------------Prune Tree-------------------------------------------

start_time = time.time()
acc_prune_valid,acc_prune_train,acc_prune_test = pruneTree(root)
print("After pruning validation, train, test:",acc_prune_valid,acc_prune_train,acc_prune_test)
end_time = time.time()
print("time:",end_time-start_time)
