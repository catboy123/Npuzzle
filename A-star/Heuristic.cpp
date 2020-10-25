#include "Heuristic.h"
int Euclide::calc(int n, int** A, int** B) {
	static int res;
	static ii* pos = NULL;
	if (pos == NULL) {
		pos = new ii[n * n + 1];
	}
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			pos[A[i][j]] = mkp(i, j);
		}
	}
	res = 0;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			static int x, y, val;
			val = B[i][j];
			x = pos[val].fi;
			y = pos[val].se;
			res += sqrt((i - x) * (i - x) + (j - y) * (j - y));
		}
	}
	return res;
}//*/
int Manhattan::calc(int n, int** A, int** B) {
	static int res;
	static ii* pos = NULL;
	if (pos == NULL) {
		pos = new ii[n * n + 1];
	}
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			pos[A[i][j]] = mkp(i, j);
		}
	}
	res = 0;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			static int x, y, val;
			val = B[i][j];
			x = pos[val].fi;
			y = pos[val].se;
			res += abs(i - x) + abs(j - y);
		}
	}
	return res;
}//*/

int MisplacedTiles::calc(int n, int** A, int** B) {
	static int res;
	static ii* pos = NULL;
	if (pos == NULL) {
		pos = new ii[n * n + 1];
	}
	res = 0;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			if (A[i][j] != B[i][j]) {
				res++;
			}
		}
	}
	return res;
}//*/

int LinearConflict::calc(int n, int** A, int** B) {
	static int res,cnt;
	static ii* posA = NULL;
	static ii* posB = NULL;
	if (posA == NULL) {
		posA = new ii[n * n + 1];
		posB = new ii[n * n + 1];
	}
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			posA[A[i][j]] = mkp(i, j);
		}
	}
	res = 0;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			static int x, y, val;
			val = B[i][j];
			x = posA[val].fi;
			y = posA[val].se;
			res += abs(i - x) + abs(j - y);
			posB[B[i][j]] = mkp(i, j);
		}
	}
	cnt = 0;
	for (int i = 1; i < n*n; ++i) {
		for (int j = 1; j < n * n; ++j) {
			if (i < j) {
				static int xA, yA, xB, yB;
				static int dual;
				if (posA[i] == posB[j]) {
					break;
				}
				dual = 0;
				xA = posA[i].fi;
				yA = posA[i].se;
				xB = posB[i].fi;
				yB = posB[i].se;
				if (xA == xB || yA == yB) {
					dual++;
				}
				xA = posA[j].fi;
				yA = posA[j].se;
				xB = posB[j].fi;
				yB = posB[j].se;
				if (xA == xB || yA == yB) {
					dual++;
				}
				if (dual > 0) {
					cnt++;
				}
			}
		}
	}
	return res+2*cnt;
}//*/

int Gaschnig::calc(int n, int** A, int** B) {
	static int misstype,res;
	static ii _pos;
	static int** tmp=NULL;
	if (tmp == NULL) {
		tmp = new int* [n];
		for (int i = 0; i < n; ++i) {
			tmp[i] = new int[n];
		}
	}
	misstype = 0;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			if (A[i][j] != B[i][j]) {
				misstype++;
			}
			tmp[i][j] = A[i][j];
			if (A[i][j] == 0 ) {
				_pos.fi = i;
				_pos.se = j;
			}
		}
	}
	while (misstype != 0){
		static int itmp;
		static int x,y;
		x = _pos.fi;
		y = _pos.se;
		if (B[x][y]!=0){
			static ii posB;
			posB = mkp(x, y);
			for (int i = 0; i < n; ++i) {
				for (int j = 0; j < n; ++j) {
					if (tmp[i][j] == B[i][j]) {
						posB = mkp(i, j);
						break;
					}
				}
				if (posB != mkp(x, y)) {
					break;
				}
			}
			itmp = tmp[posB.fi][posB.se];
			tmp[x][y] = itmp;
			tmp[posB.fi][posB.se] = itmp;
			res++;
			_pos = posB;
			misstype--;
			if (B[_pos.fi][_pos.se]==0){
				misstype--;
			}
		}
		else {
			static ii posDiff;
			posDiff = mkp(x, y);
			for (int i = 0; i < n; ++i) {
				for (int j = 0; j < n; ++j) {
					if (tmp[i][j] != B[i][j]) {
						posDiff = mkp(i, j);
						break;
					}
				}
				if (posDiff != mkp(x, y)) {
					break;
				}
			}
			itmp = tmp[posDiff.fi][posDiff.se];
			tmp[x][y] = itmp;
			tmp[posDiff.fi][posDiff.se] = itmp;
			res++;
			_pos = posDiff;
			misstype++;
		}
	}
	return res;
}//*/