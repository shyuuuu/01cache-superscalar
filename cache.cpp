#include <iostream>
#include <fstream>
#include <windows.h>

using namespace std;

int **generateMatrix(int n)
{
    int **a = new int*[n];
    for (int i = 0; i < n; i++)
    {
        a[i] = new int[n];
        for (int j = 0; j < n; j++)
        {
            a[i][j] = i+j;
        }
    }
    return a;
}
int *generateVector(int n)
{
    int *v = new int[n];
    for (int i = 0; i < n; i++)
    {
        v[i] = i;
    }
    return v;
}
void normal_multiply(int **matrix, int *v, int n, ostream &out)
{
    long long head, tail , freq ;
    QueryPerformanceFrequency((LARGE_INTEGER *)&freq );
    QueryPerformanceCounter((LARGE_INTEGER *)&head);
    for (int i = 0; i < n; i++)
    {
        int res = 0;
        for (int j = 0; j < n; j++)
        {
            res += matrix[j][i]*v[j];
        }
    }
    QueryPerformanceCounter((LARGE_INTEGER *)&tail );
    out << (tail - head)*1000.0/freq<<"ms"<<"\t";
}
void cache_multiply(int **matrix, int *v, int n, ostream &out)
{
    long long head, tail , freq ;
    QueryPerformanceFrequency((LARGE_INTEGER *)&freq );
    QueryPerformanceCounter((LARGE_INTEGER *)&head);
    int *res = new int[n];
    for (int i = 0; i < n; i++)
    {
        res[i] = 0;
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            res[j] += matrix[i][j]*v[i];
        }
    }
    QueryPerformanceCounter((LARGE_INTEGER *)&tail );
    out << (tail - head)*1000.0/freq<<"ms"<<endl<<"\t";
    delete []res;
}
int main()
{
    ofstream out("output.txt");
    for (int n = 200; n <= 10000; n += 200)
    {
        out << n << "\t";
        int **a = generateMatrix(n);
        int *v = generateVector(n);
        normal_multiply(a, v, n, out);
        cache_multiply(a, v, n, out);
        out << endl;
        for (int i = 0; i < n; i++)
        {
            delete []a[i];
        }
        delete []a;
        delete []v;
    }
        out.close();
    return 0;
}
