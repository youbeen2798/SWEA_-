#include <iostream>
#include <vector>

using namespace std;

int t; //테스트 케이스 개수
int n; //한변길이
int m; //가로길이
int c; //최대 양
int map[11][11];
int profit[11][11]; 
bool visited[11][11];
int max_tmp_profit = 0; 
int ans = 0;

void combination(vector<pair<int, int>> arr, vector<pair<int, int>> comb, int r, int idx, int depth) {
	if (r == 0) {
		int tmp_profit = 0;
		int tmp_sum = 0;
		for (int i = 0; i < comb.size(); i++) {
			int num = map[comb[i].first][comb[i].second];
			tmp_sum += num;
			tmp_profit += num * num;
		}
		if (tmp_sum <= c) {
			max_tmp_profit = max(max_tmp_profit, tmp_profit);
		}
		return;
	}
	else if (arr.size() == depth) {
		return;
	}
	else {
		comb[idx] = arr[depth];
		combination(arr, comb, r - 1, idx + 1, depth + 1);
		combination(arr, comb, r, idx, depth + 1);
	}
}
int make_profit(int x, int y) {
	//(x,y) 이익
	vector<pair<int, int>> v;
	int sum = 0;
	int profit = 0;
	for (int j = y; j < y + m; j++) {
		v.push_back({ x,j });
		sum += map[x][j];
		profit += map[x][j] * map[x][j];
	}

	if (sum <= c) {
		return profit;
	}

	max_tmp_profit = 0;
	
	for (int r = m - 1; r >= 1; r--) {
		vector<pair<int, int>> comb(r);
		combination(v, comb, r, 0, 0);
	}
	return max_tmp_profit;
}

int find_other_man_profit(int x, int y) {

	int max_col = n - m + 1;
	int other_man_profit = 0;

	for (int j = y + m; j <= max_col; j++) {
		other_man_profit = max(other_man_profit, profit[x][j]);
	}

	for (int i = x + 1; i <= n; i++) {
		for (int j = 1; j <= max_col; j++) {
			other_man_profit = max(other_man_profit, profit[i][j]);
		}
	}

	return other_man_profit;
}
void solution() {

	int max_col = n - m + 1;
	ans = 0;


	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= max_col; j++) {
			profit[i][j] = make_profit(i, j);
		}
	}

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= max_col; j++) {
			int one_man = profit[i][j];
			for (int k = j; k < m + j; k++) {
				visited[i][k] = true;
			}
			int other_man = find_other_man_profit(i,j);
			for (int k = j; k < m + j; k++) {
				visited[i][k] = false;
			}
			ans = max(ans, one_man + other_man);
		}
	}
}

void input() {

	cin >> t;

	for (int tc = 1; tc <= t; tc++) {
		cin >> n >> m >> c;

		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				cin >> map[i][j];
			}
		}
		solution();
		cout << "#" << tc << " " << ans << "\n";
	}
	
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	input();
	solution();
}