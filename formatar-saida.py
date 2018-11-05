from sys import argv

try:
    filename = argv[1]
except:
    print("\n\tuse : python3 %s <arquivo>\n" % argv[0])
    exit(-1)

with open(filename) as arq:
    separador = '+'+'-'*20+'+'+'-'*20+'+'
    print(separador)
    print('| %sNUMERO LINHA | POSICAO RAINHA %s|'%(' '*6, ' '*4))
    print(separador)
    arq = arq.read().split()[:-1]
    n = int(len(arq)**.5)
    linha = 1
    for v in arq:
        if (v[0] != '-'):
            print('| {0:18} | {1:18}|'.format(linha, str(n if not int(v)%n else int(v)%n)))
            linha += 1
    print(separador)
