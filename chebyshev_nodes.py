import math

def z(i,n):
	return 2*math.cos(math.pi*(2*i-1)/n)

def Cheb_Poly(x_0, data, a, b):
	x = [point[0] for point in data]
	y = [point[1] for point in data]

	n = len(data)

	alpha = [0]*n

	for i in range(n):

		g = [0]*n

		g[0] = y[i]
		g[1] = 0.5 * z(i,n)*g[0]

		alpha[0] += g[0]
		alpha[1] += g[1]

		for j in range(2,n):
			g[j] = z(i,n)*g[j-1] - g[j-2]
			alpha[j] += g[j]

	alpha[0] = alpha[0]/n

	for i in range(1,n):
		alpha[i] *= 2/n

	result = 0

	z_ = 2 * ( ( 2 * x_0 - (b + a) ) / ( b - a ) )

	T = [0]*n

	T[0] = 1
	T[1] = z_ / 2

	result += (alpha[0] * T[0] + alpha[1] * T[1])

	for i in range(2,n):
		T[i] = z_ * T[i-1] - T[i-2]
		result += (alpha[i]*T[i])

	return result
