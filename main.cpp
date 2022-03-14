#include <iostream>
#include <bits/stdc++.h>
#include <chrono>
#include <ctime>
#include <vector>

using namespace std;

int T;
long long Max, n;
vector <long long> v, tmp, random;

///****MergeSort****
void MergeSort(vector <long long>& v, long long st, long long dr)
{
    if(st < dr)
    {
        ///Impartirea vectorului in jumatate
       long long  m = (st + dr) / 2;
        ///Sortarea independenta a jumatatilor in mod recursiv
        MergeSort(v, st, m);
        MergeSort(v, m + 1, dr);
        ///Interclasare
        long long i = st, j = m + 1;
        tmp.clear();
        while( i <= m && j <= dr )
            if( v[i] < v[j])
                tmp.push_back(v[i++]);
            else
                tmp.push_back(v[j++]);
        while(i <= m)
            tmp.push_back(v[i++]);
        while(j <= dr)
            tmp.push_back(v[j++]);
        for(i = st, j = 0 ; i <= dr ; i ++, j ++)


            v[i] = tmp[j];
    }
}


///****RadixSort****
void CountSort(vector <long long> &v, long long n, long long exp, int baza)
{
	vector <long long> rez=vector <long long>(n+1);
    long long f[baza+1]={0};

	for (long long i=0; i<n; i++)
		f[(v[i] / exp) % baza]++;

	for (long long i=1; i<baza; i++)
		f[i] += f[i-1];

	for (long long i=n-1; i>=0; i--) {
		rez[f[(v[i]/exp)%baza]-1]=v[i];
		f[(v[i]/exp)%baza]--;
	}

	for (long long i=0; i<n; i++)
		v[i] = rez[i];
}

void RadixSort(vector <long long> &v, long long n, int baza)
{
	long long m=0;
	for(long long i=0; i<n; i++)
        if(m<v[i])
            m=v[i];

	for (long long exp=1; m/exp>0; exp*=baza)
		CountSort(v, n, exp, baza);
}

///ShellSort

void ShellSort(vector <long long> &v, long long n)
{
    for (long long d = n/2; d > 0; d /= 2)
    {
        for (long long i = d; i < n; i ++)
        {
            long long elem = v[i];
            long long j;
            for (j = i; j >= d && v[j - d] > elem; j -= d)
                v[j] = v[j - d];
            v[j] = elem;
        }
    }
}


///QuickSort cu pivot random

long long Pivot(vector <long long> &v,long long st,long long dr)
{
    long long i=st-1;
    for(long long j=st;j<=dr-1;j++)
    {
        if(v[j]<=v[dr])
        {
            i=i+1;
            long long aux=v[i];
            v[i]=v[j];
            v[j]=aux;
        }
    }
    long long aux=v[i+1];
    v[i+1]=v[dr];
    v[dr]=aux;
    return i+1;
}

long long PivotRandom(vector <long long> &v,long long st,long long dr)
{
    long long i=st+rand()%(dr-st+1);
    long long aux=v[dr];
    v[dr]=v[i];
    v[i]=aux;
    return Pivot(v,st,dr);
}

  void QuickSort(vector <long long> &v,long long st,long long dr)
{
    if(st<dr)
    {
        long long pivot=PivotRandom(v,st,dr);
        QuickSort(v,st,pivot-1);
        QuickSort(v,pivot+1,dr);
    }
}

///QuickSort mediana din 3
long long mijloc(long long x1, long long x2, long long x3)
{
    if((v[x1]<=v[x2] && v[x2]<=v[x3])||(v[x3]<=v[x2] && v[x2]<=v[x1]))
        return x2;
    if((v[x2]<=v[x1] && v[x1]<=v[x3])||(v[x3]<=v[x1] && v[x1]<=v[x2]))
        return x1;
    return x3;
}

long long PivotMed3(vector <long long> &v,long long st,long long dr)
{
    long long x1=st+rand()%(dr-st+1), x2=st+rand()%(dr-st+1), x3=st+rand()%(dr-st+1);
    long long i=mijloc(x1, x2, x3);
    long long aux=v[dr];
    v[dr]=v[i];
    v[i]=aux;
    return Pivot(v,st,dr);
}

  void QuickSortMed3(vector <long long> &v,long long st,long long dr)
{
    if(st<dr)
    {
        long long pivot=PivotMed3(v,st,dr);
        QuickSortMed3(v,st,pivot-1);
        QuickSortMed3(v,pivot+1,dr);
    }
}


///***HeapSort***

//pune in radacina elementul maxim, aranjand poz

void adauga(vector <long long> &v, long long n, long long poz)
{

    long long st = 2 * poz + 1;
    long long dr = 2 * poz + 2;
    long long rad = poz;

    //Comparare stanga
    if (st < n && v[st] > v[rad])
        rad = st;

    // Comparare dreapta
    if (dr < n && v[dr] > v[rad])
        rad = dr;

    if (rad != poz)
        {
        long long aux=v[poz];
        v[poz]=v[rad];
        v[rad]=aux;

        adauga(v, n, rad);
    }
}

void HeapSort(vector <long long> &v, int n)
{
    for (long long i = n / 2 - 1; i >= 0; i--)
        adauga(v, n, i);

    for (long long i = n - 1; i > 0; i--)
    {
        long long aux=v[0];
        v[0]=v[i];
        v[i]=aux;
        adauga(v, i, 0);
    }
}


