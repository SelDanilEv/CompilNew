#include <cstdlib>

extern "C" {

	int getmin(int* first, int n) {
		int res = first[0];
		for (int i = 0; i <n; i++) {
			if (res > first[i]) {
				res = first[i];
			}
		}
		return res;
	}

	int getmax(int* first, int n) {
		int res = first[0];
		for (int i = 0; i <n; i++) {
			if (res < first[i]) {
				res = first[i];
			}
		}
		return res;
	}

}