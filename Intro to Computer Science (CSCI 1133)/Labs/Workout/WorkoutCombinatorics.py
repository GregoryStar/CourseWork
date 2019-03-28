def choose(n, k):
    if (k == 0) | (k == n):
        return 1
    else:
        x = choose(n - 1, k - 1) + choose(n - 1, k)
        return x

print(choose(52, 5))
