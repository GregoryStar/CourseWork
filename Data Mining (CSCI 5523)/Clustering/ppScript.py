from html.parser import HTMLParser
from html.entities import name2codepoint
from collections import Counter
import math

articleDataList = []  
#PORTERS'S STEMMING ALGORITHM CLASS; TAKEN FROM THE LINK PROVIDED IN THE ASSIGNMENT DESCRIPTION
#Comments have been removed so that this class takes up less space
class PorterStemmer:

    def __init__(self):
        self.b = ""
        self.k = 0
        self.k0 = 0
        self.j = 0

    def cons(self, i):
        if self.b[i] == 'a' or self.b[i] == 'e' or self.b[i] == 'i' or self.b[i] == 'o' or self.b[i] == 'u':
            return 0
        if self.b[i] == 'y':
            if i == self.k0:
                return 1
            else:
                return (not self.cons(i - 1))
        return 1

    def m(self):
        n = 0
        i = self.k0
        while 1:
            if i > self.j:
                return n
            if not self.cons(i):
                break
            i = i + 1
        i = i + 1
        while 1:
            while 1:
                if i > self.j:
                    return n
                if self.cons(i):
                    break
                i = i + 1
            i = i + 1
            n = n + 1
            while 1:
                if i > self.j:
                    return n
                if not self.cons(i):
                    break
                i = i + 1
            i = i + 1

    def vowelinstem(self):
        for i in range(self.k0, self.j + 1):
            if not self.cons(i):
                return 1
        return 0

    def doublec(self, j):
        if j < (self.k0 + 1):
            return 0
        if (self.b[j] != self.b[j-1]):
            return 0
        return self.cons(j)

    def cvc(self, i):
        if i < (self.k0 + 2) or not self.cons(i) or self.cons(i-1) or not self.cons(i-2):
            return 0
        ch = self.b[i]
        if ch == 'w' or ch == 'x' or ch == 'y':
            return 0
        return 1

    def ends(self, s):
        length = len(s)
        if s[length - 1] != self.b[self.k]:
            return 0
        if length > (self.k - self.k0 + 1):
            return 0
        if self.b[self.k-length+1:self.k+1] != s:
            return 0
        self.j = self.k - length
        return 1

    def setto(self, s):
        length = len(s)
        self.b = self.b[:self.j+1] + s + self.b[self.j+length+1:]
        self.k = self.j + length

    def r(self, s):
        if self.m() > 0:
            self.setto(s)

    def step1ab(self):
        if self.b[self.k] == 's':
            if self.ends("sses"):
                self.k = self.k - 2
            elif self.ends("ies"):
                self.setto("i")
            elif self.b[self.k - 1] != 's':
                self.k = self.k - 1
        if self.ends("eed"):
            if self.m() > 0:
                self.k = self.k - 1
        elif (self.ends("ed") or self.ends("ing")) and self.vowelinstem():
            self.k = self.j
            if self.ends("at"):   self.setto("ate")
            elif self.ends("bl"): self.setto("ble")
            elif self.ends("iz"): self.setto("ize")
            elif self.doublec(self.k):
                self.k = self.k - 1
                ch = self.b[self.k]
                if ch == 'l' or ch == 's' or ch == 'z':
                    self.k = self.k + 1
            elif (self.m() == 1 and self.cvc(self.k)):
                self.setto("e")

    def step1c(self):
        if (self.ends("y") and self.vowelinstem()):
            self.b = self.b[:self.k] + 'i' + self.b[self.k+1:]

    def step2(self):
        if self.b[self.k - 1] == 'a':
            if self.ends("ational"):   self.r("ate")
            elif self.ends("tional"):  self.r("tion")
        elif self.b[self.k - 1] == 'c':
            if self.ends("enci"):      self.r("ence")
            elif self.ends("anci"):    self.r("ance")
        elif self.b[self.k - 1] == 'e':
            if self.ends("izer"):      self.r("ize")
        elif self.b[self.k - 1] == 'l':
            if self.ends("bli"):       self.r("ble")
            elif self.ends("alli"):    self.r("al")
            elif self.ends("entli"):   self.r("ent")
            elif self.ends("eli"):     self.r("e")
            elif self.ends("ousli"):   self.r("ous")
        elif self.b[self.k - 1] == 'o':
            if self.ends("ization"):   self.r("ize")
            elif self.ends("ation"):   self.r("ate")
            elif self.ends("ator"):    self.r("ate")
        elif self.b[self.k - 1] == 's':
            if self.ends("alism"):     self.r("al")
            elif self.ends("iveness"): self.r("ive")
            elif self.ends("fulness"): self.r("ful")
            elif self.ends("ousness"): self.r("ous")
        elif self.b[self.k - 1] == 't':
            if self.ends("aliti"):     self.r("al")
            elif self.ends("iviti"):   self.r("ive")
            elif self.ends("biliti"):  self.r("ble")
        elif self.b[self.k - 1] == 'g':
            if self.ends("logi"):      self.r("log")

    def step3(self):
        if self.b[self.k] == 'e':
            if self.ends("icate"):     self.r("ic")
            elif self.ends("ative"):   self.r("")
            elif self.ends("alize"):   self.r("al")
        elif self.b[self.k] == 'i':
            if self.ends("iciti"):     self.r("ic")
        elif self.b[self.k] == 'l':
            if self.ends("ical"):      self.r("ic")
            elif self.ends("ful"):     self.r("")
        elif self.b[self.k] == 's':
            if self.ends("ness"):      self.r("")

    def step4(self):
        if self.b[self.k - 1] == 'a':
            if self.ends("al"): pass
            else: return
        elif self.b[self.k - 1] == 'c':
            if self.ends("ance"): pass
            elif self.ends("ence"): pass
            else: return
        elif self.b[self.k - 1] == 'e':
            if self.ends("er"): pass
            else: return
        elif self.b[self.k - 1] == 'i':
            if self.ends("ic"): pass
            else: return
        elif self.b[self.k - 1] == 'l':
            if self.ends("able"): pass
            elif self.ends("ible"): pass
            else: return
        elif self.b[self.k - 1] == 'n':
            if self.ends("ant"): pass
            elif self.ends("ement"): pass
            elif self.ends("ment"): pass
            elif self.ends("ent"): pass
            else: return
        elif self.b[self.k - 1] == 'o':
            if self.ends("ion") and (self.b[self.j] == 's' or self.b[self.j] == 't'): pass
            elif self.ends("ou"): pass
            else: return
        elif self.b[self.k - 1] == 's':
            if self.ends("ism"): pass
            else: return
        elif self.b[self.k - 1] == 't':
            if self.ends("ate"): pass
            elif self.ends("iti"): pass
            else: return
        elif self.b[self.k - 1] == 'u':
            if self.ends("ous"): pass
            else: return
        elif self.b[self.k - 1] == 'v':
            if self.ends("ive"): pass
            else: return
        elif self.b[self.k - 1] == 'z':
            if self.ends("ize"): pass
            else: return
        else:
            return
        if self.m() > 1:
            self.k = self.j

    def step5(self):
        self.j = self.k
        if self.b[self.k] == 'e':
            a = self.m()
            if a > 1 or (a == 1 and not self.cvc(self.k-1)):
                self.k = self.k - 1
        if self.b[self.k] == 'l' and self.doublec(self.k) and self.m() > 1:
            self.k = self.k -1

    def stem(self, p, i, j):
        self.b = p
        self.k = j
        self.k0 = i
        if self.k <= self.k0 + 1:
            return self.b

        self.step1ab()
        self.step1c()
        self.step2()
        self.step3()
        self.step4()
        self.step5()
        return self.b[self.k0:self.k+1]

