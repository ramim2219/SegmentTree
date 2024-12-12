//Problem Link: https://cses.fi/problemset/task/1144
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std;

#define ll long long int
#define endl '\n'
#define fast ios_base::sync_with_stdio(false); cin.tie(NULL);

template<typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

int main() {
    fast;
    ll n, q;
    cin >> n >> q;

    vector<ll> arr(n);
    ordered_set<pair<ll, ll>> s;  // Stores {value, index}
    map<ll, ll> mp;              // Keeps track of current values by index

    // Input and initialization
    for (ll i = 0; i < n; i++) {
        cin >> arr[i];
        s.insert({arr[i], i});
        mp[i] = arr[i];
    }

    while (q--) {
        char ch;
        cin >> ch;

        if (ch == '!') {
            ll k, x;
            cin >> k >> x;
            k--;  // Convert to 0-based index

            ll oldVal = mp[k];
            s.erase({oldVal, k});  // Remove the old value
            s.insert({x, k});      // Insert the new value
            mp[k] = x;             // Update map
        } else if (ch == '?') {
            ll a, b;
            cin >> a >> b;

            // Count elements in range [a, b]
            ll k = s.order_of_key({a, 0});         // Count elements < a
            ll m = s.order_of_key({b + 1, 0});    // Count elements ≤ b
            cout << m - k << endl;
        }
    }

    return 0;
}
