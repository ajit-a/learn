#include <stdio.h>
 
// C recursive function to solve tower of hanoi puzzle
static int _i;
void towerOfHanoi(int n, char fromrod, char auxrod, char torod)
{
    printf("%c %c %c\n",fromrod,torod,auxrod);
    _i++;
    if (n > 0)
    {
    //    printf("%d Move disk 1 from rod %c to rod %c\n",_i, fromrod, torod);
    //    return;
    towerOfHanoi(n-1, fromrod, torod, auxrod);
    printf("%d Move disk %d from rod %c to rod %c\n",_i, n, fromrod, torod);
    towerOfHanoi(n-1, auxrod, fromrod, torod);
    }
}
 
int main()
{
    int n = 3; // Number of disks
    towerOfHanoi(n, 'A', 'B', 'C');  // A, B and C are names of rods
    return 0;
}
