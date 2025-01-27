#include <iostream>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <cmath>
#include <string>
#include <vector>
#include <bitset>

using namespace std;

void algoritmoShannonFano(vector<int>& occurrenceNums, vector<string>& codeWord, int startRange, int finishRange) {
    if (startRange >= finishRange) return; // Condição de parada

    int total = 0;
    for (int i = startRange; i < finishRange; i++) {
        total += occurrenceNums[i];
        cout << "total: " << total << endl;
    }

    int leftSum = 0, rightSum = total, splitIndex = startRange;
    int minDifference = abs(total);

    // Encontrar o ponto de divisão ideal
    for (int i = startRange; i < finishRange; i++) {
        leftSum += occurrenceNums[i];
        rightSum -= occurrenceNums[i];
        int difference = abs(leftSum - rightSum);

        cout << "minDifference: " << minDifference << endl;
        cout << "difference: " << difference << endl;

        if (difference < minDifference) {
            minDifference = difference;
            cout << "minDifference (if): " << minDifference << endl;
            splitIndex = i;
        }
    }

    cout << "splitIndex: " << splitIndex << endl;

    // Atribuir "0" para o grupo esquerdo e "1" para o direito
    for (int i = startRange; i < finishRange; i++) {
        if (i <= splitIndex)
            codeWord[i] += "0";
        else
            codeWord[i] += "1";
        
        cout << codeWord[i] << endl;
    }

    cout << "---------------------" << endl;

    // Recursão para os dois grupos
    algoritmoShannonFano(occurrenceNums, codeWord, startRange, splitIndex);
    algoritmoShannonFano(occurrenceNums, codeWord, splitIndex + 1, finishRange);
}

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
  //string input = "DBABCACBAA";
  string input = "CCCBBBBBBBCCCAAAAAAAAAAAAAAADDDDDDEEEEEE";
  cout << "---------- Frase Inserida ----------\n\t" << input << endl;
  
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


  // ====================================== COMECA DAQUI SALSICHA
  
  // Bubble sort antes de qualquer operacao!
  sort(letrasPres, countLetters);

  vector<string> palavraCod;  // Guarda a palavra codigo (ex: 000 ou 101... etc)
  vector<int> quantLetraOrd;  // Guarda a quantidade de cada letra (em ordem decrescente)

  // Adiciona as quantidades de cada letra individual em um vector (ex: A = 4... B = 3...)
  for ( int i : letrasPres ){
    quantLetraOrd.push_back(countLetters[i]);
    //cout << "Push num: " << countLetters[i] << " para letra " << (char)('A' + i) << endl; // Apenas um print de quantidade de letra e qual letra
  }

  // print vector quantidade de cada letra em ordem
  for ( int i : quantLetraOrd){
    cout << i << ", ";
  }

  // Passamos a quantidade de letras presentes (ex: abcd = 4 letras)
  int quantPorLetra = letrasPres.size();
  cout << "\nTamanho do vector de letras: " << quantPorLetra << endl;
  
  // Atribuimos uma string "vazia" ao vector de palavra codigo para adicionarmos 0 e 1 quando necessario
  for ( int i = 0; i < quantPorLetra; i++ ){
    palavraCod.push_back("");
  }
  
  cout << "---------- Shannon Fano -----------" << endl;
  
  algoritmoShannonFano( quantLetraOrd, palavraCod, 0, quantPorLetra );

  cout << "\nQuant let: ";
  for ( int i : quantLetraOrd){
    cout << "\t(" << i << ")";
  }

  cout << "\nLetra do Cod: ";
  for ( int i : letrasPres ){
    if ( i == 26 )
      cout << "\t_";
    else
      cout << "\t" << (char)( 'A' + i );
  }
  cout << "\nCodigo Letra: ";
  for ( int i = 0; i < quantPorLetra; i++ ){
    cout << "\t" << palavraCod.at(i) ;
  }

  /*
  // Funcao para ordenar por probabilidade.
  for ( int i : ordemProb){
    if (find(letrasPres.begin(), letrasPres.end(), i) == letrasPres.end()){
      //cout << "Nao tem a letra: " << (char)('A' + i) << endl;
    }
    else{
      letrasOrdem.push_back (i);
      //cout << "Possui a letra:  " << (char)('A' + i) << endl;
    }
  }
  */

  return 0;
}