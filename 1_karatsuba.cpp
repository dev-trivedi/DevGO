#include<stdio.h>
#include<iostream>
#include<math.h>
using namespace std;

long long karatsuba(long a,long b)
{
    if(a<10 || b<10)
    {
        return (a*b);
    }

    long long n=max(to_string(a).length(),to_string(b).length());
    long long m=n/2;

    long long a1=a/pow(10,m);
    long long a2=a%long(pow(10,m));

    long long b1=b/pow(10,m);
    long long b2=b%long(pow(10,m));

    long long A=karatsuba(a1,b1);
    long long B=karatsuba(a2,b2);
    long long C=karatsuba((a1+a2),(b1+b2));

    long long D=C-B-A;

    long long ab=A*pow(10,n)+D*pow(10,n/2)+B;
    return ab;
}

int main()
{
    int a,b;
    cout<<"Enter A : ";
    cin>>a;
    cout<<"Enter B : ";
    cin>>b;
    cout<<"Result : "<<karatsuba(a,b);
}

// Dev Trivedi
// 21BCE2546