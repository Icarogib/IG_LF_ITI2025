#include <iostream>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <cmath>
#include <string>
#include <vector>

using namespace std;

void sort(vector<int> &simbPresentes, int contSimb[])
{
  int n = simbPresentes.size();

  for (int i = n ; i >= 0; i--) {
    
    bool flag = false;
    for (int j = n - 1; j > n - i; j--) {
      
      int letra = simbPresentes.at( j );
      int letra1 = simbPresentes.at( j - 1 );

      //cout << "vez: [" << i << "][" << j <<"] - contSimb[" << letra << "]: " << contSimb[letra] << " > contSimb[" << letra1 << "]: " << contSimb[letra1] << endl;

      if (contSimb[letra] > contSimb[letra1]) {
        swap(simbPresentes[j], simbPresentes[j-1]);
        flag = true;
      }
    }

    if (!flag)
      break;
  }
//  print(v, n);

}

int main()
{
  string input = "ICARO SALSICHA UFPB";
  cout << input << endl;
  
  // Contagem de cada letra em específico (em ordem alfabética)
  int countLetters[27] = {0};
  
  // Ordem da lista de probabilidade em ordem do documento
  int ordemProb[27] = {26, 4, 0, 14, 18, 17, 8, 13, 3, 12, 20, 19, 2, 11, 15, 21, 6, 7, 16, 1, 5, 25, 9, 23, 10, 22, 24};

  // Probabilidade de cada letra/espaco
                      //A     B      C      D     E    F    G      H     I    J    K     L    M
  float probPT[27] = {13.72, 1.04, 3.88, 4.99, 14.63, 1.02, 1.3, 1.28, 6.18, 0.4, 0.02, 2.78, 4.74,
                      5.05, 10.73, 2.52, 1.20, 6.53, 7.81, 4.34, 4.63, 1.67, 0.01, 0.27, 0.01, 0.47, 17.00};
                      //N     O      P     Q     R    S    T      U      V    W      X     Y    Z    ESPACO

  // Vector com as letras presentes.
  vector <int> letrasPres; 
  vector <int> letrasOrdem;
  
  for (int i = 0; i < input.length(); i++) {          // Loop para contar cada char
      char c = input[i];

      if ( c == ' ' ){                                // Se for um espaco, conte
        countLetters[26] += 1;
        if ( countLetters[26] == 1 )                  // E adicione o espaco nos simbolos presentes
          letrasPres.push_back(26);        
      }
      else 
        if (c < 'A' || c > 'Z') continue;             // Verifique se há o range que queremos de letras (apenas maiusculas)
          
          countLetters[c-'A'] += 1;                   // Se houver tal letra, adicione na conta
          
          if ( countLetters[c-'A'] == 1 )            // E adicione o numero nos simbolos presentes
            letrasPres.push_back(c-'A');

  }

  // Funcao para ordenar por quantidade
  /*
  
  cout << "\nInicial: ";
  for ( int i :  letrasPres){
    cout << i << " ";
  }
  cout << endl;
  */

  sort(letrasPres, countLetters);
  
  /*
  cout << "\nPos sort: ";
  for ( int i :  letrasPres){
    cout << i << " ";
  }
  cout << endl;
  */
  /*
  // Funcao para ordenar por probabilidade.
  for ( int i : ordemProb){
    if (find(letrasPres.begin(), letrasPres.end(), i) == letrasPres.end()){
      cout << "Nao tem a letra: " << (char)('A' + i) << endl;
    }
    else{
      letrasOrdem.push_back (i);
      cout << "Possui a letra:  " << (char)('A' + i) << endl;
    }
  }
  */
  
  // 3 Prints para saber se foi ordenado e as letras
/*
  cout << "Letras Presentes: ";
  for (int i : letrasPres ){
    cout << i << " ";
  }
  cout << "\nIndexs P Ordenadas: ";
  for (int i : letrasOrdem ){
    cout << i << "  ";
  }
  cout << "\nLetras P Ordenadas:    ";
  for (int i : letrasOrdem ){
    if ( i == 26 )
      cout << (char)(32);
    else
      cout << (char)(i + 'A') << "  ";
  }
*/

  for (int i = 0; i < 27; i++) {                    // Printamos as letras e quantidade de vezes que elas aparecem
    if ( i != 26 )
      cout << "[" << i << "]"<< (char)('A' + i) << ": " << countLetters[i] << endl;
    else
      cout << "Espaco" << ": " << countLetters[26] << endl;

  } 
 


  return 0;
}