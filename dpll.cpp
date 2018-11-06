#include <iostream>
#include <algorithm>
#include <vector>
#include <time.h>
#include <stdio.h>

using namespace std;

vector<vector<int>> simplifica(vector<vector<int>> formula) {
    bool tem_clausula_unitaria = true;
    int atomo_sozinho, i;
    vector<int>::iterator it;
    
    while (tem_clausula_unitaria) {
        atomo_sozinho = 0;
        for (i=0; i < formula.size(); i++) {
            if (formula[i].size() == 1) {
                atomo_sozinho = formula[i][0];
                break;
            }
        }

        if (atomo_sozinho == 0) break;

        for (i=0; i < formula.size(); i++) {
            it = find(formula[i].begin(), formula[i].end(), atomo_sozinho);
            if (it != formula[i].end()) {
                formula.erase(formula.begin()+i);
                i--;
            }
        }

        for (i=0; i < formula.size(); i++) {
            it = find(formula[i].begin(), formula[i].end(), atomo_sozinho*-1);
            if (it != formula[i].end()) {
                formula[i].erase(it);
            }
        }
    }
    return formula;
}

bool dpll(vector<vector<int>> formula) {
    formula = simplifica(formula);
    
    if (formula.empty()) return true;
    
    for (int i=0; i < formula.size(); i++) {
        if (formula[i].size() == 0){
            return false;
        }
    }
    // usar heuristicas
    // loop ??
    int literal = formula[0][0];
    // cout << "Literal : " << literal << endl;
    formula.push_back({literal});
    
    if (dpll(formula)) return true;
    
    formula.pop_back();
    formula.push_back({-literal});
    
    if (dpll(formula)) return true;
    return false;
}


int main(int argc, char const *argv[]) {
    clock_t tempo_inicial, tempo_final;
    double tempo_execucao;

    tempo_inicial = clock();

    vector<vector<int>> formula;
    vector<int> clausula;    
    int literal;

    while (cin >> literal) {
        clausula.clear();
        while (literal) {
            clausula.push_back(literal);
            cin >> literal;
        }
        formula.push_back(clausula);
    }

    bool resultado = dpll(formula);

    tempo_final = clock();
    tempo_execucao = ((double)(tempo_final - tempo_inicial)) / CLOCKS_PER_SEC;

    if (resultado) {
        cout << "d\tSATISFIABLE\n";
    } else {
        cout << "d\tUNSATISFIABLE\n";
    }
    printf("d\tRUNTIME : %lf seconds\n", tempo_execucao);
    return 0;
}
