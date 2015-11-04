world = {"0":0,"1":1,"2":2,"3":3,"4":4,"5":5,"6":6,"7":7,"8":8,"9":9,"A":10,"B":11,"C":12,"D":13,"E":14,"F":15,"G":16,"H":17,"I":18,"J":19,"K":20,"L":21,"M":22,"N":23,"O":24,"P":25,"Q":26,"R":27,"S":28,"T":29,"U":30,"V":31,"W":32,"X":33,"Y":34,"Z":35,"*":26}


def main():
    """
    l= list(genWorld(100).items())
    l.sort()
    print(l)
    """
    print(magicNumbers("24F", 16, 10))


def magicNumbers(num,bo,bd):
    l1=makelist(num)
    return doMagic2(l1, [], 0, bo, bd)

    
def doMagic2(list1,list2,cont,bo,bd):
    global world
    if list1==[]:
        return list2
    x = (bo**cont) - (bd**cont)
    print (26 * cuentaPalo(list1[0]))
    #numRed = (world[list1[0][0]] + (26 * cuentaPalo(list1[0]))) * x
    #list2.append(numRed)
    return doMagic2(list1[1:], list2, cont+1, bo, bd)


def genWorld(base):
    world={}
    i=0
    j=1
    h=1
    while i<base:
        if i<10:
            world[str(chr(48+i))]=i
        else:
            if j % 27 == 0:
                h+=1
                j=1
            for x in range(h):
                world[str(chr(65+j-1))+("*"*(h-1))]=i
            j+=1
        
        i+=1
    return world
        
        
        

def cuentaPalo(string):
    x=0
    for i in range(len(string)):
        if string[i]=="*":
            x=x+1
    return x
    
def makelist(string):
    l=[]
    listNum=list(string)
    for i in range(len(string)):
        if listNum[i]=="*":
            l[len(l)-1]=l[len(l)-1]+listNum[i]
        else:
            l.append(listNum[i])
    return l
    


if __name__ == "__main__":
   main()
