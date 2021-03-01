import timeit

def pop_first ():
    sz = 10
    lst = [x for x in range(sz)]
    res = []
    for x in range(sz):
        res.append(lst.pop(0))
    return res

def pop_last ():
    sz = 10
    lst = [x for x in range(sz)]
    res = []
    for x in range(sz):
        res.append(lst.pop())
    return res


print(timeit.timeit(pop_first))
print(timeit.timeit(pop_last))

