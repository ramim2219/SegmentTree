//Problem Link: https://codeforces.com/edu/course/2/lesson/4/1/practice/contest/273169/problem/C
#include<bits/stdc++.h>
#define ll long long int
#define endl '\n'
#define fast
#define MOD 1000000000
#define fast ios_base::sync_with_stdio(false); cin.tie(NULL);
using namespace std;

vector<pair<ll,ll>> seg; // Segment tree array
ll n;           // Size of the original array

// Build the segment tree
void build(ll ind, ll low, ll high, const vector<ll>& arr){
    if (low == high) {
        seg[ind].first = arr[low];
        seg[ind].second = 1;
        return;
    }
    ll mid = (low + high) / 2;
    build(2 * ind + 1, low, mid, arr);
    build(2 * ind + 2, mid + 1, high, arr);

    if(seg[2*ind+1].first>seg[2*ind+2].first)
    {
        seg[ind].first=seg[2*ind+2].first;
        seg[ind].second=seg[2*ind+2].second;
    }
    else if(seg[2*ind+1].first<seg[2*ind+2].first)
    {
        seg[ind].first=seg[2*ind+1].first;
        seg[ind].second=seg[2*ind+1].second;
    }
    else
    {
        seg[ind].first=seg[2*ind+1].first;
        seg[ind].second=seg[2*ind+2].second+seg[2*ind+1].second;
    }
}

// Query the segment tree
pair<ll,ll> query(ll ind,ll low, ll high, ll l, ll r) {
    // No overlap
    if (r < low || high < l) {
        return {MOD,-1}; // for finding summation
    }
    // Complete overlap
    if (low >= l && high <= r) return seg[ind];
    ll mid = (low + high) / 2;
    pair<ll,ll> left = query(2 * ind + 1, low, mid, l, r);
    pair<ll,ll> right = query(2 * ind + 2, mid + 1, high, l, r);
    pair<ll,ll>q;
    if(left.first<right.first)q=left;
    else if(left.first>right.first)q=right;
    else
    {
        q.first = left.first;
        q.second = left.second+right.second;
    }
    return q; // for finding minimum
}

// Update a value in the segment tree
void update(ll ind, ll low, ll high, ll i, ll val) {
    if (low == high) {
        seg[ind].first = val;
        seg[ind].second = 1;
        return;
    }
    ll mid = (low + high) >> 1;
    if (i <= mid) update(2 * ind + 1, low, mid, i, val);
    else update(2 * ind + 2, mid + 1, high, i, val);
    if(seg[2*ind+1].first>seg[2*ind+2].first)
    {
        seg[ind].first=seg[2*ind+2].first;
        seg[ind].second=seg[2*ind+2].second;
    }
    else if(seg[2*ind+1].first<seg[2*ind+2].first)
    {
        seg[ind].first=seg[2*ind+1].first;
        seg[ind].second=seg[2*ind+1].second;
    }
    else
    {
        seg[ind].first=seg[2*ind+1].first;
        seg[ind].second=seg[2*ind+2].second+seg[2*ind+1].second;
    }
}

int main(){
    fast;
    ll n, q;
    cin >> n >> q;
    vector<ll> arr(n);
    for (ll i = 0; i < n; i++) cin >> arr[i];

    seg.resize(4 * n);
    build(0, 0, n - 1, arr);

    for (ll i = 0; i < q; i++) {
        ll type, l, r;
        cin >> type;
        if (type == 2) {
            cin >> l >> r;
            pair<ll,ll>ans = query(0, 0, n - 1, l, r-1) ;
            cout << ans.first<<" "<<ans.second<< endl;
        } else if (type == 1) {
            ll pos, val;
            cin >> pos >> val;
            update(0, 0, n - 1, pos, val);
            arr[pos] = val;
        }
    }
    return 0;
}
