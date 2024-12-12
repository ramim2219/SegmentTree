//problem Link: https://codeforces.com/edu/course/2/lesson/4/1/practice/contest/273169/problem/A
#include<bits/stdc++.h>
#define ll long long int
#define endl '\n'
#define fast ios_base::sync_with_stdio(false); cin.tie(NULL);
using namespace std;

void build(ll ind,ll low,ll high,ll arr[],vector<ll>&seg) {
    if(low == high)
    {
        seg[ind]=arr[low];
        return;
    }
    ll mid=(low+high)/2;
    build(2*ind+1,low,mid,arr,seg);
    build(2*ind+2,mid+1,high,arr,seg);
    seg[ind]=seg[2*ind+1]+seg[2*ind+2];
}

ll query(ll ind, ll low, ll high, ll l, ll r, vector<ll>& seg) {
    // No overlap
    if (r < low || high < l) {
        return 0;
    }
    // Complete overlap
    if (low >= l && high <= r) {
        return seg[ind];
    }
    // Partial overlap
    ll mid = (low + high) / 2;
    ll left = query(2 * ind + 1, low, mid, l, r, seg);
    ll right = query(2 * ind + 2, mid + 1, high, l, r, seg);
    return left + right;
}

void update(ll ind, ll low, ll high, ll i, ll val, vector<ll>& seg) {
    if (low == high) {
        seg[ind] = val;
        return;
    }
    ll mid = (low + high) / 2;
    if (i <= mid) {
        update(2 * ind + 1, low, mid, i, val, seg);
    } else {
        update(2 * ind + 2, mid + 1, high, i, val, seg);
    }
    seg[ind] = seg[2 * ind + 1] + seg[2 * ind + 2];
}

int main() {
    fast;
    ll n, q;
    cin>>n>>q;
    ll arr[n + 5];
    for (ll i = 0; i < n; i++)cin>>arr[i];
    vector<ll> seg(4 * n, 0);
    build(0, 0, n - 1, arr, seg);

    for (int i = 0; i < q; i++) {
        ll type, l, r;
        cin >> type;
        if (type == 2) {
            cin >> l >> r;
            cout << query(0, 0, n - 1, l, r - 1, seg) << endl;
        } else if (type == 1) {
            ll pos, val;
            cin >> pos >> val;
            update(0, 0, n - 1, pos, val, seg);
            arr[pos] = val;
        }
    }
    return 0;
}
