# the interpolation of a given data set by the polynomial of 
# lowest possible degree that passes through the points of the dataset.

# compute diveded difference table
def diveded_diff_table(data):

	table = list(list())

	for i in range(len(data)):
		table.append([0]*len(data))

	for i in range(len(data)):
		table[i][0] = data[i][1]

	for i in range(1,len(data)):
		for j in range(0,len(data)-i):
			table[j][i] = \
			(table[j][i-1] - table[j+1][i-1])/(data[j][0] - data[i+j][0])	

	return table


# compute term like (x-x_0)(x-x_1)...(x-x_n)
def term(data, n, x):

	result = x - data[0][0]

	if (n!=1):
		for i in range(1,n):
			x_i = data[i][0]
			result *= x-x_i
	return result

def interpolate(data, x):

	result = data[0][1]

	table = diveded_diff_table(data)

	for i in range(1,len(data)):
		x_i = data[i-1][0]

		result += term(data,i,x)*table[0][i]

	return result
 

def plot(data):
	x = [point[0] for point in data]
	y = [point[1] for point in data]

	x.sort()
	y.sort()

	plt.plot(x,y)
	plt.show()


def main(data, x):
	result = interpolate(data,x)
	plot(data)
	print(result)



