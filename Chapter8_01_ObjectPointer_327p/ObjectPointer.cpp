#include <iostream>

using std::endl;
using std::cout;

class Person
{
public:
	void Sleep()
	{
		cout << "Sleep" << endl;
	}
};

class Student :public Person
{
public:
	void Study()
	{
		cout << "Study" << endl;
	}
};

class PartTimeSstudent :public Student
{
public:
	void Work()
	{
		cout << "Work" << endl;
	}
};

int main(void)
{
	Person * ptr1 = new Student();
	Person * ptr2 = new PartTimeSstudent();
	Student * ptr3 = new PartTimeSstudent();
	ptr1->Sleep();
	ptr2->Sleep();
	ptr3->Study();

	delete ptr1;
	delete ptr2;
	delete ptr3;

	system("pause");
	return 0;
}