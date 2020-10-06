(lambda home, slf, get_nums, opt:
    (lambda n:
        (lambda classes:
            [(home.update(x) if (0 in x) else 0) for x in classes] + 
            [(slf.update(x) if (x&home) else 0) for x in classes] + [0]
        )([set(get_nums()[1:]) for x in range(n)]) and
        (opt(home-{0}) or opt(slf-home))
    )(get_nums()[0])
)(set(), set(), lambda: [int(x) for x in input().split(' ')], lambda st: print(" ".join(str(x) for x in st)) if st else print("None"))
