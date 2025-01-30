#include <iostream>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <cmath>
#include <string>
#include <vector>
#include <bitset>
#include <map>

using namespace std;

// O algoritmo de Shannon Fano em si
// Passamos a quantidade de cada letra (em ordem decrescente), uma string vazia para adicionar a palavra chave, o inicio e o fim de onde ele tem de "dividir".

void algoritmoShannonFano(vector<int>& occurrenceNums, vector<string>& codeWord, int startRange, int finishRange) {
    // Condição de parada
    if (startRange >= finishRange || startRange == finishRange-1) return; 

    int total = 0;
    // Adicionamos uma variavel para a soma de todos os valores
    for (int i = startRange; i < finishRange; i++) {
        total += occurrenceNums[i];
    }

    int leftSum = 0, rightSum = total, splitIndex = startRange;
    int minDifference = abs(total);

    // Encontrar o ponto de divisão ideal
    for (int i = startRange; i <= finishRange; i++) {
        leftSum += occurrenceNums[i];
        rightSum -= occurrenceNums[i];
        int difference = abs(leftSum - rightSum);

        if (difference < minDifference) {
            minDifference = difference;
            splitIndex = i;
        }else break;
    }

    // Atribuir "0" para o grupo esquerdo e "1" para o direito
    for (int i = startRange; i < finishRange; i++) {
        if (i <= splitIndex)
            codeWord[i] += "0";
        else
            codeWord[i] += "1";        
    }

    // Recursão para os dois grupos
    algoritmoShannonFano(occurrenceNums, codeWord, startRange, splitIndex+1);
    algoritmoShannonFano(occurrenceNums, codeWord, splitIndex+1, finishRange);
}

// Função para a decodificação da string codificada
string descompressorShannonFano(const string& codificado, const vector<int>& letrasPres, const vector<string>& palavraCod) {
    // Criar um mapa para associar o código binário a cada letra
    map<string, char> codigoParaLetra;
    
    for (int i = 0; i < letrasPres.size(); i++) {
        if (letrasPres[i] == 26) {  // Espaco
            codigoParaLetra[palavraCod[i]] = ' ';
        } else {
            codigoParaLetra[palavraCod[i]] = 'A' + letrasPres[i];
        }
    }
    
    string mensagemDecodificada = "";
    string codigoAtual = "";
    
    // Percorrer o código codificado e decodificar
    for (char c : codificado) {
        codigoAtual += c;  // Acumula o código binário
        
        if (codigoParaLetra.find(codigoAtual) != codigoParaLetra.end()) {
            // Se o código binário corresponde a uma letra, adiciona à mensagem decodificada
            mensagemDecodificada += codigoParaLetra[codigoAtual];
            codigoAtual = "";  // Reseta para o próximo código
        }
    }
    
    return mensagemDecodificada;
}

// Um algoritmo de bubble sort (n^2), como sao poucos valores, nao se torna tao pesado.
void sort(vector<int> &simbPresentes, int contSimb[])
{
  int n = simbPresentes.size();

  for (int i = n ; i >= 0; i--) {
    
    bool flag = false;
    for (int j = n - 1; j > n - i; j--) {
      
      int letra = simbPresentes.at( j );
      int letra1 = simbPresentes.at( j - 1 );

      if (contSimb[letra] > contSimb[letra1]) {
        swap(simbPresentes[j], simbPresentes[j-1]);
        flag = true;
      }
    }

    if (!flag)
      break;
  }
}

// Funcao para ordenar por probabilidade.
void sortByProb( vector<int> simbPresentes, vector<int> &newOrdenado, vector<int> ordemProb ){
  for ( int i : ordemProb){
    
    if (find(simbPresentes.begin(), simbPresentes.end(), i) == simbPresentes.end()) continue;
    else
      newOrdenado.push_back (i);
  }

}

