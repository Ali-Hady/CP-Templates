#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>
#include <string.h>
#include <string>
#define ll long long
#define el '\n'
#define Ali ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0)
#define inf 1e18
#define wedges vector<vector<pair<ll, ll>>> wedges
#define wpq priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, greater<>> wpq
using namespace std;

const ll N = 1e5 + 5;

vector<vector<pair<ll, ll>>> edges(N);
vector<ll> dist;
vector<bool> vis;

void dijkstra(ll s) {
    for (ll i = 0; i < dist.size(); ++i) {
        dist[i] = inf;
        vis[i] = 0;
    }

    priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, greater<>> pq;
    pq.push({0, s}); // cost, to
    dist[s] = 0;

    while (!pq.empty()) {
        ll cur = pq.top().second;
        pq.pop();

        if (vis[cur]) continue;
        vis[cur] = 1;

        for (auto ch: edges[cur]) {
            ll cost = dist[cur];
            if (cost + ch.second < dist[ch.first]) {
                dist[ch.first] = cost + ch.second;
                pq.push({dist[ch.first], ch.first});
            }
        }
    }
}

int main() {
    Ali;
    ll n, m, k;
    cin >> n >> m >> k;
    ll arr[n];
    dist.resize(n + 1);
    vis.resize(n + 1);
    for (ll i = 0; i < n; ++i) {
        cin >> arr[i];
    }

    for (ll i = 0; i < m; ++i) {
        ll u, v, w;
        cin >> u >> v >> w;
        --u, --v;
        edges[u].push_back({v, w}); // to, weight
        edges[v].push_back({u, w});
    }

    for (ll i = 0; i < n; ++i) {
        edges[n].push_back({i, arr[i]}); // special path
        edges[i].push_back({n, arr[i]});
    }

    for (ll i = 0; i < k; ++i) {
        ll x;
        cin >> x;
        --x;
        dijkstra(x);
        for (ll j = 0; j < n; ++j) {
            cout << dist[j] << " ";
        }
        cout << el;
    }

    return 0;
}
