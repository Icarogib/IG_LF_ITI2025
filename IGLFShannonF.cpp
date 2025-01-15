#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cmath>
#include <string>

using namespace std;

int main()
{
  string input = "ABCDEFGHIJKLMNOPQRSTUVWXYZaaaaBBBB";
  int countLetters[26] = {0};

  for (int i = 0; i < input.length(); i++) {
      char c = input[i];
      if (c < 'A' || c > 'Z') continue;
      countLetters[c-'A'] += 1;
  }
  for (int i = 0; i < 26; i++) {
    cout << (char)('A' + i) << ": " << countLetters[i] << endl;
  } 
   
    return 0;
}