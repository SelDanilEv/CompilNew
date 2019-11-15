#include <iostream>
#include <cstdlib>


extern "C"
{
	int __stdcall getmin(int* ar, int n);
	int __stdcall getmax(int* ar, int n);

}

int main()
{
	using namespace std;
	long max;
	long min;
	int array[] = { 11,22,14,67,3,123,45,234,22,10 };
	int size = sizeof(array) / 4-1;

	max = getmax(array, size);
	cout << max << endl;
	min = getmin(array, size);
	cout << min << endl;

	std::cout << max - min;
	system("pause");
}