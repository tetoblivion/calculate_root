#include<stdio.h>
#include<math.h>

namespace square_root {

	int isqrt(int a) {

		int m = 1 << sizeof(int) * 4 -1;
		int rxr, r = 0;

		for (int i = 0; m != 0; i++, m >>= 1) {
			r |= m;
			rxr = r*r;
			if (rxr == a) { return r; }
			if (rxr > a) { r &= ~m; }
		}

		return r;
	}


	template<typename T>
	__forceinline T fastisqrt(T a) {

		if (a < 0) throw L"a is negative"; // if T is unsigned a is never less than zero 

		int i = (sizeof(T) << 2) -1;

		T m = (T)1 << i;
		T x, b;
		T  r = 0, rxr = 0;

		while (m > a) { m >>= 1; i--; }

		for (; m != 0; m >>= 1, i--) {

			x = r | m;

			b = rxr + ((r + x) << i);  //no multiplication in this function

			if (b == a) return x;
			if (b < a) { r = x; rxr = b; }
		}

		return r;
	}


	extern "C" int isqrasm(int);
	


	double doublesqrt(double a) {

		int mm;
		frexp(a, &mm);
		mm = (mm >> 1) + 1;
		double m=ldexp(1.0, mm);

		double rxr, r = 0;

		for (int i = 0; i<60 ; i++, m *=.5) {
			r += m;
			rxr = r*r;
			if (rxr == a) { return r; }
			if (rxr > a) { r -=m; }
		}

		return r;
	}

}
	int main(int argc, wchar_t* argv[]) {

		using namespace square_root;

		int a = 34135;


		for (int i = 0; i <20; i++)printf("\n%d",fastisqrt(i*i));

		printf("\n%I64d\n%f\n\n", fastisqrt(0xFFFFFFFFffffffff), sqrt(double(0xFFFFFFFFffffffff)) );

		try {
			printf("\n%d\n\n", fastisqrt(-1));
		}
		catch (wchar_t a[]) {
			printf("Error %ws",a);
		}
		
		printf("\n%d\n\n", isqrasm(121));

		a = 34135;
		printf("\n%lf\n%lf\n\n", doublesqrt(a), sqrt(double(a)));


		return 0;
	}
