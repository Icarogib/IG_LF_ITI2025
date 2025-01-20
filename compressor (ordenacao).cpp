#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>

using namespace std;

#define FREQ_ESPACO 0.17;
#define FREQ_E 0.1463;
#define FREQ_A 0.1372;
#define FREQ_O 0.1073;
#define FREQ_S 0.0781;
#define FREQ_R 0.0653;
#define FREQ_I 0.0618;
#define FREQ_N 0.0505;
#define FREQ_D 0.0499;
#define FREQ_M 0.0474;
#define FREQ_U 0.0463;
#define FREQ_T 0.0434;
#define FREQ_C 0.0388;
#define FREQ_L 0.0278;
#define FREQ_P 0.0252;
#define FREQ_V 0.0167;
#define FREQ_G 0.0130;
#define FREQ_H 0.0128;
#define FREQ_Q 0.0120;
#define FREQ_B 0.0104;
#define FREQ_F 0.0102;
#define FREQ_Z 0.0047;
#define FREQ_J 0.0040;
#define FREQ_X 0.0027;
#define FREQ_K 0.0002;
#define FREQ_W 0.0001;
#define FREQ_Y 0.0001;

void algoritmoShannonFano(){

}

int main()
{

  string input = "LUIS FELIPE TOLENTINO LEMOS SAO PAULO SP";
  int countLetters[27] = {0};
  char letters[27] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z',' '};


  for (int i = 0; i < input.length(); i++) {                  // CONTA A QUANTIDADE DE OCORRENCIAS PRA CADA CARACTERE
      char c = input[i];

      if (c == ' ') countLetters[26] += 1;

      if (c < 'A' || c > 'Z') continue;
      countLetters[c-'A'] += 1;
  }

  for (int i = 0; i < 26; i++) {                              // EXIBIÇAO DAS QUANTIDADES PARA CADA CARACTERE
    cout << (char)('A' + i) << ": " << countLetters[i] << endl;
  } 

  cout << "Espaco: " << countLetters[26] << endl;


  int count = 0;                                              // CONTA A QUANTIDADE DE CARACTERESES COM NUMERO DE OCORRENCIAS > 0
  for (int i = 0; i < 27; i++){                              

    if (countLetters[i] > 0){
      count += 1;
    }
  }
  char usedLetters[count] = {0};                              // ARRAY QUE USA COUNT PARA ARMAZENAR OS CARACTERES QUE CONTEM OCORRENCIA
  int  occurrenceNums[count]= {0};                            // ARRAY QUE USA COUNT PARA ARMAZENAR O NUMERO DE OCORRENCIA DOS CARACTERES



  for (int i = 0; i < 27; i++){                               // SELETOR DE OCORRENCIAS, ORGANIZA UM ARRAY COM OCORRENCIAS > 0 EM ORDEM DECRESCENTE       

    if (countLetters[i] == 0) continue;

    int compare = countLetters[i];                            // VARIAVEL QUE RECEBE O NUMERO A SER ALOCADO NO NOVO ARRAY
    int points = count - 1;                                   // VARIAVEL PARA DETERMINAR A POSIÇAO DO NUMERO NO NOVO ARRAY
    char lett = letters[i];

    for (int j = 0; j < 27; j++){                              // LOOP PARA COMPARAR O NUMERO ATUAL COM OS NUMEROS > 0 RESTANTES DO ARRAY
      
      if (countLetters[j] == 0) continue;                      // IGNORA ZEROS E O PROPRIO NUMERO, DE ACORDO COM SUA POSIÇAO NO ARRAY
      if (j == i) continue;


      if (compare >= countLetters[j]){                         // DETERMINA A POSIÇAO DO NUMERO NO ARRAY NOVO, A FIM DE ORGANIZA-LO EM ORDEM DECRESCENTE
        points -= 1;
      }

    }

    if(occurrenceNums[points] == 0 && usedLetters[points] == 0){
      occurrenceNums[points] = compare;
      usedLetters[points] = lett;
    }else{
      int occ = occurrenceNums[points];
      while(occ != 0){
        points += 1;
        occ = occurrenceNums[points];
        if(occ == 0){
          occurrenceNums[points] = compare;
          usedLetters[points] = lett;
        }
      }
    }

  }

  for (int i = 0; i < count; i++) cout << usedLetters[i] << occurrenceNums[i] << ", ";

  algoritmoShannonFano();

    return 0;
}