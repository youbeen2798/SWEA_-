#include <iostream>
#include <queue>
#include <cstring>

using namespace std;

int t, n, m;
int map[21][21];
bool visited[21][21];
int ans = 0;

//센터와 밑이 차이가 (k - 1)

int dx[4] = { 1,-1,0,0 };
int dy[4] = { 0,0,1,-1 };


bool inrange(int x, int y) {
	if (1 <= x && x <= n && 1 <= y && y <= n) {
		return true;
	}
	return false;
}
void make_center(int x, int y, int k) {

	int home_cnt = 0;

	int start_y = y - (k - 1);
	int end_y = y + (k - 1);

	//center 행
	for (int ny = start_y; ny <= end_y; ny++) {
		if (inrange(x, ny) && map[x][ny]) {
			home_cnt++;
		}
	}

	//top부터 center 바로 윗 행까지
	int top_x = x - (k - 1);

	for (int i = 0; i < k - 1; i++) {
		start_y = y - i;
		end_y = y + i;
		for (int j = start_y; j <= end_y; j++) {
			if (inrange(top_x, j) && map[top_x][j]) {
				home_cnt++;
			}
		}
		top_x++;
	}

	//bottom부터 center 바로 아래 행까지
	int bottom_x = x + (k - 1);

	for (int i = 0; i < k - 1; i++) {
		start_y = y - i;
		end_y = y + i;
		for (int j = start_y; j <= end_y; j++) {
			if (inrange(bottom_x, j) && map[bottom_x][j]) {
				home_cnt++;
			}
		}
		bottom_x--;
	}
	

	int 운영비용 = k * k + (k - 1) * (k - 1);
	int 수익 = m * home_cnt; //3 * 9 = 27
	int 이익 = 수익 - 운영비용; //36

	if (이익 >= 0) {
		ans = max(home_cnt, ans);
	}
}
void center(int x, int y) {
	//(x,y)에서 center일 때

	int max_k = 2 * n;

	for (int i = 1; i <= max_k; i++) {
		make_center(x, y, i);
	}
}
void solution() {


	ans = 0;

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			center(i, j);
		}
	}
}

void input() {

	cin >> t;

	for (int tc = 1; tc <= t; tc++) {
		cin >> n >> m;

		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				cin >> map[i][j];
			}
		}

		solution();

		cout << "#" << tc <<" " << ans << "\n";
	}
	
}
int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	input();
}