#############################################################################################################################
#MY CODE STARTS HERE
#Here I define a couple of classes to make the processing of the data easier
#This is an HTML parsing class which splits the data into separate articles and extracts the body tags:
class InitialParser(HTMLParser):
    def __init__(self):
        HTMLParser.__init__(self)
        self.articleCount = 0
        self.checkingTopicList = False
        self.inTagOfInterest = False
        self.currentArticleData = []
        self.currentLine = ""
        self.saveCurrentArticle = False
        self.currentTopic = ""
    
    def handle_starttag(self, tag, attrs):
        if(tag == "reuters"):
            self.saveCurrentArticle = False
            self.currentArticleData = []
            self.currentArticleData.append(self.currentLine)
            if(attrs[0][1] == "YES"):
                self.inTagOfInterest = True
        elif(self.inTagOfInterest and tag == "topics"):
            self.checkingTopicList = True

    def handle_endtag(self, tag):
        if(self.checkingTopicList == True):
            self.checkingTopicList = False
            self.inTagOfInterest = False
        if(tag == "reuters"):
            if(self.saveCurrentArticle):
                #Save article, along with its topic, to RAM (this article has one and only one topic)
                articleList.append((self.currentTopic, self.currentArticleData))
                self.articleCount += 1
            currentArticleData = []
            self.SaveCurrentArticle = False

    def handle_data(self, data):
        if(self.checkingTopicList):
            topicList = data.split('-')
            if len(topicList) == 1:
                self.currentTopic = topicList[0]
                self.saveCurrentArticle = True

    def readFile(self, file):
        for line in file:
            self.currentLine = line
            self.currentArticleData.append(self.currentLine)
            self.feed(line)

