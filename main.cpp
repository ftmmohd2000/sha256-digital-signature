#include "main.h"
#include <ctime>

int main()
{
  using namespace std::chrono;

  high_resolution_clock::time_point t1 = high_resolution_clock::now();

  string input = "helloworld";

  cout << sha256(input) << endl;

  high_resolution_clock::time_point t2 = high_resolution_clock::now();

  duration<double, std::milli> time_span = t2 - t1;

  cout << "It took me " << time_span.count() << " milliseconds." << endl;
}