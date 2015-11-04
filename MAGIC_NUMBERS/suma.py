world = {"0":0,"1":1,"2":2,"3":3,"4":4,"5":5,"6":6,"7":7,"8":8,"9":9,"A":10,"B":11,"C":12,"D":13,"E":14,"F":15,"G":16,"H":17,"I":18,"J":19,"K":20,"L":21,"M":22,"N":23,"O":24,"P":25,"Q":26,"R":27,"S":28,"T":29,"U":30,"V":31,"W":32,"X":33,"Y":34,"Z":35}

def sumar(pNum1, pNum2, base):
    global world

    #Variables de apoyo para el algoritmo
    result = ""
    sumIndex = min(len(pNum1), len(pNum2))

    dig1 = 0
    dig2 = 0
    llevoDig = 0
    
    for i in range(sumIndex, 0, -1):
        dig1 = world[pNum1[i - 1]]
        dig2 = world[pNum2[i - 1]]

        suma = dig1 + dig2 + llevoDig

        if (suma) >= base:
            digDer = suma % base
            llevoDig = suma // base

            key = list(world.keys())[list(world.values()).index(digDer)]
            result = result + key
        else:
            llevoDig = 0
            key = list(world.keys())[list(world.values()).index(suma)]
            result = result + key

    
    if llevoDig != 0:
        key = list(world.keys())[list(world.values()).index(llevoDig)]
        result = result + key
    print (result[::-1])


"""
    *Esta función suma números en cualquier base
"""
#Entradas: pNum1, pNum2 (ambos deben ser hileras)
#          base (entero)
#Restricción: El largo de pNum1 debe ser mayor a pNum2
def sumar1(pNum1, pNum2, base):
    global world;

    result = ""
    sumIndex = max(len(pNum1), len(pNum2))
    mayor = pNum1 if len(pNum1) > len(pNum2) else pNum2
    menor = pNum1 if len(pNum1) < len(pNum2) else pNum2

    dig1 = 0
    dig2 = 0
    llevoDig = 0

    for i in range (sumIndex, 0, -1):
        dig1 = world[mayor[-1:]]
        mayor = mayor[:-1]
        dig2 = 0
        if len(menor) != 0:
            dig2 = world[menor[-1:]]
            menor = menor[:-1]

        suma = dig1 + dig2 + llevoDig
        if (suma) >= base:
            #digDer = suma % base
            #llevoDig = suma // base
            digDer, llevoDig = divmod(suma, base)
            
            key = list(world.keys())[list(world.values()).index(digDer)]
            result = result + key
        else:
            llevoDig = 0
            key = list(world.keys())[list(world.values()).index(suma)]
            result = result + key
    
    if llevoDig != 0:
        key = list(world.keys())[list(world.values()).index(llevoDig)]
        result = result + key
    print (result[::-1])
        

<<<<<<< HEAD

def mult(pNum1,pNum2, base):
    l=makelist(pNum1)
    l.reverse()
    x="0"
    num= sum(doMagic(l,[],0,base))
    for i in range(num):
        x=suma(pNum2,x,base)
    return x



def doMagic(list1,list2,cont,bo):
    global world
    if list1==[]:
        return list2
    numRed=(world[list1[0][0]]+(26*cuentaPalo(list1[0])))*(bo**cont)
    list2.append(numRed)
    return doMagic(list1[1:],list2,cont+1,bo)

def main():
    print(mult("A72B3","A72B3",16))

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
    
=======
def mayor (num1, num2):
    mayor = num1 if num1 > num2 else num2
    return mayor
        
>>>>>>> origin/master

if __name__ == "__main__":
   main()
