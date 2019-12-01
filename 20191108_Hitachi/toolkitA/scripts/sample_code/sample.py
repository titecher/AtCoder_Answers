# recieve |V| and |E|
V, E = map(int, input().split())
es = [[] for i in range(V)]

for i in range(E):

	# recieve edges
	a, b, c = map(int, input().split())
	a, b = a-1, b-1
	es[a].append((b,c))
	es[b].append((a,c))

T = int(input())

# recieve info
for i in range(T):
	Nnew = int(input())
	for j in range(Nnew):
		new_id, dst = map(int, input().split())

# insert your code here to get more meaningful output
# all stay
for i in range(T) :
	print (-1)
