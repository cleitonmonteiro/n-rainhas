#include <iostream>
#include <string> 
using namespace std;

int n;

void clausulas_linhas() {
    for (int linha = 1; linha <= n; linha++) {
        int num_inicial_linha = (n * (linha - 1)) + 1;
        int num_final_linha = num_inicial_linha + n - 1;

        for (int i = num_inicial_linha; i <= num_final_linha; i++) {
            cout << i << " ";
        }
        cout << "0\n";

        for (int i = num_inicial_linha; i <= num_final_linha; i++) {
            for (int k = i+1; k <= num_final_linha; k++) {
                cout << -i << " " << -k << " 0\n";
            }
        }
    }
}

void clausulas_colunas() {
    for (int coluna = 1; coluna <= n; coluna++) {
        for (int i = coluna; i < n*n + 1; i+=n) {
            cout << i << " ";
        }
        cout << "0\n";
        
        for (int i = coluna; i < n*n + 1; i+=n) {
            for(int k = i+n; k < n*n + 1; k+=n) {
                cout << -i << " " << -k << " 0\n";
            }            
        }
    }    
}

void clausulas_diagonais_primarias() {
    int f = n*n - (n + 1);
    
    for (int i = 1; i <= f; i++) {
        if (i % n == 0) continue;

        int prox = i + n+1;
        
        int linha_atual = i/n;
        if (linha_atual % n) linha_atual++;
        
        int coluna_atual = i%n;
        if (coluna_atual == 0) coluna_atual = n;

        linha_atual++;
        coluna_atual++;
        while (linha_atual <= n && coluna_atual <= n) {
            cout << -i << " " << -prox << " 0\n";
            prox += (n+1);
            linha_atual++;
            coluna_atual++;
        }
    }
    
}

void clausulas_diagonais_secundarias() {
    int numero = 1, aux , copy_numero, copy_linha, copy_coluna;
    
    for (int linha = 1; linha <= n; linha++) {
        for (int coluna = 1; coluna <= n; coluna++) {
            copy_numero = numero;
            copy_linha = linha;
            copy_coluna = coluna;
            aux = numero;
            
            while (copy_linha < n && copy_coluna > 1) {
                cout << -aux << " " << -(copy_numero+(n-1)) << " 0\n";
                copy_numero += (n-1);
                copy_linha++;
                copy_coluna--;
            }
            numero++;
        }
    }
}

int main(int argc, char const *argv[]) {
    
    if (argc == 1) {
        cerr << "\n\t Use : " << argv[0] << " <numero-rainhas>\n\n";
        exit(-1);
    }
    n = stoi(argv[1]);

    clausulas_linhas();
    clausulas_colunas();
    clausulas_diagonais_primarias();
    clausulas_diagonais_secundarias();
    return 0;
}