############################################################################################################################
#This parser extracts important information from the already split articles
class SecondPassParser(HTMLParser):
    def __init__(self):
        HTMLParser.__init__(self)
        self.inBody = False
        self.bodyCount = 0
        self.currentArticleData = articleData()
        self.inTopic = False
        self.currentBody = ""
    
    def handle_starttag(self, tag, attrs):
        if tag == "reuters":
            for attr in attrs:
                if attr[0] == "newid":
                    self.currentArticleData.id = attr[1]
        if tag == "topics":
            self.inTopic = True
        if tag == "body":
            self.inBody = True
            self.bodyCount += 1

    def handle_endtag(self, tag):
        if tag == "body":
            self.inBody = False
        if tag == "topics":
            self.inTopic = False
            
    def handle_data(self, data):
        if self.inBody:
            self.currentBody += data
        if self.inTopic:
            self.currentArticleData.topic = data
            
    def readArticle(self, article):
        for line in article:
            self.feed(line)
        self.currentArticleData.body = self.currentBody
        self.currentBody = ""
        articleDataList.append(self.currentArticleData)
        self.currentArticleData = articleData()

###########################################################################################################################
#A simple struct for keeping data about an article
class articleData():
    def __init__(self):
        self.id = ""
        self.topic = ""
        self.body = ""

###########################################################################################################################
#Algorithmic logic starts here:

#Load the stoplist into memory        
stoplistFile = open("reuters21578/stoplist.txt")
tempStopList = stoplistFile.readlines()
stopList = set()
for line in tempStopList:
    splitLine = line.split(" ")
    for word in splitLine:
        stopList.add(word.rstrip())

articleList = []


#Load the article data into memory
parser = InitialParser()
for i in range (0, 20):
    fileName = "reuters21578/reut2-0"
    if(i < 10):
        fileName += "0"
    fileName += str(i) + ".sgm"
    currentFile = open(fileName, encoding="latin-1")
    articles = parser.readFile(currentFile)

#Take the topics of the articles and put them into a list
justTopics = []
for tup in articleList:
    justTopics.append(tup[0])

#Now get a count for the frequency of every topic
counts = Counter(justTopics)

#Get the 20 most common topics and add them to a set
top20TopicsTuple = counts.most_common(20)
top20TopicsSet = set()
for tup in top20TopicsTuple:
    top20TopicsSet.add(tup[0])


#Only retain articles that are part of the top 20 most frequent topics
filteredArticleList = []
for article in articleList:
    if article[0] in top20TopicsSet:
        filteredArticleList.append(article[1])

#This piece of code here should load the articles and their data into article
#data structs. This will make processing conceptually simpler.         
parser = SecondPassParser()
for article in filteredArticleList:
    parser.readArticle(article)

#Only retain articles that are part of the top 20 most frequent topics
tempDataList = []
for article in articleDataList:
    if article.topic in top20TopicsSet:
        tempDataList.append(article)
articleDataList = tempDataList

#The id, topic, and body of each relevant article is now in articleDataList.
#The body of each member of articleDataList must now be cleaned up according
#To the rules provided.

#Steps 1 through 7 of the text processing step
for item in articleDataList:
    newBody = item.body

    #String non-ascii characters
    newBody = "".join(char for char in newBody if 0 < ord(char) <= 127)

    #Replace &lt and &ge with < and > respectively
    newBody = newBody.replace("&lt", "<")
    newBody = newBody.replace("&ge", ">")

    #Make all characters lowercase
    newBody = newBody.lower()

    #Replace any non alphanumeric characters with space
    newBody = "".join(char if char.isalnum() else ' ' for char in newBody)

    #Split the text into tokens, using space as the delimiter
    #Also remove all empty tokens
    splitString = list(filter(None, newBody.split(" ")))

    #Filter out tokens that contain only digits
    newSplitString = []
    for string in splitString:
        if not string.isnumeric():
            newSplitString.append(string)
    splitString = newSplitString

    #Filter out tokens from the stop list
    newSplitString = []
    for string in splitString:
        if not string in stopList:
            newSplitString.append(string)
    splitString = newSplitString

    item.body = splitString


