from __future__ import print_function
import numpy as np
from sklearn.cluster import KMeans
from io import StringIO
import time

s = time.time()
data = np.genfromtxt("in.txt",dtype="int32",skip_header=1)
comp = np.sum(np.sum(data))
X = np.zeros((comp,2))
cur = 0

for i in range(300):
	for j in range(300):
		for k in range(data[i][j]):
			X[cur] = (j,i)
			cur += 1
e = time.time()
np.random.shuffle(X)
#print("Loading and preparing data : {}".format(e-s))

s = time.time()
km = KMeans(30,init='random',precompute_distances=True,max_iter=100,tol=1e-5,n_init=1)
e = time.time()
#print("Loading KMeans : {}".format(e-s))
s = time.time()
km.fit(X[0:100000])
e = time.time()
#print("Fitting : {}".format(e-s))
ans = km.cluster_centers_

for i in range(30):
	for j in range(2):
		print(ans[i][j],end=" ")
	print('')
