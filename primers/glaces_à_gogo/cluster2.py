from __future__ import print_function
import numpy as np
from sklearn.cluster import MiniBatchKMeans
from io import StringIO

data = np.genfromtxt("in.txt",dtype="int32",skip_header=1)
comp = np.sum(np.sum(data))
X = np.zeros((comp,2))
cur = 0
for i in range(300):
	for j in range(300):
		for k in range(data[i][j]):
			X[cur] = (j,i)
			cur += 1
			
#print("Let's go !")

km = MiniBatchKMeans(30)
km.fit(X)
ans = km.cluster_centers_

for i in range(30):
	for j in range(2):
		print(ans[i][j],end=" ")
	print('')