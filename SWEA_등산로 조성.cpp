#include <iostream>
#include <queue>
#include <vector>
#include <cstring>

using namespace std;

int t;
int n, k;
int arr[9][9];
bool visited[9][9];

int ans = 0;
int tmp_ans = 0;
int max_height; //현재 등산로 중에서 가장 높은 봉우리 높이

int dx[4] = { 0,0,1,-1 };
int dy[4] = { 1,-1,0,0 };
bool cut = false;
int tc;

void bfs(int x, int y, int num) {

	if (tmp_ans < num) {
		tmp_ans = num;
	}
	tmp_ans = max(tmp_ans, num);

	for (int i = 0; i < 4; i++) {
		int nx = x + dx[i];
		int ny = y + dy[i];

		if (1 <= nx && nx <= n && 1 <= ny && ny <= n && !visited[nx][ny]) {

			int height_diff = arr[x][y] - arr[nx][ny]; //높이 차이
			int abs_height_diff = abs(height_diff);

			if (height_diff > 0) { //더 낮아진다면
				visited[nx][ny] = true;

				bfs(nx, ny, num + 1);

				visited[nx][ny] = false;
			}
			else if (height_diff == 0 && !cut) { //높이가 같으면서, cut을 하지 않았다면
				visited[nx][ny] = true;
				cut = true;
				arr[nx][ny] -= 1;

				bfs(nx, ny, num + 1);

				visited[nx][ny] = false;
				cut = false;
				arr[nx][ny] += 1;
			}
			else if (abs_height_diff + 1 <= k && !cut) {
				visited[nx][ny] = true;
				cut = true;
				arr[nx][ny] -= (abs_height_diff + 1);

				bfs(nx, ny, num + 1);

				visited[nx][ny] = false;
				cut = false;
				arr[nx][ny] += (abs_height_diff + 1);
			}
		}
	}

}
void solution() {

	ans = 0;

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (arr[i][j] == max_height) {
				tmp_ans = 0;
				cut = false;
				memset(visited, false, sizeof(visited));
				visited[i][j] = true;
				bfs(i, j, 1);
				ans = max(ans, tmp_ans);
			}
		}
	}

	cout << "#" << tc << " " << ans << "\n";
}

void input() {

	cin >> t;

	for (tc = 1; tc <= t; tc++) {
		cin >> n >> k;

		max_height = 0;
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				cin >> arr[i][j];
				max_height = max(max_height, arr[i][j]);
			}
		}

		solution();
	}
}
int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	input();
}
