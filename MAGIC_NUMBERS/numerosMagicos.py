#FUNCIÓN PARA LA GENERACIÓN DEL MUNDO SEGÚN UNA BASE
def genWorld(base):
    world = {}
    i = 0
    j = 1
    h = 1
    while i < base:
        if i < 10:
            world[str(chr(48 + i))] = i
        else:
            if j % 27 == 0:
                h += 1
                j = 1
            for x in range(h):
                world[str(chr(65 + j - 1))+("*" * (h - 1))] = i
            j += 1
        
        i += 1
    return world

#FUNCIÓN PARA LA GENERACIÓN DE LOS NÚMEROS MÁGICOS
def doMagic(list1, list2, cont, bo, bd):
    if list1 == []:
        return list2
    x = (bo**cont) - (bd**cont)
    numRes = mult(x, list1[0], bo, bd)
    list2.append(numRes)
    return doMagic(list1[1:], list2, cont + 1, bo, bd)

#FUNCIÓN PARA LA SUMA DE DOS NÚMEROS EN CUALQUIER BASE
def sumar(pNum1, pNum2, base):
    result = ""
    sumIndex = max(len(pNum1), len(pNum2))
    mayor = pNum1 if len(pNum1) >= len(pNum2) else pNum2
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
    return result[::-1]

#FUNCIÓN PARA MULTIPLICAR UN NÚMERO DECIMAL Y UN NÚMERO EN UNA BASE DADA  
def mult(pNum1, pNum2, baseOrigen, baseDestino):
    dictionary = genWorld(baseOrigen) if pNum1 >= 0 else world #world se generó de la base destino
    value = dictionary[pNum2]
    multRes = abs(value * pNum1) # abs(x) -> por si se está convirtiendo de una base menor a una mayor
    res = ""

    while multRes > baseDestino:
        dig = multRes % baseDestino
        res += str(list(dictionary.keys())[list(dictionary.values()).index(dig)])
        multRes = multRes // baseDestino
    res += str(list(dictionary.keys())[list(dictionary.values()).index(multRes)])
    return res[::-1]

    


""" FUNCIÓN MAIN DEL PROGRAMA """

def main():
    numeroActual = "24F"
    baseOrigen = 16
    baseDestino = 3

    global world
    world = genWorld(baseDestino)

    listNum = list(numeroActual)[::-1]
    print(doMagic(listNum, [], 0, baseOrigen, baseDestino))

"""
    listNum = list(numeroActual)[::-1] # [::-1] -> voltear la lista
    listMagic = doMagic(listNum, [], 0, baseOrigen, baseDestino)

    print(sumar(numeroActual, str(sum(listMagic)), baseDestino))
 """

if __name__ == "__main__":
    main()
