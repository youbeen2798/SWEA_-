#include <iostream>
#include <algorithm>

using namespace std;

int t;
int n;
int map[21][21];
int real_ans = -1;

void update_ans(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4) {
	//(2,2), (3, 1), (4, 2), (3, 3)
	int ans[101] = { 0, };

	//왼쪽으로
	for (int x = x1, y = y1; y >= y2; x++, y--) {
		if (ans[map[x][y]] == 0) {
			ans[map[x][y]]++;
		}
		else {
			return;
		}
	}

	//오른쪽으로
	for (int x = x2 + 1, y = y2 + 1; x <= x3, y <= y3; x++, y++) {
		if (ans[map[x][y]] == 0) {
			ans[map[x][y]]++;
		}
		else {
			return;
		}
	}

	//위로
	for (int x = x3 - 1, y = y3 + 1; x >= x4, y <= y4; x--, y++) {
		if (ans[map[x][y]] == 0) {
			ans[map[x][y]]++;
		}
		else {
			return;
		}
	}

	for (int x = x4 - 1, y = y4 - 1; x > x1, y > y1; x--, y--) {
		if (ans[map[x][y]] == 0) {
			ans[map[x][y]]++;
		}
		else {
			return;
		}
	}

	int one_side = abs(x1 - x2) + 1;
	int other_side = abs(y1 - y4) + 1;

	int total_size = 2 * (one_side + other_side) - 4;

	real_ans = max(real_ans, total_size);
}
void make_rectangle(int top_x, int top_y) {
	//왼쪽으로

	int x1 = top_x;
	int y1 = top_y;

	int x2;
	int y2;
	int x3;
	int y3;
	int x4;
	int y4;

	for (int y = top_y - 1, x = top_x + 1; y >= 1; y--, x++) {
		x2 = x;
		y2 = y;


		for (int xx = x2 + 1, yy = y2 + 1; xx <= n; xx++, yy++) {
			x3 = xx;
			y3 = yy;

			x4 = x3 - (x2 - x1);
			y4 = y3 + (y1 - y2);

			if (1 <= x4 && x4 <= n && 1 <= y4 && y4 <= n) {
				update_ans(x1, y1, x2, y2, x3, y3, x4, y4);
			}
		}
	}
}
void solution() {
	real_ans = -1;

	for (int i = 1; i < n; i++) {
		for (int j = 2; j < n; j++) {
			//	cout << "시작: " << i << " " << j << "\n";
			make_rectangle(i, j);
		}
	}
}
void input() {
	cin >> t;

	for (int tc = 1; tc <= t; tc++) {
		cin >> n;

		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				cin >> map[i][j];
			}
		}

		solution();
		cout << "#" << tc << " " << real_ans << "\n";
	}
}
int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	input();
}