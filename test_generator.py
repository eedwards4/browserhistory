# Created by Ethan Edwards on 5/18/2023
# ethanedwards.me
# Test-case generator for highest-hand problem

# Imports
import random

# Vardef
domains = [".com", ".net", ".org", ".me", ".io", ".gov", ".edu", ".biz", ".info", ".co", ".tv", ".us", ".ca", ".uk",
           ".au", ".de", ".jp", ".fr", ".ru", ".ch", ".it", ".nl", ".se", ".no", ".es", ".mil", ".ed", ".ac", ".kr"]


def main():
    tmpinput = input("Enter name of file to write to [this will overwrite any existing file]: ")
    wfile = open(tmpinput, "w")
    numcases = int(input("Enter number of test cases to generate: "))

    for i in range(numcases):
        wfile.write("BrowserHistory ")
        print("BrowserHistory ")
        # Generate random site urls
        for j in range(random.randint(1, 100)):
            url = ""
            # Pick random chars for url
            for k in range(random.randint(1, 25)):
                url += chr(random.randint(97, 122))
            # Pick a domain
            dnum = random.randint(0, domains.__len__() - 1)
            domain = domains[dnum]
            url += domain
            wfile.write(url)
            print(url)
            # Randomly decide to visit or browseUntil (skewed towards visit)
            nextThing = random.randint(0, 100)
            if nextThing <= 80:
                wfile.write(" visit ")
                print(" visit ")
            elif nextThing > 80:
                wfile.write(" browseUntil " + str(random.randint(1, 60)) + " ")
                print(" browseUntil " + str(random.randint(1, 60)) + " ")
        wfile.write(" endOfHistory\n")
        print(" endOfHistory\n")


main()
