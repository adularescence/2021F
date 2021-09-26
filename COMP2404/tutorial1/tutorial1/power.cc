
using namespace std;

void power(int a, int b, int& c) {
	if (b == 0) {
		c = 1;
	} else {
		c = 1;
		for (int i = 1; i <= b; ++i) {
			c *= a;
		}
	}
}
