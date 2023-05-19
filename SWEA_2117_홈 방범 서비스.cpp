#include <iostream>
#include <queue>

using namespace std;

int t;
int n, m;
int map[21][21];
int ans = 0;

bool inrange(int x, int y) {
	if (1 <= x && x <= n && 1 <= y && y <= n) {
		return true; 
	}
	return false; 
}

void center(int x, int y, int k) {
	
	//같은 행

	int cnt = 0;
	if (map[x][y]) {
		cnt++;
	}
	for (int i = 1; i < k; i++) {

		int ny = y - i;
		if (inrange(x, ny) && map[x][ny]) {
			cnt++;
		}
		ny = y + i; 
		if (inrange(x, ny) && map[x][ny]){
			cnt++;
		}
	}
	
	//다른 행
	int num = k - 2;


	for (int i = 1; i < k; i++) {
		int nx = x - i;
		//위 행
		if (inrange(nx, y) && map[nx][y]) {
			cnt++;
		}
		for (int j = 1; j <= num; j++) {
			int ny = y + j;

			if (inrange(nx,ny) && map[nx][ny]) {
				cnt++;
			}
			ny = y - j;
			if (inrange(nx, ny) && map[nx][ny]) {
				cnt++;
			}
		}
		num--;
	}

	num = k - 2;

	for (int i = 1; i < k; i++) {

		int nx = x + i;

		//아래 행
		if (inrange(nx, y) && map[nx][y]) {
			cnt++;
		}

		for (int j = 1; j <= num; j++) {
			int ny = y + j;

			if (inrange(nx, ny) && map[nx][ny]) {
				cnt++;
			}
			ny = y - j;
			if (inrange(nx, ny) && map[nx][ny]) {
				cnt++;
			}
		}
		num--;
	}

	int 운영비용 = k * k + (k - 1) * (k - 1);
	int 수익 = cnt * m;
	int 이익 = 수익 - 운영비용;

	if (이익 >= 0) {
		ans = max(ans, cnt);
	}
}

void solution() {

	int max_k = n * n;

	ans = 0;
	for (int k = 1; k <= max_k; k++) {
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				center(i, j, k);
			}
		}
	}
}

void input() {

	cin >> t;

	for(int tc = 1; tc <= t; tc++) {
		cin >> n >> m;

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