///*****************

bool TestSort(vector <long long> v, long long n)
{
    for(long long i=1; i< n ;i++)
    {
        if(v[i] < v[i-1])
            return 0;
    }
    return 1;
}

int main()
{
    cin >> T;
    for(int k=0; k<T; k++)
    {
        cin>>n>>Max;
        cout<<"N= "<<n<<" Maxim= "<<Max<<endl;
        //long long v[n+1], random[n+1];

        chrono::time_point<std::chrono::system_clock> start, stop;

        ///generare vector pentru toate sortarile
        random=vector <long long>(n+1);
        for(long long i = 0 ; i < n ; i ++)
            random[i]=rand()%Max;
        v=vector <long long>(n+1);
        ///v pt MergeSort
        for(long long i = 0 ; i < n ; i ++)
            v[i]=random[i];

        start = chrono::system_clock::now();
        MergeSort(v, 0, n - 1);

        stop = chrono::system_clock::now();
        chrono::duration<double> elapsed_seconds = stop - start;
        cout  << "MergeSort\n"<<"Durata: " << elapsed_seconds.count() << "s\n";
        if (TestSort(v, n)==1)
            cout<<"Sortare reusita\n";
        else
            cout<<"Sortare nereusita\n";


        ///v pt ShellSort
        for(long long i = 0 ; i < n ; i ++)
            v[i]=random[i];
        start = chrono::system_clock::now();
        ShellSort(v, n);
        stop = chrono::system_clock::now();

        chrono::duration<double> elapsed_seconds2 = stop - start;

        cout  << "ShellSort\n"<<"Durata: " << elapsed_seconds2.count() << "s\n";
        if (TestSort(v, n)==1)
            cout<<"Sortare reusita\n";
        else
            cout<<"Sortare nereusita\n";


        ///v pt HeapSort
        for(long long i = 0 ; i < n ; i ++)
            v[i]=random[i];
        start = chrono::system_clock::now();
        HeapSort(v, n);
        stop = chrono::system_clock::now();

        chrono::duration<double> elapsed_seconds4 = stop - start;

        cout  << "HeapSort\n"<<"Durata: " << elapsed_seconds4.count() << "s\n";
        if (TestSort(v, n)==1)
            cout<<"Sortare reusita\n";
        else
            cout<<"Sortare nereusita\n";

        ///v pt RadixSort baza 2^16
        for(long long i = 0 ; i < n ; i ++)
            v[i]=random[i];
        start = chrono::system_clock::now();
        RadixSort(v, n, 65536);
        stop = chrono::system_clock::now();

        chrono::duration<double> elapsed_seconds1 = stop - start;

        cout  << "RadixSort baza 2^16\n"<<"Durata: " << elapsed_seconds1.count() << "s\n";
        if (TestSort(v, n)==1)
            cout<<"Sortare reusita\n";
        else
            cout<<"Sortare nereusita\n";

        ///v pt RadixSort baza 10
        for(long long i = 0 ; i < n ; i ++)
            v[i]=random[i];
        start = chrono::system_clock::now();
        RadixSort(v, n, 10);
        stop = chrono::system_clock::now();

        chrono::duration<double> elapsed_seconds5 = stop - start;

        cout  << "RadixSort baza 10\n"<<"Durata: " << elapsed_seconds5.count() << "s\n";
        if (TestSort(v, n)==1)
            cout<<"Sortare reusita\n";
        else
            cout<<"Sortare nereusita\n";

         ///v pt QuickSort pivot random
        for(long long i = 0 ; i < n ; i ++)
            v[i]=random[i];
        start = chrono::system_clock::now();
        QuickSort(v, 0, n-1);
        stop = chrono::system_clock::now();

        chrono::duration<double> elapsed_seconds3 = stop - start;

        cout  << "QuickSort pivot random\n"<<"Durata: " << elapsed_seconds3.count() << "s\n";
        if (TestSort(v, n)==1)
            cout<<"Sortare reusita\n";
        else
            cout<<"Sortare nereusita\n";

         ///v pt QuickSort mediana din 3
        for(long long i = 0 ; i < n ; i ++)
            v[i]=random[i];
        start = chrono::system_clock::now();
        QuickSortMed3(v, 0, n-1);
        stop = chrono::system_clock::now();

        chrono::duration<double> elapsed_seconds6 = stop - start;

        cout  << "QuickSort mediana din 3\n"<<"Durata: " << elapsed_seconds6.count() << "s\n";
        if (TestSort(v, n)==1)
            cout<<"Sortare reusita\n";
        else
            cout<<"Sortare nereusita\n";

        ///v pt STL Sort
        for(long long i = 0 ; i < n ; i ++)
            v[i]=random[i];
        start = chrono::system_clock::now();
        sort(v.begin(), v.end()-1);
        stop = chrono::system_clock::now();

        chrono::duration<double> elapsed_seconds7 = stop - start;

        cout  << "STLSort algoritmul nativ\n"<<"Durata: " << elapsed_seconds7.count() << "s\n";
        if (TestSort(v, n)==1)
            cout<<"Sortare reusita\n";
        else
            cout<<"Sortare nereusita\n";
    }

    return 0;
}
