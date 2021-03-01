n = int(input())
nums = [int(x) for x in input().split()]

def solve (idx):
    if (idx == n**4):
        print(" ".join([str(x) for x in nums]))
        exit(0)
    x, y = idx//(n*n), idx%(n*n)
    if nums[idx] != 0:
        solve(idx+1)
    else:
        used = set()
        for dx in range(n*n):
            used.add(grid[dx][y])
        for dy in range(n*n):
            used.add(grid[x][dy])
        xo = x // n * n
        yo = y // n * n
        for dx in range(n):
            for dy in range(n):
                used.add(grid[xo+dx][yo+dy])
        for test in range(1, n*n+1):
            if test not in used:
                nums[idx] = test
                grid[x][y] = test
                solve(idx+1)
                nums[idx] = 0
                grid[x][y] = 0



grid = []
for x in range(n*n):
    row = []
    for y in range(n*n):
        row.append(nums[x*n*n+y])
    grid.append(row)

print("Solutions:")
solve(0)

