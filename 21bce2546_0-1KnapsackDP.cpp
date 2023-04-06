#include<iostream>
using namespace std;

int main()
{
    int n,m;
    cout<<"Enter Knapsack Capacity : ";
    cin>>m;
    cout<<endl<<"Enter Number of Objects : ";
    cin>>n;

    int w[n+1];
    int p[n+1];

    w[0]=0;
    p[0]=0;
    cout<<"Input Weight Array"<<endl;
    for(int i=1;i<n+1;i++)
    {
        cin>>w[i];
    }
    
    cout<<endl<<"Input Profit Array"<<endl;
    for(int i=1;i<n+1;i++)
    {
        cin>>p[i];
    }

    int dp[n+1][m+1];
    for(int i=0;i<n+1;i++)
    {
        for(int j=0;j<m+1;j++)
        {
            if(i==0 || j==0)
            {
                dp[i][j]=0;
            }
        }
    }

    for(int i=1;i<n+1;i++)
    {
        for(int j=1;j<m+1;j++)
        {
            int a=0,b=-1;
            a=dp[i-1][j]; // object not included
            if(j-w[i]>=0)
            {
                b=dp[i-1][j-w[i]]+p[i];// object is included
            }
            if(a>b || a==b)
            {
                dp[i][j]=a;
            }
            if(a<b)
            {
                dp[i][j]=b;
            }

        }
    }
    cout<<"Table"<<endl;
    for(int i=0;i<n+1;i++)
    {
        for(int j=0;j<m+1;j++)
        {
            cout<<dp[i][j]<<" ";
        }
        cout<<endl;
    }
    int p_max=dp[n][m];
    cout<<endl<<"Max Profit = "<<p_max<<endl;

    int x[n+1];
    // Now finding optimal solution 

    for(int i=n;i>=0;i--)
    {
        int c=0;
        for(int j=m;j>=0;j--)
        {
            if(p_max==dp[i][j])
            {
                c++;
                break;
            }
        }
        if(c==1)
        {
            for(int j=m;j>=0;j--)
            {
                if(p_max==dp[i-1][j])
                {
                    c++;
                    break;
                }
            }
            if(c==2)
            {
                x[i]=0;
            }
            else
            {
                x[i]=1;
                if(p_max>0)
                {
                    p_max=p_max-w[i];
                }
                else
                {
                    p_max=0;
                }
            }
        }
    }
    cout<<endl<<"Optimal Solution"<<endl;
    for(int i=1;i<n+1;i++)
    {
        cout<<x[i]<<" ";
    }



}