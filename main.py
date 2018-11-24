from os import popen 
import time

n_rainhas =  int(input("Número de rainhas: "))

if(n_rainhas <= 0):
    print("Número inválido, informe um número maior que 0!")
    exit(1)
else:
    print("Compilando arquivos gerador-clausulas.cpp e dpll.cpp ...")
    popen("g++ gerador-clausulas.cpp -o gerador")
    popen("g++ dpll.cpp -o dpll")
    time.sleep(3)
    print("Gerando arquivo " + str(n_rainhas) +"-rainhas.cnf ...")
    aux = "./gerador " + str(n_rainhas)
    popen(aux)
    time.sleep(3)
    print("Executando DPLL com ", str(n_rainhas) +"-rainhas.cnf")
    aux = "./dpll <" + str(n_rainhas) +"-rainhas.cnf" 
    print(popen(aux).read())

    # nao exibir tabuleiro
    if (n_rainhas <= 3):
        exit(0)
    # exibindo o tabuleiro com valoracao
    import math
    texto = ""
    with open("valoracao.txt","r") as arq:
        texto = arq.read()

    rainhas = texto.split(" ")
    import matplotlib.pyplot as plt
    
    nrainhas = math.sqrt(len(rainhas))
    nrainhas = int(nrainhas)
    
    for i in range(nrainhas):
        plt.plot([i,i],[0,nrainhas],color="black")
        plt.plot([0,nrainhas],[i,i],color="black")

    for i in rainhas:
        i = int(i)-1
        if(i > 0):
            x = i%nrainhas
            y = i//nrainhas
            plt.plot([x+0.5],[y+0.5],"ro",color="blue")
    plt.show()