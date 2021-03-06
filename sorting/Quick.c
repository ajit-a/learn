#include <stdio.h>

int n;
int arr[100];
void quickSort (int arr[], int left, int right)
{
    int i = left, j = right;
    int tmp;
    int pivot = arr[ (left + right) / 2]; //Any element can be considered as pivot, we have variants of quick sort

    int _i;
    printf("pivot: %d\n",pivot);
    for(_i=left;_i<=right;_i++){printf("%d ",arr[_i]);}printf("\n");
    /* partition */
    while (i <= j)
    {
        while (arr[i] < pivot) //search for element greater than / equal to pivot
        {
            i++;
        }
        while (arr[j] > pivot) //search for element smaller than / equal to pivot
        {
            j--;
        }
        if (i <= j) //If indexes have not crossed each other, swap the left and right element
        {
            tmp = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp;
            i++;
            j--;
        }
    //for(_i=left;_i<=right;_i++){printf("%d ",arr[_i]);}printf("\n");
    }
    for(_i=left;_i<=right;_i++){printf("%d ",arr[_i]);}printf("\n");
    printf("i:%d j:%d\n",i,j);
    /* recursion */ //This is the division step, perform the swapping recursively of small sub-arrays
    if (left < j)
    {
        quickSort (arr, left, j); //Call left subarray
    }
    if (i < right)
    {
        quickSort (arr, i, right); //call right subarray
    }
}

void display()
{
    int i;
    for (i = 0; i < n; i++)
    {
        printf ("%d ", arr[i]);
    }
    printf ("\n");
}
int main()
{
    int i;
    printf ("Enter the number of elements\n");
    scanf ("%d", &n);
    for (i = 0; i < n; i++)
    {
        scanf ("%d", &arr[i]);
    }
    quickSort (arr, 0, n - 1);
    display();
    return 0;
}
