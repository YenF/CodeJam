"""

String cleaning
===============

Your spy, Beta Rabbit, has managed to infiltrate a lab of mad scientists who are turning rabbits into zombies. He sends a text transmission to you, but it is intercepted by a pirate, who jumbles the message by repeatedly inserting the same word into the text some number of times. At each step, he might have inserted the word anywhere, including at the beginning or end, or even into a copy of the word he inserted in a previous step. By offering the pirate a dubloon, you get him to tell you what that word was. A few bottles of rum later, he also tells you that the original text was the shortest possible string formed by repeated removals of that word, and that the text was actually the lexicographically earliest string from all the possible shortest candidates. Using this information, can you work out what message your spy originally sent?

For example, if the final chunk of text was "lolol," and the inserted word was "lol," the shortest possible strings are "ol" (remove "lol" from the beginning) and "lo" (remove "lol" from the end). The original text therefore must have been "lo," the lexicographically earliest string.

Write a function called answer(chunk, word) that returns the shortest, lexicographically earliest string that can be formed by removing occurrences of word from chunk. Keep in mind that the occurrences may be nested, and that removing one occurrence might result in another. For example, removing "ab" from "aabb" results in another "ab" that was not originally present. Also keep in mind that your spy's original message might have been an empty string.

chunk and word will only consist of lowercase letters [a-z].
chunk will have no more than 20 characters.
word will have at least one character, and no more than the number of characters in chunk.

Languages
=========

To provide a Python solution, edit solution.py
To provide a Java solution, edit solution.java

Test cases
==========

Inputs:
    (string) chunk = "lololololo"
    (string) word = "lol"
Output:
    (string) "looo"

Inputs:
    (string) chunk = "goodgooogoogfogoood"
    (string) word = "goo"
Output:
    (string) "dogfood"


"""

strList = []
isSeen = set()
finalAns = ""
def answer(chunk, word):
    strList[:] = []
    global isSeen
    isSeen = set()
    global finalAns
    finalAns = chunk
    generateStrList(chunk, word)
    # strList.sort(key = lambda item: (len(item), item))
    # return strList[0]
    return finalAns

def generateStrList(chunk, word):
    global finalAns
    # Prune
    if chunk in isSeen:
        return
    isSeen.add(chunk)

    frontwardWord = chunk

    wordIndex = 0
    IsRemoved = True
    while IsRemoved:
        #Remove words that we doesn't need to care about remove order
        (chunk, IsRemoved) = removeNonNestWord(chunk, word)
    firstTimeFind = True
    while True:
        wordIndex = chunk.find(word, wordIndex)
        # print wordIndex
        if wordIndex == -1:
            if firstTimeFind is True:
                # compare with existing answer
                strList.append(frontwardWord)
                if len(finalAns) > len(chunk):
                    finalAns = chunk
                elif len(finalAns) == len(chunk):
                    finalAns = min(finalAns, chunk)
            return
        frontwardWord = chunk[:wordIndex] + chunk[wordIndex + len(word):]
        wordIndex += 1
        firstTimeFind = False
        generateStrList(frontwardWord, word)

def removeNonNestWord(chunk, word):
    prevWordIndex = -1
    currentWordIndex = 0
    afterWordIndex = 0
    IsRemoved = False
    while True:
        currentWordIndex = chunk.find(word, prevWordIndex+1)
        if currentWordIndex == -1:
            return chunk, IsRemoved
        afterWordIndex = chunk.find(word, currentWordIndex+1)

        # at the end of the string
        if afterWordIndex == -1:
            # if word nested, -1 is at the start place
            if prevWordIndex == -1 or currentWordIndex - prevWordIndex >= len(word):
                chunk = chunk[:currentWordIndex] + chunk[currentWordIndex + len(word):]
            return chunk, IsRemoved

        # when next token is > len from previous token
        if afterWordIndex - currentWordIndex >= len(word):
            #if word nested, -1 is at the start place
            if prevWordIndex == -1 or currentWordIndex - prevWordIndex >= len(word):
                chunk = chunk[:currentWordIndex] + chunk[currentWordIndex + len(word):]
        prevWordIndex = currentWordIndex


print(answer("goodgooogoogfogoood", "goo"))
print(answer("lololololo", "lol"))
print(answer("llolol", "lol"))
print(answer("lolol", "lol"))
print(answer("lllololol", "lol"))
print(answer("sbblobblobbam", "bblobb"))
print(answer("", "lol"))
print(answer("aaaaaaa", "aaa"))