#Convert each word to its stem representation and also count frequencies
wordFreqs = {}
stemmer = PorterStemmer()
for item in articleDataList:
    for i in range(0, len(item.body)):
        word = item.body[i]
        word = stemmer.stem(word, 0, len(word) - 1)
        item.body[i] = word
        if word not in wordFreqs:
            wordFreqs[word] = 1
        else:
            wordFreqs[word] += 1

#Filter words that have a frequency less than 5 and the word reuter
for item in articleDataList:
    newBodyList = []
    for word in item.body:
        if wordFreqs[word] >= 5 and word != "reuter":
            newBodyList.append(word)
    item.body = newBodyList

remainingWordSet = set()
#Remove articles with empty bodies
newArticleDataList = []
for item in articleDataList:
    if len(item.body) > 0:
        newArticleDataList.append(item)
        for word in item.body:
            remainingWordSet.add(word)
articleDataList = newArticleDataList

#Obtain a sorted list of the remaining words
remainingWordList = list(remainingWordSet)
remainingWordList.sort()

#Create an index dictionary for the words
wordIndexDict = {}
for i in range (0, len(remainingWordList)):
    wordIndexDict[remainingWordList[i]] = i

#Now we will create five files:
# file 1: freq.csv
# file 2: sqrtfreq.csv
# file 3: log2freq.csv
# file 4: reuters21578.clabel
# file 5: reuters21578.class

# freq.csv:
freqFile = open("freq.csv", "w")
for article in articleDataList:
    #Obtain the vector magnitude
    vecSum = 0
    wordInArticleCount = {}
    for word in article.body:
        if word in wordInArticleCount:
            prevCount = wordInArticleCount[word]
            newCount = prevCount + 1
            vecSum -= prevCount ** 2
            vecSum += newCount ** 2
            wordInArticleCount[word] = newCount
        else:
            wordInArticleCount[word] = 1
            vecSum += 1
    magnitude = math.sqrt(vecSum)

        
    for word in wordInArticleCount:
        wordDim = wordIndexDict[word]
        currentLine = article.id + "," + str(wordDim) + "," + str(wordInArticleCount[word]/magnitude) + "\n"
        freqFile.write(currentLine)
freqFile.close()

# sqrtfreq.csv:
sqrtfreqFile = open("sqrtfreq.csv", "w")
for article in articleDataList:
    vecList = []
    vecSum = 0
    wordInArticleCount = {}
    uniqueWordList = []
    for word in article.body:
        if word in wordInArticleCount:
            wordInArticleCount[word] = wordInArticleCount[word] + 1
        else:
            wordInArticleCount[word] = 1
            uniqueWordList.append(word)
    for word in uniqueWordList:
        wordInArticleCount[word] = 1 + math.sqrt(wordInArticleCount[word])
        vecSum += wordInArticleCount[word] ** 2
    magnitude = math.sqrt(vecSum)
    
    for word in wordInArticleCount:
        wordDim = wordIndexDict[word]
        currentLine = article.id + "," + str(wordDim) + "," + str(wordInArticleCount[word]/magnitude) + "\n"
        sqrtfreqFile.write(currentLine)
sqrtfreqFile.close()

# log2freq.csv:
log2freqFile = open("log2freq.csv", "w")
for article in articleDataList:
    vecList = []
    vecSum = 0
    wordInArticleCount = {}
    uniqueWordList = []
    for word in article.body:
        if word in wordInArticleCount:
            wordInArticleCount[word] = wordInArticleCount[word] + 1
        else:
            wordInArticleCount[word] = 1
            uniqueWordList.append(word)
    for word in uniqueWordList:
        wordInArticleCount[word] = 1 + math.log(wordInArticleCount[word], 2)
        vecSum += wordInArticleCount[word] ** 2
    magnitude = math.sqrt(vecSum)
                   
    for word in wordInArticleCount:
        wordDim = wordIndexDict[word]
        currentLine = article.id + "," + str(wordDim) + "," + str(wordInArticleCount[word]/magnitude) + "\n"
        log2freqFile.write(currentLine)
log2freqFile.close()

#reuters21578.clabel
reuterLabels = open("reuters21578.clabel", "w")
for word in remainingWordList:
    reuterLabels.write(word + "\n")
reuterLabels.close()

#reuters21578.class
reuterClasses = open("reuters21578.class", "w")
for article in articleDataList:
    reuterClasses.write(article.id + "," + article.topic + "\n")
reuterClasses.close()

#Here, the pre-processing should be done! We've created three different frequency
#representations, and also a class file and a label file.

print("Number of articles remaining: ", len(articleDataList))
print("Number of unique words remaining: ", len(remainingWordList))





