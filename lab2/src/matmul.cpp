#include <cstdlib>
#include <iostream>
#include <cmath>
#include <ctime>
#include <omp.h>

using namespace std;

int main();
void timestamp();

//****************************************************************************80

int main()

{
  #define SIZE 300
  auto a = new double[SIZE][SIZE];
  double angle;
  auto b = new double[SIZE][SIZE];
  auto c = new double[SIZE][SIZE];
  int i;
  int j;
  int k;
  int n = SIZE;
  double pi = 3.141592653589793;
  double s;
  int thread_num;
  double wtime;

  timestamp();

  cout << "\n";
  cout << "MATMUL:\n";
  cout << "  C = A * B.\n";
  cout << "  Order N                 = " << n << "\n";

  //
  //  Loop 1: Evaluate A.
  //
  s = 1.0 / sqrt((double)(n));

  wtime = omp_get_wtime();

  for (i = 0; i < n; i++)
  {
    for (j = 0; j < n; j++)
    {
      angle = 2.0 * pi * i * j / (double)n;
      a[i][j] = s * (sin(angle) + cos(angle));
    }
  }
  //
  //  Loop 1: Evaluate B.
  //
  for (i = 0; i < n; i++)
  {
    for (j = 0; j < n; j++)
    {
      b[i][j] = a[i][j];
    }
  }
  
  //
  //  Loop 3: Compute C = A * B.
  //
  for (i = 0; i < n; i++)
  {
    for (j = 0; j < n; j++)
    {
      c[i][j] = 0.0;
      for (k = 0; k < n; k++)
      {
        c[i][j] = c[i][j] + a[i][k] * b[k][j];
      }
    }
  }

    wtime = omp_get_wtime() - wtime;
    cout << "  Elapsed seconds = " << wtime << "\n";
    cout << "  C(100,100)  = " << c[99][99] << "\n";
    
    //
    //  Terminate.
    //
    cout << "\n";
    cout << "Matmul:\n";
    cout << "  Normal end of execution.\n";
    cout << "\n";
    timestamp();
    return 0;
}
//****************************************************************************80

void timestamp()
{
#define TIME_SIZE 40

  static char time_buffer[TIME_SIZE];
  const struct std::tm *tm_ptr;
  std::time_t now;

  now = std::time(NULL);
  tm_ptr = std::localtime(&now);

  std::strftime(time_buffer, TIME_SIZE, "%d %B %Y %I:%M:%S %p", tm_ptr);

  std::cout << time_buffer << "\n";

  return;
#undef TIME_SIZE
}
