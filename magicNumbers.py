world = {"0":0,"1":1,"2":2,"3":3,"4":4,"5":5,"6":6,"7":7,"8":8,"9":9,"A":10,"B":11,"C":12,"D":13,"E":14,"F":15,"G":16,"H":17,"I":18,"J":19,"K":20,"L":21,"M":22,"N":23,"O":24,"P":25,"Q":26,"R":27,"S":28,"T":29,"U":30,"V":31,"W":32,"X":33,"Y":34,"Z":35,"*":26}


def main():
    l=makelist("24F")
    l.reverse()
    print(doMagic2(l,[],0,16,10))




def magicNumbers(num,bo,bd):
    l1=makelist(num)

    
def doMagic2(list1,list2,cont,bo,bd):
    global world
    if list1==[]:
        return list2
    x=(bo**cont)-(bd**cont)
    numRed=(world[list1[0][0]]+(26*cuentaPalo(list1[0])))*x
    list2.append(numRed)
    return doMagic2(list1[1:],list2,cont+1,bo,bd)

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
