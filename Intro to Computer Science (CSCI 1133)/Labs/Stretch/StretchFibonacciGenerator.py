def fibonacci(n):
    if n == 0:
        return 0
    if n == 1:
        return 1
    fn = fibonacci(n-1) + fibonacci(n-2)
    return fn

for i in range (0, 20):
    print(fibonacci(i))
