#include "submit.h"
#include <bits/stdc++.h>

extern int ai_side;
std::string ai_name = "RagnarRoss";

const int P1 = 1;
const int P2 = 2;
const int WALL = 3;
const int INF = 100000;

template<class T>
inline bool relax(T &x, T y) {
	return x > y ? x = y, 1 : 0;
}

int locx, locy;
int elocx, elocy;
int dir, edir;

int n = 10;
int board[20][20];

std::vector<std::pair<int, int> > my_aim;

inline bool in_board(int x, int y) {
	return (1 <= x && x <= 19 && 1 <= y && y <= 19);
}

void init() {
	if (ai_side == 0) {
		locx = 2;
		locy = 10;
		edir = -1;
		elocx = 18;
		elocy = 10;
		for(int x = 18, y = 2; y < 20; y += 2)
			my_aim.push_back(std::make_pair(x, y));
	} else {
		locx = 18;
		locy = 10;
		edir = 1;
		elocx = 2;
		elocy = 10;
		for(int x = 2, y = 2; y < 20; y += 2)
			my_aim.push_back(std::make_pair(x, y));
	}
}

void GetUpdate(std::pair<int, int> location) {
	if(location.first % 2 == 0 && location.second % 2 == 0) {
		elocx = location.first;
		elocy = location.second;
	} else if(location.first % 2) {
		for(int y = location.second; y <= location.second + 2; y++) {
			board[location.first][y] = WALL;
		}
	} else if(location.second % 2) {
		for(int x = location.first; x <= location.first + 2; x++) {
			board[x][location.second] = WALL;
		}
	} else {
		Debug("WTF!!!");
	}
}

bool place_wall(std::pair<int, int> &res) {
	if(elocy + 2 <= 19
			&& board[elocx + edir][elocy] != WALL
			&& board[elocx + edir][elocy + 1] != WALL
			&& board[elocx + edir][elocy + 2] != WALL) {
		res.first = elocx + edir;
		res.second = elocy;
		for(int y = 0; y <= 2; y++)
			board[res.first][res.second + y] = WALL;
		return true;
	}
	return false;
}

inline int get_id(int x, int y) {
	return x * 20 + y;
}
inline int get_id(std::pair<int, int> p) {
	return p.first * 20 + p.second;
}

std::pair<int, int> cur;

int try_move(int x, int y) {
//	std::cout << x << " " << y << std::endl;
	if(x == elocx && y == elocy) {
		int t = try_move(2 * x - locx, 2 * y - locy);
		if(t != INF) {
			cur = std::make_pair(2 * x - locx, 2 * y - locy);
			return t;
		} else {
			if(x != locx) {
				int a = try_move(x, y + 2), b = try_move(x, y - 2);
				if(a < b) {
					cur = std::make_pair(x, y + 2);
					return a;
				} else {
					cur = std::make_pair(x, y - 2);
					return b;
				}
			} else {
				int a = try_move(x + 2, y), b = try_move(x - 2, y);
				if(a < b) {
					cur = std::make_pair(x + 2, y);
					return a;
				} else {
					cur = std::make_pair(x - 2, y);
					return b;
				}
			}
		}
	}
	cur = std::make_pair(x, y);
	if(!in_board(x, y)) {
		return INF;
	}

	std::queue<int> q;
	std::vector<int> dist(400, INF);
	for(auto x: my_aim) {
		q.push(get_id(x));
		dist[get_id(x)] = 0;
	}
	static const int dx[] = {0, 0, 2, -2};
	static const int dy[] = {2, -2, 0, 0};
	static const int dwx[] = {0, 0, 1, -1};
	static const int dwy[] = {1, -1, 0, 0};
	while(!q.empty()) {
		int x = q.front() / 20;
		int y = q.front() % 20;
		q.pop();
		for(int k = 0; k < 4; k++) {
			int nx = x + dx[k], wx = x + dwx[k];
			int ny = y + dy[k], wy = y + dwy[k];
			if(in_board(nx, ny) && board[wx][wy] != WALL && dist[get_id(nx, ny)] == INF) {
				q.push(get_id(nx, ny));
				dist[get_id(nx, ny)] = dist[get_id(x, y)] + 1;
			}
		}
	}
	return dist[get_id(x, y)];
}

std::pair<int, int> move() {
	int dis = INF;
	std::pair<int, int> res;
	if(board[locx + 1][locy] != WALL && relax(dis, try_move(locx + 2, locy))) {
		res = cur;
	}
	if(board[locx][locy + 1] != WALL && relax(dis, try_move(locx, locy + 2))) {
		res = cur;
	}
	if(board[locx - 1][locy] != WALL && relax(dis, try_move(locx - 2, locy))) {
		res = cur;
	}
	if(board[locx][locy - 1] != WALL && relax(dis, try_move(locx, locy - 2))) {
		res = cur;
	}
	locx = res.first;
	locy = res.second;
	return res;
}

std::pair<int, int> Action() {
	std::pair<int, int> res;
	if(n && place_wall(res)) {
		n--;
		return res;
	} else {
		return move();
	}
}

