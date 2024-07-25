const int INF = 1e9;
int tsp(vector<vector<int>> &d) { 
	int n = d.size();
	vector<vector<int>> dp(1 << n, vector<int>(n, INF));
 
	for (int i = 0; i < n; i++) dp[1 << i][i] = 0;
 
	for (int mask = 0; mask < (1 << n); mask++) {
		for (int i = 0; i < n; i++) if (mask & (1 << i)) {
			for (int j = 0; j < n; j++) if (!(mask & (1 << j))) {
				dp[mask | (1 << j)][j] = min(dp[mask | (1 << j)][j], dp[mask][i] + d[i][j]);
			}
		}
	}
 
	return *min_element(dp.back().begin(), dp.back().end());
}
