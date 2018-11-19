#include <iostream>
#include <algorithm>
#include <vector>
#include <time.h>
#include <stdio.h>
#include <set>

using namespace std;
vector<int> valoracao;

int get_literal_clausula_unitaria( vector<vector<int>> formula ) {
    int literal = 0;
    
    for( int i=0; i < formula.size(); i++ ) {
        if( formula[i].size() == 1 ) {
            literal = formula[i][0];
            break;
        }
    }
    return literal;
}

void remover_clausulas_com_literal( int literal, vector<vector<int>> &formula ) {
    vector<int>::iterator it;
    
    for( int i=0; i < formula.size(); i++ ) {
        it = find( formula[i].begin(), formula[i].end(), literal );
        if( it != formula[i].end() ) {
            formula.erase(formula.begin()+i);
            i--;
        }
    }
}

void remover_negacao_literal( int literal, vector<vector<int>> &formula ) {
    vector<int>::iterator it;

    for( int i=0; i < formula.size(); i++) {
        it = find( formula[i].begin(), formula[i].end(), -literal );
        
        if( it != formula[i].end() ) {
            formula[i].erase(it);
        }
    }
}

bool contem_clausula_vazia( vector<vector<int>> formula ) {
    for( int i=0; i < formula.size(); i++ ) {
        if ( formula[i].empty() ){
            return true;
        }
    }
    return false;
}

vector<vector<int>> simplifica( vector<vector<int>> formula ) {
    int literal, i;

    while ( true ) {
        literal = get_literal_clausula_unitaria( formula );
        
        if ( literal == 0 ) break;

        valoracao.push_back(literal);

        remover_clausulas_com_literal( literal, formula );
        remover_negacao_literal( literal, formula );
    }
    return formula;
}

void sat(){
    vector<int>::iterator it;
    vector<int> temp;
    for(int i=1; i <= valoracao.size(); i++){
        it = find( valoracao.begin(), valoracao.end(), -i );
        if( it == valoracao.end()){
            temp.push_back(i);
        }else {
            temp.push_back(-i);
        }
    }
    string arq = "valoracao.txt";
    FILE *f = fopen(arq.c_str(), "w");
    for(int i=0; i< temp.size(); i++){
        fprintf(f, "%i ", temp[i]);
    }
    fprintf(f, "0\n");
    fclose(f);
}

void unsat(){
    FILE *f = fopen("valoracao.txt", "w");
    fprintf(f, "UNSAT\n");
    fclose(f);
}

bool dpll( vector<vector<int>> formula ) {
    int temp = valoracao.size();

    formula = simplifica(formula);
    
    if( formula.empty() ) return true;
    if( contem_clausula_vazia( formula) ) {
        valoracao.erase(valoracao.begin()+temp, valoracao.end());
        return false;
    }
    int literal = formula[0][0];

    if(formula[0].size() > 1){
        literal = formula[0][1];
    }

    formula.push_back( { literal } );

    if( dpll( formula ) ) {
        return true;
    }
    
    formula.pop_back();
    formula.push_back( { -literal } );
    
    if( dpll( formula ) ){
        return true;
    }
    valoracao.erase(valoracao.begin()+temp, valoracao.end());
    return false;
}

vector<vector<int>> read_cnf(){
    vector<vector<int>> formula;
    vector<int> clausula;
    int literal;
    string temp;
    getline(cin, temp);
    while (cin >> literal) {
        clausula.clear();
        while ( literal != 0) {
            clausula.push_back( literal );
            cin >> literal;
        }
        formula.push_back( clausula );
    }
    return formula;
}

int main( int argc, char const *argv[] ) {

    clock_t tempo_inicial, tempo_final;
    double tempo_execucao;

    cout << "d\tLendo clausulas...\n";
    vector<vector<int>> formula = read_cnf();

    cout << "d\tIniciando DPLL...\n";
    tempo_inicial = clock();
    bool resultado = dpll( formula );
    tempo_final = clock();
    
    tempo_execucao = ((double)(tempo_final - tempo_inicial)) / CLOCKS_PER_SEC;

    if ( resultado ) {
        cout << "d\tSATISFIABLE\n";
        sat();
    } else {
        cout << "d\tUNSATISFIABLE\n";
        unsat();
    }
    printf("d\tRUNTIME DPLL: %lf seconds\n", tempo_execucao);
    return 0;
}
