#include<iostream>
#include <stdlib.h>
#include "main.hpp"
using namespace std;

int* getAddr()
{
	int *a=(int*)malloc(sizeof(int)*100000);
	cout<<"addr in cpp : "<<a<<endl;
	return a;
}
