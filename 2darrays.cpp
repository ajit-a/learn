#include <iostream>
#include <chrono>
#include <memory>
#include <vector>

using namespace std;

void print(int *a,int M,int N)
{
	cout<<__func__<<endl;
	for(int i=0;i<M;++i)
	{
	  for(int j=0;j<N;++j)
	  { 
		//cout<<a[i][j]<<endl;
		cout<<a[i*N+j]<<" ";
	  }
	  cout<<endl;
	}
}
void print1(int **a,int M,int N)
{
	cout<<__func__<<endl;
	for(int i=0;i<M;++i)
	{
	  for(int j=0;j<N;++j)
	  { 
		cout<<a[i][j]<<" ";
	  }
	  cout<<endl;
	}
}
void print2(unique_ptr<int*[]> a,int M,int N)
{
	cout<<__func__<<endl;
	for(int i=0;i<M;++i)
	{
	  for(int j=0;j<N;++j)
	  { 
		cout<<a[i][j]<<" ";
	  }
	  cout<<endl;
	}
}
template<typename T>
void print3(T a,int M,int N)
//void print3(vector<int> *a,int M,int N)
{
	cout<<__func__<<endl;
	for(int i=0;i<M;++i)
	{
	  for(int j=0;j<N;++j)
	  { 
		cout<<a[i][j]<<" ";
	  }
	  cout<<endl;
	}
}

int main()
{
	srand(time(0));
	int N,M;
	M=3000;N=6000;
	/*Method 1 - Best method*/
	{
	auto start = chrono::steady_clock::now();
	int *a = new int [M*N];
	
	for(int i=0;i<M;++i)
	{
	  for(int j=0;j<N;++j)
	  {
		  a[i*N+j]=rand()%10;
	  }
	}
	print(a,M,N);
	delete[]a;
	auto end = chrono::steady_clock::now();
	cout << "Elapsed time in microseconds: "
        << chrono::duration_cast<chrono::microseconds>(end - start).count()
        << " µs" << endl;
	}

	/*Method 2 - Regular method*/
	{
	auto start = chrono::steady_clock::now();
	int **b = new int*[M];
	for(int i=0;i<M;++i)
		b[i] = new int[N];

	for(int i=0;i<M;++i)
	{
	  for(int j=0;j<N;++j)
	  {
		  b[i][j]=rand()%10;
	  }
	}
	print1(b,M,N);
	for(int i=0;i<M;++i)
		delete []b[i];
	delete []b;
	auto end = chrono::steady_clock::now();
	cout << "Elapsed time in microseconds: "
        << chrono::duration_cast<chrono::microseconds>(end - start).count()
        << " µs" << endl;
	}
	/*With a[x][y], what you are actually doing is *(*(a + x) + y): two additions and two memory fetches. With a[index(x, y)], what you are actually doing is *(a + x + w*y): two additions, one multiplication, and one memory fetch. The latter is often preferable, for the reasons exposed in this answer (i.e., trading the extra memory fetch with a multiplication is worth it, especially because the data isn't fragmented and therefore you don't cache-miss)*/

	/*Method 3 - better than 2 method*/
	{
	auto start = chrono::steady_clock::now();
	{
	std::unique_ptr<int[]> row;
	std::unique_ptr<int*[]> c;
	// before C++14 use // newData.reset(new GridUnit[width * height]);
	row = std::make_unique<int[]>(M * N);
	// before C++14 use // newGrid.reset(new GridUnit*[width]);
	c = std::make_unique<int*[]>(M);
	for (int i = 0; i < M; i++)
    		c[i] = &row[i * N];
	for(int i=0;i<M;++i)
	{
	  for(int j=0;j<N;++j)
	  {
		  c[i][j]=rand()%10;
	  }
	}
	print2(move(c),M,N);
	}
	auto end = chrono::steady_clock::now();
	cout << "Elapsed time in microseconds: "
        << chrono::duration_cast<chrono::microseconds>(end - start).count()
        << " µs" << endl;
	}
	/*Method 4*/
	{
	auto start = chrono::steady_clock::now();
	{
	vector<vector<int>> d(M,vector<int>(N));
	for(int i=0;i<M;++i)
	{
	  for(int j=0;j<N;++j)
	  {
		  d[i][j]=rand()%10;
	  }
	}
	print3(d,M,N);
	}
	auto end = chrono::steady_clock::now();
	cout << "Elapsed time in microseconds: "
        << chrono::duration_cast<chrono::microseconds>(end - start).count()
        << " µs" << endl;
	}
	/*Method 5*/
	{
	auto start = chrono::steady_clock::now();
	{
	vector<int> E[M];
	for(int i=0;i<M;++i)
	  for(int j=0;j<N;++j)
		E[i].push_back(rand()%10);
	print3(E,M,N);
	}
	auto end = chrono::steady_clock::now();
	cout << "Elapsed time in microseconds: "
        << chrono::duration_cast<chrono::microseconds>(end - start).count()
        << " µs" << endl;
	}

}
