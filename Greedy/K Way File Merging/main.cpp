#include <cstdio>
#include <iostream>
#include <vector>
#include <map>
#include <list>
#include <algorithm>
#include <set>
#include <utility>
#include <queue>
#include <cstring>
#include <sstream>

#define SIZE 41

using namespace std;
typedef long long LLD;
typedef pair<int, int> Node;
int n, m;

int main()
{
    int t, tc, i, j, k, x, y;

    scanf("%d", &tc);

    for(int t = 1; t <= tc; t++) {
        priority_queue <long long, vector<long long>, greater<long long> > q;
        scanf("%d %d", &n, &k);

        for(i = 0; i < n; i++) {
            scanf("%d", &x);
            q.push(x);
        }

        long long ans = 0;
        long long temp = 0;

        int mod = (k - 2) - (n - 2) % (k - 1);

        while(mod--)
            q.push(0LL);

        while(q.size() > 1) {
            temp = 0;
            int cnt = min(k, (int)q.size());
            for(i = 0; i < cnt; i++) {
                temp += q.top();
                q.pop();
            }
            ans += temp;
            q.push(temp);
        }
        printf("Case %d: %lld\n", t, ans);
    }
    return 0;
}