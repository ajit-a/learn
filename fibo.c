#include <stdio.h>
 
/* Helper function that multiplies 2 matricies F and M of size 2*2, and
 *   puts the multiplication result back to F[][] */
void multiply(long long F[2][2], int M[2][2]);
 
/* Helper function that calculates F[][] raise to the power n and puts the
 *   result in F[][]
 *     Note that this function is desinged only for fib() and won't work as general
 *       power function */
void power(long long F[2][2], long long n);
 
long long fib(long long n)
{
  long long F[2][2] = {{1,1},{1,0}};
  if (n == 0)
      return 0;
  power(F, n-1);
 
  return F[0][0];
}
 
void multiply(long long F[2][2], int M[2][2])
{
  long long x =  F[0][0]*M[0][0] + F[0][1]*M[1][0];
  long long y =  F[0][0]*M[0][1] + F[0][1]*M[1][1];
  long long z =  F[1][0]*M[0][0] + F[1][1]*M[1][0];
  long long w =  F[1][0]*M[0][1] + F[1][1]*M[1][1];
 
  F[0][0] = x;
  F[0][1] = y;
  F[1][0] = z;
  F[1][1] = w;
}
 
void power(long long F[2][2], long long n)
{
  int i;
  int M[2][2] = {{1,1},{1,0}};
 
/* n - 1 times multiply the matrix to {{1,0},{0,1}}*/
     for (i = 2; i <= n; i++)
           multiply(F, M);
}
  //          
  //          /* Driver program to test above function */
            int main()
            {
              long long n = 9;
		scanf("%lld",&n);
                printf("%lld", fib(n));
                  getchar();
                    return 0;
                  }
