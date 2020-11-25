#include "main.h"

int main()
{
  vector<ZZ> bruh;
  string s = "hello";
  makeBlocks(bruh, s);
  for (int i = 0; i < bruh.size(); i++)
  {
    cout << bruh[i] << endl;
  }
  
}