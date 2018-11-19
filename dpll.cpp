#include <iostream>
#include <algorithm>
#include <vector>
#include <time.h>
#include <stdio.h>
#include <set>

using namespace std;
vector<int> valoracao;
int c=0;
// bool valoracao[36];

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

void add_unitarias(vector<vector<int>> formula) {
    for( int i=0; i < formula.size(); i++ ) {
        if(formula[i].size() == 1){
            valoracao.push_back(formula[i][0]);
        }
    }
}

vector<vector<int>> simplifica( vector<vector<int>> formula ) {
    int literal, i;

    while ( true ) {
        literal = get_literal_clausula_unitaria( formula );
        
        if ( literal == 0 ) break;

        valoracao.push_back(literal);
        c++;

        remover_clausulas_com_literal( literal, formula );
        remover_negacao_literal( literal, formula );
    }
    return formula;
}

void exibir_valoracao(){
    vector<int>::iterator it;
    vector<int> temp;
    for(auto l : valoracao){
        it = find( valoracao.begin(), valoracao.end(), -l );
        if( it == valoracao.end() && l > 0){
            cout << l << " ";
        }
    }
    cout << "0\n";
}

bool dpll( vector<vector<int>> formula ) {
    int aux = c;
    formula = simplifica(formula);
    
    if( formula.empty() ) return true;
    if( contem_clausula_vazia( formula) ) {
        while( c != aux ){
            valoracao.pop_back();
            c--;
        }
        return false;
    }
    int literal = formula[0][1];

    formula.push_back( { literal } );

    if( dpll( formula ) ) {
        return true;
    }
    
    formula.pop_back();
    formula.push_back( { -literal } );
    
    if( dpll( formula ) ){
        return true;
    }
    while( c != aux ){
        valoracao.pop_back();
        c--;
    }
    return false;
}


int main( int argc, char const *argv[] ) {
    clock_t tempo_inicial, tempo_final;
    double tempo_execucao;

    tempo_inicial = clock();

    vector<vector<int>> formula;
    vector<int> clausula;    
    int literal;

    while ( cin >> literal ) {
        clausula.clear();
        while ( literal ) {
            clausula.push_back( literal );
            cin >> literal;
        }
        formula.push_back( clausula );
    }

    bool resultado = dpll( formula );

    tempo_final = clock();
    tempo_execucao = ((double)(tempo_final - tempo_inicial)) / CLOCKS_PER_SEC;

    if ( resultado ) {
        cout << "d\tSATISFIABLE\n";
        exibir_valoracao();
    } else {
        cout << "d\tUNSATISFIABLE\n";
    }
    printf("d\tRUNTIME : %lf seconds\n", tempo_execucao);
    return 0;
}
