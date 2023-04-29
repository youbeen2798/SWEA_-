#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

int t;
int tc = 1;
int n; //세로 크기
int m; //가로 크기
int k; //배양 시간


struct cell {
	int x;
	int y;
	int now;
	int target;
};

vector<cell> inactive_cells; //비활성화 세포
vector<cell> active_cells; //활성화 세포
vector<cell> new_cells; //새로 추가된 비활성화 세포

set<pair<int, int>> cells;

int dx[4] = { 1,-1,0,0 };
int dy[4] = { 0,0,1,-1 };

void spread(int x, int y, int target) {

	for (int i = 0; i < 4; i++) {
		int nx = x + dx[i];
		int ny = y + dy[i];

		//이미 차지하고 있던 것이 없고 
		if (!cells.count({ nx, ny })) {

			bool found = false;
			for (int k = 0; k < new_cells.size(); k++) {
				if (new_cells[k].x == nx && new_cells[k].y == ny) {

					if (new_cells[k].target < target) {
						new_cells.push_back({ nx, ny, 1, target });
						found = true;
						break;
					}
					else if (new_cells[k].target == target) {
						found = true;
						break;
					}

				}
			}

			if (!found) {
				cells.insert({ nx,ny });
				new_cells.push_back({ nx,ny, 1, target });
			}
		}
	}
}
void one_second() {

	vector<cell> tmp_active_cells;
	vector<cell> tmp_inactive_cells;

	//활성화 먼저
	for (int i = 0; i < active_cells.size(); i++) {
		int x = active_cells[i].x;
		int y = active_cells[i].y;
		int now = active_cells[i].now;
		int target = active_cells[i].target;

		if (now == 1) {
			spread(x, y, target);
		}
		if (now < target) {
			tmp_active_cells.push_back({ x,y,now + 1, target });

		}
	}

	//비활성화
	for (int i = 0; i < inactive_cells.size(); i++) {
		int x = inactive_cells[i].x;
		int y = inactive_cells[i].y;
		int now = inactive_cells[i].now;
		int target = inactive_cells[i].target;

		if (now == target) {
			//활성화
	//		cout << "#3" << "\n";
			tmp_active_cells.push_back({ x,y,1,target });
		}
		else {
			//		cout << "#4" << "\n";
			tmp_inactive_cells.push_back({ x,y,now + 1, target });
		}
	}


	active_cells = tmp_active_cells;
	inactive_cells = tmp_inactive_cells;

	for (int i = 0; i < new_cells.size(); i++) {
		//	cells.insert({ new_cells[i].x, new_cells[i].y });
		inactive_cells.push_back(new_cells[i]);
	}

	new_cells.clear();

	//	print();
}


void solution() {

	for (int i = 0; i < k; i++) {
		one_second();
	}

	int ans = inactive_cells.size() + active_cells.size();
	cout << "#" << tc << " " << ans << "\n";


	inactive_cells.clear();
	active_cells.clear();
	new_cells.clear();
	cells.clear();
}
void input() {

	cin >> t;

	for (tc = 1; tc <= t; tc++) {
		cin >> n >> m >> k;
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				int num;
				cin >> num;
				if (num != 0) {
					cells.insert({ i,j });
					inactive_cells.push_back({ i,j, 1, num });
				}
			}
		}

		solution();
		//		cout << "#" << tc << " " << solution() << "\n";
	}
}
int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	input();
}