x = 1
def f1 ():
    x = 2
    def f2 ():
        global x
        x = 3
    f2()
    print(x)

f1()
print(x)
