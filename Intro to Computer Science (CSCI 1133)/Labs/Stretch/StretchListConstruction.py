word = "Place holder"
words = []
while word != "":
    word = input("Enter a word: ")
    if word != "":
        ch = word[0]
        i = 0
        for c in word:
            if ch == c:
                i += 1
        if i > 1:
            words.append(word)
for x in words:
    print(x)
