from os import popen 
import time
Nrainhas =  int(input("numero de rainhas: "))
if(Nrainhas <= 0):
    print("problema")
    exit(1)
elif(Nrainhas >= 1 and Nrainhas <= 3):
    print("unsat")
    exit(1)
else:
    popen("g++ gerador-clausulas.cpp -o gerador")
    popen("g++ dpll.cpp -o dpll")
    time.sleep(3)
    aux = "./gerador " + str(Nrainhas)
    popen(aux)
    time.sleep(3)
    aux = "./dpll <" + str(Nrainhas) +"-rainhas.cnf" 
    print(popen(aux).read())


    import math
    texto = ""
    with open("valoracao.txt","r") as arq:
        texto = arq.read()

    rainhas = texto.split(" ")
    import matplotlib.pyplot as plt
    nrainhas = math.sqrt(len(rainhas))
    nrainhas = int(nrainhas)
    for i in range(nrainhas):
            #[x,x],[y,y] 
        plt.plot([i,i],[0,nrainhas],color="black")
        plt.plot([0,nrainhas],[i,i],color="black")

    for i in rainhas:
        i = int(i)-1
        if(i > 0):
            x = i%nrainhas
            y = i//nrainhas
            plt.plot([x+0.5],[y+0.5],"ro",color="blue")
    plt.show()