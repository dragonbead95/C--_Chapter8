#include <iostream>
#include <cstring>
using std::endl;
using std::cout;

class First
{
private:
	char * strOne;
public:
	First(const char * str)
	{
		int len = strlen(str) + 1;
		strOne = new char[len];

	}
	virtual ~First()
	{
		cout << "~First()" << endl;
		delete[]strOne;
	}
};

class Second : public First
{
private:
	char * strTwo;
public:
	Second(const char * str1, const char * str2) : First(str1)
	{
		int len = strlen(str2) + 1;
		strTwo = new char[len];
	}
	~Second()
	{
		cout << "~Second()" << endl;
		delete[]strTwo;
	}
};

int main(void)
{
	First * ptr = new Second("simple", "complex");
	delete ptr;

	system("pause");
	return 0;
}