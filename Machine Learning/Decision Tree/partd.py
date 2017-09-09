from numpy import genfromtxt
import pandas as pd
import numpy as np
from sklearn.ensemble import RandomForestClassifier
Xtrain = np.array(pd.read_csv('covType/train.dat', delimiter=',', header=None, skiprows=1))
Ytrain = Xtrain[:,(Xtrain.shape[1]-1)]
Xtrain = Xtrain[:,0:(Xtrain.shape[1]-1)]

Xtest = np.array(pd.read_csv('covType/test.dat', delimiter=',', header=None, skiprows=1))
Ytest = Xtest[:,(Xtest.shape[1]-1)]
Xtest = Xtest[:,0:(Xtest.shape[1]-1)]

Xvalid = np.array(pd.read_csv('covType/valid.dat', delimiter=',', header=None, skiprows=1))
Yvalid = Xvalid[:,(Xvalid.shape[1]-1)]
Xvalid = Xvalid[:,0:(Xvalid.shape[1]-1)]

clf = RandomForestClassifier(n_estimators=10,criterion='entropy',max_features='sqrt',)
clf = clf.fit(Xtrain, Ytrain)


pr = clf.predict(Xtrain)
pr = np.asarray(pr)

prtest = clf.predict(Xtest)
prtest = np.asarray(prtest)

prvalid = clf.predict(Xvalid)
prvalid = np.asarray(prvalid)


acctest = (np.sum(prtest==Ytest[:]))/Ytest.shape[0]*100
acc = (np.sum(pr==Ytrain[:]))/Ytrain.shape[0]*100
accvalid = (np.sum(prvalid==Yvalid[:]))/Ytest.shape[0]*100

print("accuracy train test validation", acc, acctest,accvalid)