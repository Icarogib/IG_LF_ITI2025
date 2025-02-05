// **********************************************
// *             Shannon Fano by                *
// *       Luis Felipe e Icaro Gibson           *
// *            04/02/2025 - ITI                *
// *                                            *
// * https://github.com/Icarogib/IG_LF_ITI2025  *
// *                                            *
// **********************************************
//  Para executar o código, é necessário ter uma versão do
// compilador para c++ (mingw - G++ ou equivalente)
// então é compilado com:
//  
//  g++ .\IGLFShannonF.cpp -o ShannonFanoIDLF
//
//  E executado com:
//
//  .\ShannonFanoIDLF
//
//  ( Feito no VSCode e g++ 6.3.0 )
// 

#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <vector>
#include <bitset>
#include <cmath>
#include <ctime>
#include <map>

#define BYPROB 1

using namespace std;

// O algoritmo de Shannon Fano em si
// Passamos a quantidade de cada letra (em ordem decrescente), uma string vazia para adicionar a palavra chave, o inicio e o fim de onde ele tem de "dividir".
void algoritmoShannonFano(vector<float>& occurrenceNums, vector<string>& codeWord, int startRange, int finishRange) {
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

// Função para a decodificacao da string codificada
string descompressorShannonFano(const string& codificado, const vector<int>& letrasPres, const vector<string>& palavraCod) {
    // Criar um mapa para associar o codigo binario a cada letra
    map<string, char> codigoParaLetra;
    
    // Passando o codigo para cada letra fica mais facil de calcular qual a letra do codigo
    for ( int i = 0; i < letrasPres.size(); i++ ) {
        if ( letrasPres[i] == 26 ) {  // Espaco
            codigoParaLetra[ palavraCod[i] ] = ' ';
        } else {
            codigoParaLetra[ palavraCod[i] ] = 'A' + letrasPres[i];
        }
    }
    
    string mensagemDecodificada = "";
    string codigoAtual = "";
    
    // Percorrer o codigo codificado e decodificar
    for ( char c : codificado ) {
        // Soma a quantidade do codigo binario
        codigoAtual += c;  
        
        // Se o codigo binario corresponde a uma letra, adiciona a mensagem decodificada
        if ( codigoParaLetra.find(codigoAtual) != codigoParaLetra.end() ) {

            mensagemDecodificada += codigoParaLetra[codigoAtual];
            codigoAtual = "";  // Reseta para o proximo codigo
        }
    }
    
    return mensagemDecodificada;
}

// Calculo da razao de compressao.
float calcularRazaoCompressao(int totalSimbolos, const vector<int> letrasPres, const vector<string> palavraCod, int quantSimbolo[]) {
    float somaBits = 0;
    int j = 0;
    
    // Passa por cada letra presente
    for (int i : letrasPres) {
        int ocorrencias = quantSimbolo[i];  // Contar ocorrencias do simbolo
        
        // Soma os bits necessarios para cada símbolo
        somaBits += ocorrencias * palavraCod[j].size();
        j++;
    }

    // Faz a divisao da formula
    float numeroMedioBitsPorSimbolo = somaBits / totalSimbolos;
    
    // E logo apos calcula a razão de compressão
    return 5 / numeroMedioBitsPorSimbolo;
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
void sortByProb( vector<int> &simbPresentes, vector<int> ordemProb ){
  vector<int> newOrdenado;

  // Procura o valor comparando pela ordem de qual eh maior
  for ( int i : ordemProb){
    
    if (find(simbPresentes.begin(), simbPresentes.end(), i) == simbPresentes.end()) continue;
    else
      newOrdenado.push_back (i);
  }
  simbPresentes.clear();
  // Coloca o nono substituindo o vector original
  simbPresentes = newOrdenado;
  
}

// Salvamos os bits em um arquivo binário, e retornamos a 
// quantidade de bits desnecessários para retirarmos após o final dos dados
int salvarBits(const string& msg, FILE* arquivo) {
  // Pegamos o tamanho da mensagem toda, cada 1 e 0 sendo 1bit
  int num_bits = msg.length();
  // Numero total em bytes para o arquivo final
  int num_bytes = (num_bits + 7) / 8;  

  // Valor para ser retornado pela funcao para ignorarmos
  int ignorado = (num_bytes * 8) - num_bits;

  // Passamos por cada valor e salvamos seu bit no arquivo (de 8 bits em 8 bits)
  for (int i = 0; i < num_bytes; i++) { 
      unsigned char byte = 0;

      // Aqui pegamos de bit a bit
      for (int j = 0; j < 8; j++) { 
          int bit_index = i * 8 + j;
          if (bit_index < num_bits && msg[bit_index] == '1') {
              byte |= (1 << (7 - j));  
          }
      }
      // Escrevemos o valor do byte completo
      fwrite(&byte, 1, 1, arquivo); 
  }
  return ignorado;
}

vector<unsigned char> lerArquivoBinario(const string& nomeArquivo) {
    // Abrimos o arquivo binario para a leitura
    ifstream arquivo(nomeArquivo, ios::binary | ios::ate);

    if (!arquivo) {
        cerr << "Erro ao abrir o arquivo para leitura!" << endl;
        return {};
    }

    // Obtém tamanho do arquivo (parte obtida na internet)
    streamsize tamanho = arquivo.tellg(); 
    arquivo.seekg(0, ios::beg); 

    vector<unsigned char> buffer(tamanho); // Cria um vetor para armazenar os dados
    if (!arquivo.read(reinterpret_cast<char*>(buffer.data()), tamanho)) {
        cerr << "Erro ao ler o arquivo!" << endl;
        return {};
    }

    return buffer;
}

int main()
{
  string input = "ICARO DUTRA GIBSON DA SILVA CAMPINA GRANDE PARAIBA";

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

      if ( c == ' ' && c == input[i-1]) continue;     // Se o espaço for repetido, pule esse espaço
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
  
  // Guarda a probabilidade/quantidade de cada letra
  vector<float> probnumletras;

  // Seletor sort ( 1 - probabilidade / 0 - quantidade )
  if (BYPROB){
  // Sort por probabilidade e cria um novo array ordenado
    sortByProb( letrasPres, ordemProb );
  
  // Adiciona as probabilidade de cada letra individual em um vector (ex: A = 4... B = 3...)
    for ( int i : letrasPres ) probnumletras.push_back(probPT[i]);
    
  }else{
  // Bubble sort antes de qualquer operacao! (alterando o original)
    sort(letrasPres, countLetters);
  
  // Adiciona as quantidades de cada letra individual em um vector (ex: A = 4... B = 3...)
    for ( int i : letrasPres ) probnumletras.push_back(countLetters[i]);
  }

  // Guarda a palavra codigo (ex: 000 ou 101... etc)
  vector<string> palavraCod;  
  
  // Passamos a quantidade de letras presentes (ex: abcd = 4 letras)
  int quantPorLetra = letrasPres.size();
  
  // Atribuimos uma string "vazia" ao vector de palavra codigo para adicionarmos 0 e 1 quando necessario
  for ( int i = 0; i < quantPorLetra; i++ ){
    palavraCod.push_back("");
  }
  
  cout << "\n---------- Shannon Fano -----------" << endl;
  
  // Chamada do algoritmo shannon fano (alterando palavra código)
  algoritmoShannonFano( probnumletras, palavraCod, 0, quantPorLetra );

  // Prints Finais 
  cout << "\nQuant let: ";
  for ( float i : probnumletras){
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


  // ================= Abertura de arquivo =========================

  FILE* arquivo = fopen("saida.bin", "wb");

  if (!arquivo) {
      cerr << "Erro ao abrir o arquivo!" << endl;
      return 1;
  }

  // Salvamos a quantidade de bits ignorados enquanto ele salva os dados em um arquivo binário.
  int ignore = salvarBits(codificado, arquivo);
  fclose(arquivo);

  cout << "\nBits salvos em saida.bin!" << endl;

  // =================== Leitura de arquivo ========================

  codificado = "";
  vector<unsigned char> dados = lerArquivoBinario("saida.bin");

  if (!dados.empty()) {
      cout << "\nArquivo lido com sucesso!" << endl;
      bitset<8> bytesCod;

      // Passa cada Byte para a string
      for (unsigned char byte : dados) {
        bytesCod = bitset<8>(byte);
        codificado += bytesCod.to_string();
      }
      cout << endl;

      // Remove os ultimos a serem ignorados
      for ( int i = 0 ; i < ignore; i++ ){
        codificado.pop_back();
      }
  }

  cout << "---------- Resultados -----------" << endl;
  cout << "\nFrase Codificada: " << codificado << "\n\n";

  // Decodificando a mensagem
  string mensagemDecodificada = descompressorShannonFano(codificado, letrasPres, palavraCod);
  
  cout << "Frase decodificada: " << mensagemDecodificada << endl;

  cout << "\nTamanho da frase original: \t" << input.size() << " Bytes" << endl;
  cout << "\nTamanho do arquivo Binario: \t" << dados.size() << " Bytes" << endl;

  // Calculando a razao de compressao
  float razao = calcularRazaoCompressao( input.size(), letrasPres, palavraCod, countLetters);

  cout << "\nRazao de compressao: " << razao << endl;
  cout << endl;

  return 0;
}