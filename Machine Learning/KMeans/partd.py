from sklearn import svm
import pandas as pd
import numpy as np
from sklearn.model_selection import cross_val_score
Xtrain = np.array(pd.read_csv('kmeans_data/attr.txt', sep=' ', header=None))
Ytrain = np.array(pd.read_csv('kmeans_data/label.txt',sep=' ', header=None))
c, r = Ytrain.shape
Ytrain = Ytrain.reshape(c,)
#Ytrain = np.array((np.matrix(Ytrain)).transpose())
'''
lin_clf = svm.LinearSVC()
scores = cross_val_score(lin_clf, Xtrain, Ytrain, cv=10)
scores = scores*100
print("one vs all:", scores)
'''
clf = svm.SVC(kernel='linear')
scores = cross_val_score(clf, Xtrain, Ytrain, cv=10)
scores = scores*100
print("one vs one:",scores)
print("average:", np.mean(scores))
