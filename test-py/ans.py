def get_nums ():
	return [int(x) for x in input().split(' ')]
 
def opt(st):
	if st:
		print(" ".join(str(x) for x in st))
	else:
		print("None")
n = get_nums()[0]
 
classes = []
 
home = set()
slf = set()
for i in range(n):
	cur = set(get_nums()[1:])
	classes.append(cur)
	if 0 in cur:
		home = home | cur
 
for x in classes:
	if (home&x):
		slf = slf | x
 
slf -= home
home -= {0}
opt(home)
opt(slf)
