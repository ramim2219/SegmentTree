#include<bits/stdc++.h>
#define ll long long int
#define endl '\n'
#define fast ios_base::sync_with_stdio(false);cin.tie(NULL);
using namespace std;
int main()
{
    fast;
    int n;
    cin>>n;
    vector<ll>a(n);
    ll cnt=0;
    for(int i=0;i<n;i++)cin>>a[i];
    for(int i=0;i<n;i++)
    {
        for(int j=i+1;j<n;j++)
        {
            if(a[j]<a[i])
            {
                for(int k=j+1;k<n;k++)
                {
                    if(a[k]<a[j])cnt++;
                }
            }
        }
    }
    cout<<cnt<<endl;
    return 0;
}
