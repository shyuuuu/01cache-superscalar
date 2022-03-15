#include <iostream>
#include <fstream>
#include <windows.h>
#include <math.h>
using namespace std;

int* array_generator(int n)
{
    int num = pow(2,n);
    int* a = new int[num];
    for(int i = 1;i<=pow(2,n);i+=1)
    {
        a[i-1] = i;
    }
    return a;
}
void normal_addition(int* a,int n,ostream &out)
{
    long long int sum = 0;
    long long head, tail , freq ;
    QueryPerformanceFrequency((LARGE_INTEGER *)&freq );
    QueryPerformanceCounter((LARGE_INTEGER *)&head);
    for(int i = 0;i<pow(2,n);i+=1)
    {
        sum+=a[i];
    }
    QueryPerformanceCounter((LARGE_INTEGER *)&tail );
    out << (tail - head)*1000.0/freq<<"ms"<<"\t";
}
void superscalar_addition(int* a,int n,ostream &out)
{
    int num = pow(2,n);
    long long head, tail , freq ;
    QueryPerformanceFrequency((LARGE_INTEGER *)&freq );
    QueryPerformanceCounter((LARGE_INTEGER *)&head);
    for(int m = num;m>1;m/=2)
    {
        for(int i = 0;i<m/2;i++)
        {
            a[i] = a[i*2]+a[i*2+1];
        }
    }
    QueryPerformanceCounter((LARGE_INTEGER *)&tail );
    out << (tail - head)*1000.0/freq<<"ms"<<"\t";
}
int main()
{
    ofstream out("output.txt");
    for (int n = 1; n <= 30; n += 1)
    {
        out << pow(2,n) << "\t";
        int *a = array_generator(n);
        normal_addition(a,n,out);
        superscalar_addition(a,n,out);
        out << endl;
        delete[] a;
    }
    out.close();
    return 0;
}
