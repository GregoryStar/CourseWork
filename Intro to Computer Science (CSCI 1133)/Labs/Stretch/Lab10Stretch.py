def convertToMorse(string):
    lettersToMorse = {'A' : "._", "B" : "_...", 'C' : "_._.", 'D' : "_..", 'E' : ".", 'F' : ".._.",
                      'G' : "__.",'H' : "....",'I' : "..",'J' : ".___",'K' : "_._",'L' : "._..",'M' : "__",
                      'N' : "_.",'O' : "___",'P' : ".__.",'Q' : "__._",'R' : "._.",'S' : "...",'T' : "_",
                      'U' : ".._",'V' : "..._", 'W' : ".__", 'X' : "_.._", 'Y' : "_.__", 'Z' : "__.."}
    string = string.upper()
    for ch in string:
        if ch != " ":
            print(lettersToMorse[ch])
        else:
            print()
phrase = input("enter a phrase: ")
convertToMorse(phrase)
