# the interpolation of a given data set by the polynomial of lowest possible degree that passes through the points of the dataset.

import matplotlib.pyplot as plt


def interpolate(data, x):
	result = 0
	for i in range(len(data)):

		y_i = data[i][1]

		for j in range(len(data)):
			if (i!=j):

				x_j = data[j][0]
				x_i = data[i][0]

				y_i = y_i*((x - x_j) / (x_i - x_j)) 

		result += y_i

	return result

def plot(data):
	x = [point[0] for point in data]
	y = [point[1] for point in data]

	x.sort()
	y.sort()

	plt.plot(x,y)
	plt.show()


def main(data, x):
	result = interpolate(data, x)
	data.append([x, result])
	plot(data)
  return result
  
 # example:
 
data = [[2,3],[4,65], [6,32], [8,11]]
result = main(data,10)
