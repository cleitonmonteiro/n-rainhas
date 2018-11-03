import math

n = 3#int()

def combinacao(n,p):
    return int(math.factorial(n)/(math.factorial(p) *math.factorial(n-p)))

def linha(numLinha):
    numInicioLinha = (n*(numLinha-1))+1
    numFinalLinha = numInicioLinha + n
    for k in range(numInicioLinha, numFinalLinha):
        print(k, end=' ')
    print('0')

    for k in range(numInicioLinha, numFinalLinha):
        for i in range(k+1, numFinalLinha):
            print(-k, -i, '0')

def linhas():
    for i in range(1, n+1):
        linha(i)

def coluna(numColuna):
    for i in range(numColuna, (n**2)+1, n):
        print(i, end=' ')
    print('0')

    for i in range(numColuna, (n**2)+1, n):
        for k in range(i+n, (n**2)+1, n):
            print(-i, -k, '0')

def colunas():
    for i in range(1, n+1):
        coluna(i)

def diagonaisPrimarias():
    final = n**2 - (n+1)

    for i in range(1, final+1):
        if (not i % n):
            continue
        
        prox = i+(n+1)
        
        linhaAtual = i/n
        if not linhaAtual % n:
            linhaAtual = int(linhaAtual) + 1
        
        colunaAtual = i % n
        if not colunaAtual:
            colunaAtual = n

        linhaAtual+=1
        colunaAtual+=1
        while(linhaAtual <= n and colunaAtual <= n):
            print(-i, -prox, '0')
            prox += (n+1)
            linhaAtual+=1
            colunaAtual+=1

def diagonaisSecundarias():
    def pegarDiagonal(linha, coluna, numero):
        aux = numero
        while(linha < n and coluna > 1):
            print(-aux, -(numero*(n+1)), '0')
            numero -= (n+1)
            linha -= 1
            coluna -= 1
    
    m = 1
    for l in range(1, n+1):
        for c in range(1, n+1):
            pegarDiagonal(l, c, m)
            m += 1

    

def numClausulasDiagonais():
    ret = 0
    
    for i in range(2, n):
        ret += combinacao(i, 2)
    ret *= 2
    ret += combinacao(n, 2)
    return ret

print('total:', numClausulasDiagonais())
# diagonaisPrimarias()
diagonaisSecundarias()

# print(combinacao(5, 2))

