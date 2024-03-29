func minimumAddedCoins(coins []int, target int) int {
    slices.Sort(coins)
s, i : = 1, 0
ans : = 0
    for s <= target {
    if i < len(coins) && coins[i] <= s {
            s += coins[i]
            i ++
        } else {
            s *= 2
            ans++
        }
    }
    return ans
}