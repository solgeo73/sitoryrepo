def maximum(a):
	m = -999999999999
	for i in a:
		if i > m:
			m = i
	return m
n = int(input())
l = []
for k in range(n):
	l += [int(input())]
print(maximum(l))
