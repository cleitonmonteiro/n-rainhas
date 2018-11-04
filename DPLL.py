from copy import deepcopy

def dpll_algoritimo(formula):
    formula_invertida = simplifica(formula)
    if(formula_invertida):
        return True
    elif([] in formula_invertida):
        return False
    
    literal = []
    for i in formula_invertida:
        if(i):
            literal.append(i[0])

    auxformula1 = deepcopy(formula_invertida)
    auxformula2 = deepcopy(formula_invertida)
    auxformula1.append(literal)
    literal2 = ([literal[0]*(-1)])
    auxformula2.append(literal2)
    if(dpll_algoritimo(auxformula1)):
        return True
    elif(dpll_algoritimo(auxformula2)):
        return True
    else:
        return False

    

def simplifica(formula):
    tem_clausula_unitaria = True
    while(tem_clausula_unitaria):
        atomo_sozinho = None
        for i in formula:
            if(len(i) == 1):
                atomo_sozinho = i[0]
        if(atomo_sozinho == None):
            tem_clausula_unitaria=False
            continue
        for i,j in enumerate(formula):
            if(atomo_sozinho in j):
                del(formula[i])
        for i,j in enumerate(formula):
            if(atomo_sozinho*(-1) in j):
                formula[i].remove(atomo_sozinho*(-1))
    return formula

def main():
    formula = []
    with open("entradaDPLL.txt","r") as  arq:
        for i in arq.readlines():
            formula.append([int(j) for j in i.split(" ")])
    print(formula)
    print(dpll_algoritimo(formula))        
    

if __name__ == '__main__':
    main()
        

