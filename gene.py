import random

def creartxt():
    archi=open('datos.txt','w')
    archi.close()

def grabartxt(c):
    archi=open('datos.txt','a')
    archi.write(geneGenerador(c))
    archi.close()

def geneGenerador(c):
    x=["A","C","G","T"]
    R=""
    for i in range(c):
        R=x[random.randint(0, 3)]+R
    return R

def test(c):
    creartxt()
    grabartxt(c)


test(1050)