int main()
{
  string input = "ICARO E SALSICHA";
  cout << "\n---------- Frase Inserida ----------\n\nFrase:\t" << input << endl;
  
  // Contagem de cada letra em específico (em ordem alfabética)
  int countLetters[27] = {0};
  
  // Ordem da lista de probabilidade em ordem do documento
  const vector<int> ordemProb = {26, 4, 0, 14, 18, 17, 8, 13, 3, 12, 20, 19, 2, 11, 15, 21, 6, 7, 16, 1, 5, 25, 9, 23, 10, 22, 24};

  // Probabilidade de cada letra/espaco
                      //A     B      C      D     E    F    G      H     I    J    K     L    M
  float probPT[27] = {13.72, 1.04, 3.88, 4.99, 14.63, 1.02, 1.3, 1.28, 6.18, 0.4, 0.02, 2.78, 4.74,
                      5.05, 10.73, 2.52, 1.20, 6.53, 7.81, 4.34, 4.63, 1.67, 0.01, 0.27, 0.01, 0.47, 17.00};
                      //N     O      P     Q     R    S    T      U      V    W      X     Y    Z    ESPACO

  // Vector com as letras presentes.
  vector <int> letrasPres; 
  vector <int> letrasOrdem;

  // Funcao para contagem de caracteres e assimilar vector apenas com as letras presentes
  for (int i = 0; i < input.length(); i++) {          // Loop para contar cada char
      char c = input[i];

      if ( c == ' ' ){                                // Se for um espaco, conte
        countLetters[26] += 1;
        if ( countLetters[26] == 1 )                  // E adicione o espaco nos simbolos presentes
          letrasPres.push_back(26);        
        continue;
      }
      else 
        if (c < 'A' || c > 'Z') continue;             // Verifique se há o range que queremos de letras (apenas maiusculas)
          
        countLetters[c-'A'] += 1;                   // Se houver tal letra, adicione na conta
        
        if ( countLetters[c-'A'] == 1 )            // E adicione o numero nos simbolos presentes
          letrasPres.push_back(c-'A');
  }


  // ====================================== Sort ==========================

  // Sort por probabilidade e cria um novo array ordenado (para nao alterar o original)
  //sortByProb( letrasPres, letrasOrdem, ordemProb );

  // Bubble sort antes de qualquer operacao! (alterando o original)
  sort(letrasPres, countLetters);

  // Guarda a palavra codigo (ex: 000 ou 101... etc)
  vector<string> palavraCod;  
  // Guarda a quantidade de cada letra (em ordem decrescente)
  vector<int> quantLetraOrd;  

  // Adiciona as quantidades de cada letra individual em um vector (ex: A = 4... B = 3...)
  for ( int i : letrasPres ){
    quantLetraOrd.push_back(countLetters[i]);
  }

  // Passamos a quantidade de letras presentes (ex: abcd = 4 letras)
  int quantPorLetra = letrasPres.size();
  
  // Atribuimos uma string "vazia" ao vector de palavra codigo para adicionarmos 0 e 1 quando necessario
  for ( int i = 0; i < quantPorLetra; i++ ){
    palavraCod.push_back("");
  }
  
  cout << "\n---------- Shannon Fano -----------" << endl;
  
  // Chamada do algoritmo shannon fano (alterando palavra código)
  algoritmoShannonFano( quantLetraOrd, palavraCod, 0, quantPorLetra );

  // Prints Finais (tabela)
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

  // -------------------- Codificacao -------------------------

  cout << "\n\n---------- Codificacao -----------" << endl;

  string codificado = "";

  // Gravação dos bits.
  // Loop principal, onde ele vai passar por cada letra na frase original
  for ( int i = 0; i < input.size(); i++){
    char c = input[i];
    char p;
    
    // A partir de cada letra da frase original, ele confere o index nas letras presentes
    // (ordenadas de forma decrescente por sua quantidade)
    for ( int j = 0; j < letrasPres.size(); j++ ){
      
      // Se for um espaco, e tivermos um espaco nas letras presentes, pegamos seu index
      // (apenas para nao passar o index errado ao elemento)
      if ( c == ' ' && letrasPres[j] == 26 ){
        codificado += palavraCod.at(j);
        break;
      } 
      else{
        // A letra do vector de letras presentes é colocada em um char (representando a letra daquele index)
        p = (char)('A' + letrasPres[j]);
        
        // Se forem iguais, passamos seu index para adicionar a palavra j a string codificado
        if ( c == p ){
          codificado += palavraCod.at(j);
          break;
        }
      }
    }
  }

  cout << "\nFrase Codificada: " << codificado << "\n\n";

  // Decodificando a mensagem
  string mensagemDecodificada = descompressorShannonFano(codificado, letrasPres, palavraCod);
  
  cout << "Mensagem decodificada: " << mensagemDecodificada << endl;

  return 0;
}