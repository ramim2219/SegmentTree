//Problem Link: https://codeforces.com/edu/course/2/lesson/4/3/practice/contest/274545/problem/A
#include<bits/stdc++.h>
#define ll long long int
#define endl '\n'
#define fast ios_base::sync_with_stdio(false); cin.tie(NULL);
using namespace std;

vector<int> seg; // Segment tree array
int n;           // Size of the original array

// Build the segment tree
void build(int ind, int low, int high, const vector<int>& arr) {
    if (low == high) {
        seg[ind] = arr[low];
        return;
    }
    int mid = (low + high) / 2;
    build(2 * ind + 1, low, mid, arr);
    build(2 * ind + 2, mid + 1, high, arr);
    seg[ind] = seg[2 * ind + 1] + seg[2 * ind + 2]; // for finding summation
}

// Query the segment tree
int query(int ind, int low, int high, int l, int r) {
    // No overlap
    if (r < low | high < l) {
        return 0; // for finding summation
    }
    // Complete overlap
    if (low >= l && high <= r) return seg[ind];

    int mid = (low + high) / 2;
    int left = query(2 * ind + 1, low, mid, l, r);
    int right = query(2 * ind + 2, mid + 1, high, l, r);
    return left + right; // for finding summation
}

// Update a value in the segment tree
void update(int ind, int low, int high, int i, int val) {
    if (low == high) {
        seg[ind] = val;
        return;
    }
    int mid = (low + high) >> 1;
    if (i <= mid) update(2 * ind + 1, low, mid, i, val);
    else update(2 * ind + 2, mid + 1, high, i, val);
    seg[ind] = seg[2 * ind + 1] + seg[2 * ind + 2]; // for finding summation
}

int main() {
    fast;
    int n, q;
    cin >> n ;
    vector<int> arr(n),frq(n+5,0);
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
        frq[arr[i]]++;
    }

    seg.resize(4*n);
    build(0, 0, n, frq);
    stack<int>ans;
    for(int i=n-1;i>=0;i--)
    {
        int l;
        l=arr[i]+1;
        int cnt=query(0,0,n,l,n);
        ans.push(cnt);
        update(0,0,n,arr[i],frq[arr[i]]-1);
        frq[arr[i]]-=1;
    }
    while(!ans.empty())
    {
        cout<<ans.top()<<" ";
        ans.pop();
    }
//    for (int i=1;i<=n ; i++)
//        cout<<frq[i]<<endl;

    return 0;
}

