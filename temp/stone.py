class Solution:
    dp = {}

    def sol(self, l, r, t, stones):
        if (l, r) in Solution.dp:
            return Solution.dp[(l, r)]
        if l > r:
            return 0
        if t == 0:
            diff = max(Solution.sol(self, l+1, r, 1, stones) + sum(
                stones[l+1:r]), Solution.sol(self, l, r-1, 1, stones) + sum(stones[l:r-1]))
        else:
            diff = min(Solution.sol(self, l+1, r, 0, stones) - sum(
                stones[l+1:r]), Solution.sol(self, l, r-1, 0, stones) - sum(stones[l:r-1]))
        Solution.dp[(l, r)] = diff
        return diff

    def stoneGameVII(self, stones):
        return Solution.sol(self, 0, len(stones), 0, stones)

print(Solution.stoneGameVII(Solution, [1,100,1]))
