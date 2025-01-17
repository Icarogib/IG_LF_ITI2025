#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cmath>
#include <string>

using namespace std;

int main()
{
  string input = "ABCDEFGHIJ KLMNOPQRSTUVWXYZ aaaa BBBB";
  int countLetters[27] = {0};
                      //A     B      C      D     E    F    G      H     I    J    K     L    M
  float probPT[27] = {13.72, 1.04, 3.88, 4.99, 14.63, 1.02, 1.3, 1.28, 6.18, 0.4, 0.02, 2.78, 4.74,
                      5.05, 10.73, 2.52, 1.20, 6.53, 7.81, 4.34, 4.63, 1.67, 0.01, 0.27, 0.01, 0.47, 17.00};
                      //N     O      P     Q     R    S    T      U      V    W      X     Y    Z    ESPACO

  for (int i = 0; i < input.length(); i++) {          // Loop para contar cada char
      char c = input[i];

      if ( c == ' ' )                                // Se for um espaco, conte
        countLetters[26] += 1;
      else 
        if (c < 'A' || c > 'Z') continue;            // Verifique se há o range que queremos de letras (apenas maiusculas)
          countLetters[c-'A'] += 1;

  }

  for (int i = 0; i < 27; i++) {                    // Printamos as letras e quantidade de vezes que elas aparecem
    if ( i != 26 )
      cout << (char)('A' + i) << ": " << countLetters[i] << endl;

    else
      cout << "Espaco" << ": " << countLetters[26] << endl;

  } 
   
    return 0;
}