#include <bits/stdc++.h>
#define ll long long int
#define endl '\n'
#define fast ios_base::sync_with_stdio(false);cin.tie(NULL);
using namespace std;

int main() {
    fast;
    ll n;
    cin >> n;
    vector<ll> a(n);
    map<ll, ll> frq,frq2;

    for (int i = 0; i < n; i++) {
        cin >> a[i];
        frq[a[i]]++;
        frq2[a[i]]++;
    }

    vector<ll>left,right;

    for (int i = n - 1,j=0; i >= 0 && j<n; i--,j++) {
        auto it = frq.find(a[i]);
        if (it != frq.end()) {
            ll distance_from_start = distance(frq.begin(), it);
            frq.erase(it);
            ll x=frq.size()-distance_from_start;
            left.push_back(x);
        }

        auto it2 = frq2.find(a[j]);
        if (it2 != frq2.end()){
            ll distance_from_start = distance(frq2.begin(), it2);
            frq2.erase(it2);
            ll x=distance_from_start;
            right.push_back(x);
        }
    }
    reverse(left.begin(), left.end());
    ll cnt=0;
    for(int i=0;i<n;i++)
        cnt+=(left[i]*right[i]);
    cout<<cnt<<endl;
    return 0;
}
