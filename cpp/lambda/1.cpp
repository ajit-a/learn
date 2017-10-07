/*https://msdn.microsoft.com/en-us/library/dd293608.aspx
 * http://stackoverflow.com/questions/7627098/what-is-a-lambda-expression-in-c11
 * */
#include <algorithm>
#include <cmath>
void abssort(float* x, unsigned n) {
    std::sort(x, x + n,
        // Lambda expression begins
        [](float a, float b) {
            return (std::abs(a) < std::abs(b));
        } // end of lambda expression
    );
}
int main()
{
	float p[3]={3,2,1};
	float *a=p;
 	abssort(p,3);
	for(int i=0;i<3;i++)
		printf("%f ",p[i]);
	return 0;
}
