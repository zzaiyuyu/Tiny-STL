#define _CRT_SECURE_NO_WARNINGS 1
#include "List.hpp"
#include "Vector.hpp"
#include "Algorithm.hpp"
#include "String.hpp"
using namespace std;


void TestVector()
{
	Vector<double> vi(5, 3.14);
	vi.PushBack(1.5);
	vi.PushBack(2.5);
	vi.PushBack(3.33);
	std::cout << vi.Size() << std::endl;
	std::cout << vi.Capacity() << std::endl;
	std::cout << vi.Front() << std::endl;
	std::cout << vi.Back() << std::endl;
	vi.PopBack();
	vi.PopBack();
	std::cout << vi.Size() << std::endl;
	std::cout << vi.Capacity() << std::endl;
	std::cout << vi.Front() << std::endl;
	std::cout << vi.Back() << std::endl;
	vi.Resize(20, 9);
	std::cout << std::endl;
	for (size_t i = 0; i < vi.Size(); i++) {
		std::cout << vi[i] << " ";
	}
	std::cout << std::endl;
	Vector<String> vs(10, "Nice");
	vs.PushBack("l1");
	vs.PushBack("12");
	vs.Erase(10);
	vs.Insert(1, "insert");
	vs.PopBack();
	Vector<String>::Iterator its;
	for (its = vs.Begin(); its != vs.End(); its++) {
		std::cout << *its << std::endl;
	}
}

int main()
{
	TestVector();
	//TestLList();

	//Vector<int> v(10, 0);
	//v[0] = 2;
	//v[1] = 10;
	//v[2] = 6;
	//v[3] = 1;
	//v[4] = 7;
	//v[5] = 5;
	//Sort(v.Begin(), v.End());
	//ForEach(v.Begin(), v.End(), Display<int>());
}