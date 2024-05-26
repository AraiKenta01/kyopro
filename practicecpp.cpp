#include <bits/stdc++.h>
#define int long long
using namespace std;
struct Node{
	int l, r, x;
} q[50005];
int T, n, k, f[50005], dp[50005], a[50005], s1[50005], s2[50005];
int calc(int x, int y){ 
	if(x == 0) return y * s1[y] - s2[y];
	if(y == n + 1) return s2[n] - s2[x - 1] - x * (s1[n] - s1[x - 1]);
	int mid = (x + y) / 2;
	return dp[x] + s2[mid] - s2[x - 1] - x * (s1[mid] - s1[x - 1]) - (s2[y] - s2[mid]) + y * (s1[y] - s1[mid]);
}
int chk(int x, int ff){
	int hh = 1, tt = 0;
	q[++tt] = {1, n, 0};
	for(int i = 1; i <= n; i++){
		while(q[hh].r < i) hh++;
		dp[i] = calc(q[hh].x, i) + x; f[i] = f[q[hh].x] + 1;
		while(tt >= hh && (calc(q[tt].x, q[tt].l) >= calc(i, q[tt].l))) tt--;
		int l = q[tt].l, r = q[tt].r;
		while(l < r){
			int mid = l + r + 1 >> 1;
			if(calc(q[tt].x, mid) >= calc(i, mid)) r = mid - 1;
			else l = mid;
		}
		q[tt].r = l; 
		if(l < n) q[++tt] = {l + 1, n, i};
	}

    //aaaaaaaa
	int id = 0, mn = 1e18;
	for(int i = 1; i <= n; i++)
		if(mn > dp[i] + calc(i, n + 1))
			mn = dp[i] + calc(i, n + 1), id = i;
	if(ff) cout << mn - k * x << '\n';
	return f[id];
}
signed main(){
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cin >> n >> k;
	for(int i = 1; i <= n; i++) cin >> a[i], s1[i] = s1[i - 1] + a[i], s2[i] = s2[i - 1] + a[i] * i;
	int l = 0, r = 1e11;
	while(l < r){
		int mid = l + r + 1 >> 1;
		if(chk(mid, 0) >= k) l = mid;
		else r = mid - 1;
	}
	chk(l, 1);
	return 0;
}