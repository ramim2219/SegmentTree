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
    //seg[ind] = min(seg[2 * ind + 1], seg[2 * ind + 2]); // for finding minimum
    seg[ind] = seg[2 * ind + 1] + seg[2 * ind + 2]; // for finding summation
}

// Query the segment tree
int query(int ind, int low, int high, int l, int r) {
    // No overlap
    if (r < low | high < l) {
        // return INT_MAX; // for finding minimum
        return 0; // for finding summation
    }
    // Complete overlap
    if (low >= l && high <= r) return seg[ind];

    int mid = (low + high) / 2;
    int left = query(2 * ind + 1, low, mid, l, r);
    int right = query(2 * ind + 2, mid + 1, high, l, r);
    // return min(left, right); // for finding minimum
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
    // seg[ind] = min(seg[2 * ind + 1], seg[2 * ind + 2]); // for finding minimum
    seg[ind] = seg[2 * ind + 1] + seg[2 * ind + 2]; // for finding summation
}

int main() {
    fast;
    int n, q;
    cin >> n >> q;
    vector<int> arr(n);
    for (int i = 0; i < n; i++) cin >> arr[i];

    seg.resize(4 * n);
    build(0, 0, n - 1, arr);

    for (int i = 0; i < q; i++) {
        int type, l, r;
        cin >> type;
        if (type == 1) {
            cin >> l >> r;
            cout << query(0, 0, n - 1, l, r) << endl;
        } else if (type == 2) {
            int pos, val;
            cin >> pos >> val;
            update(0, 0, n - 1, pos, val);
            arr[pos] = val;
        }
    }
    return 0;
}

