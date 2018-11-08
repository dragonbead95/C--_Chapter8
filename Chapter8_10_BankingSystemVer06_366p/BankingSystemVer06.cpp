/*
제목 : Banking System ver06
날짜 : 2018-11-08
내용 : NormalAccount(보통예금계좌)와 HightCreditAccount(신용신뢰계좌) 클래스 추가
*/

#include <iostream>
#include <cstring>

using std::cout;
using std::endl;
using std::cin;

const int NAME_LEN = 20;	// 이름 길이

/* 1:계좌생성 2:입금 3:출금 4:개인정보 전체 출력 5:프로그램 종료 */
enum { MAKE = 1, DEPOSIT, WITHDRAW, INQUIRE, EXIT };

/* 신용등급 A,B,C */
enum CREDIT { A = 1, B, C };

/*
클래스 이름 : Account
클래스 유형 : Entity 클래스
*/
class Account
{
private:
	int accID;			// 계좌ID
	int balance;		// 잔고
	char * cusName;		// 이름
public:
	/*생성자*/
	Account(int ID, int money, const char * name);
	Account(const Account& ref);

	int GetAccID() const;	// 계좌ID 반환
	virtual void Deposit(int money);	// 입금
	int Withdraw(int money);			// 출금
	virtual void ShowAccInfo() const;	// 개인정보 출력
	~Account();							// 소멸자
};

/*생성자*/
Account::Account(int ID, int money, const char * name) :accID(ID), balance(money)
{
	int len = strlen(name) + 1;
	cusName = new char[len];
	strcpy_s(cusName, len, name);
}

/*계좌ID 반환*/
int Account::GetAccID() const
{
	return accID;
}

/*입금*/
void Account::Deposit(int money)
{
	balance += money;
}

/*출금*/
int Account::Withdraw(int money)
{
	if (balance < money)
		return 0;
	balance -= money;
	return money;
}

/*개인정보 출력*/
void Account::ShowAccInfo() const
{
	cout << "계좌ID: " << accID << endl;
	cout << "이 름: " << cusName << endl;
	cout << "잔 액: " << balance << endl;
}

/* 소멸자 */
Account::~Account()
{
	delete[]cusName;
}

/*
클래스이름: NormalAccount
클래스유형: 보통예금계좌
*/
class NormalAccount : public Account
{
private:
	int rate;	// 이자율
public:
	/* 생성자 */
	NormalAccount(int ID, int money, const char * name, int myrate);

	virtual void ShowAccInfo() const;	// 개인정보 출력
	virtual void Deposit(int money);	// 입금
};

/*생성자*/
NormalAccount::NormalAccount(int ID, int money, const char * name, int myrate)
	: Account(ID, money, name), rate(myrate)
{

}

/*개인정보 출력+(이자율 추가)*/
void NormalAccount::ShowAccInfo() const
{
	Account::ShowAccInfo();
	cout << "이자율 : " << rate << endl;
}

/*입금*/
void NormalAccount::Deposit(int money)
{
	Account::Deposit(money+(money*(((double)rate)/100)));	/* 입급액과 입급액의 이자율을 계산해서 
															Account 클래스의 Deposit 함수의 balance 변수에 대입*/
}

class HightCreditAccount : public Account
{
private:
	int rate;	// 이자율
	int credit;	// 신용등급
public:
	HightCreditAccount(int ID, int money, const char * name, int myrate, int mycredit);
	virtual void ShowAccInfo() const;
	virtual void Deposit(int money);
};

HightCreditAccount::HightCreditAccount(int ID, int money, const char * name, int myrate, int mycredit)
	: Account(ID, money, name), credit(mycredit)
{
	/* A등급이면 입력받은 이자율에 7%, B등급이면 4%, C등급이면 2%를 더한다.*/
	if (credit == 1)	// A등급
	{
		rate = myrate+ 7;
	}
	else if (credit == 2)	// B등급
	{
		rate = myrate+4;
	}
	else {	// C등급
		rate = myrate+2;
	}
}

/*개인정보 출력+(이자율,신용등급)*/
void HightCreditAccount::ShowAccInfo() const
{
	Account::ShowAccInfo();
	cout << "이자율 : " << rate << endl;
	cout << "신용등급 : " << credit << endl;
}

/*입급*/
void HightCreditAccount::Deposit(int money)
{
	Account::Deposit(money + (money*(((double)rate) / 100))); /* 입급액과 입급액의 이자율을 계산해서 
															Account 클래스의 Deposit 함수의 balance 변수에 대입*/
}

/*
클래스이름 : AccountHandler
클래스유형 : 컨트롤(Control) 클래스
*/
class AccountHandler
{
private:
	Account * accArr[100];	// 계좌의 배열
	int accNum;				// 계좌 갯수
public:
	AccountHandler(); // 생성자
	void ShowMenu(void) const;	// 메뉴
	void MakeAccount(void);		// 계좌생성
	void DepositMoney(void);	// 입급
	void WithdrawMoney(void);	// 출금
	void ShowAllAccInfo(void) const;	// 개인정보 전체 출력
	~AccountHandler();			// 소멸자
};

void AccountHandler::ShowMenu(void) const
{
	cout << "-----Menu-----" << endl;
	cout << "1. 계좌개설" << endl;
	cout << "2. 입 금" << endl;
	cout << "3. 출 금" << endl;
	cout << "4. 계좌정보 전체 출력" << endl;
	cout << "5. 프로그램 종료" << endl;
}

void AccountHandler::MakeAccount(void)
{
	int id;					// 계좌 ID
	char name[NAME_LEN];	// 이름
	int balance;	// 잔고
	int choice;	// 보통예금, 신용신뢰 계좌 선택
	int rate;	// 이자율
	int credit;	// 신용등급
	
	cout << "[계좌종류선택]" << endl;
	cout << "1.보통예금계좌 2.신용신뢰계좌" << endl;
	cout << "선택: "; cin >> choice;

	if (choice == 1)
	{
		cout << "[보통예금계좌 개설]" << endl;
		cout << "계좌ID: "; cin >> id;
		cout << "이 름: "; cin >> name;
		cout << "입금액: ";cin >> balance;
		cout << "이자율: "; cin >> rate;
		cout << endl;

		accArr[accNum++] = new NormalAccount(id, balance, name, rate);	// 보통예금계좌 생성
	}
	else if (choice == 2)
	{
		cout << "[신용신뢰계좌 개설]" << endl;
		cout << "계좌ID: "; cin >> id;
		cout << "이 름: "; cin >> name;
		cout << "입금액: ";cin >> balance;
		cout << "이자율: "; cin >> rate;
		cout << "신용등급(1toA, 2toB, 3toC): "; cin >> credit;
		cout << endl;
		accArr[accNum++] = new HightCreditAccount(id, balance, name, rate,credit);	// 신용예금계좌 생성
	}
	else {
		cout << "1번과 2번중에 선택해주세요" << endl;
		return;
	}
}

/*입급*/
void AccountHandler::DepositMoney(void)
{
	int money;	// 입급액
	int id;	// 입력받을 계좌ID 변수
	cout << "[입   금]" << endl;
	cout << "계좌ID: "; cin >> id;
	cout << "입금액: "; cin >> money;

	for (int i = 0;i < accNum;i++)
	{
		if (accArr[i]->GetAccID() == id)
		{
			accArr[i]->Deposit(money);	// 입급액 입금
			cout << "입금완료" << endl << endl;
			return;
		}
	}
	cout << "유효하지 않은 ID입니다." << endl << endl;
}

/*출금*/
void AccountHandler::WithdrawMoney(void)
{
	int money;	// 출금액
	int id;	// 입력받을 계좌ID 변수
	cout << "[출   금]" << endl;
	cout << "계좌ID: "; cin >> id;
	cout << "출금액: "; cin >> money;

	for (int i = 0;i < accNum;i++)
	{
		if (accArr[i]->GetAccID() == id)
		{
			if (accArr[i]->Withdraw(money) == 0)
			{
				cout << "잔액부족" << endl << endl;
				return;
			}
			cout << "출금완료" << endl << endl;
			return;
		}
	}
	cout << "유효하지 않은 ID입니다." << endl << endl;
}

/*생성자*/
AccountHandler::AccountHandler() :accNum(0)
{

}

/*개인정보 전체 출력*/
void AccountHandler::ShowAllAccInfo(void) const
{
	for (int i = 0;i < accNum;i++)
	{
		accArr[i]->ShowAccInfo();
		cout << endl;
	}
}

/*소멸자*/
AccountHandler::~AccountHandler()
{
	for (int i = 0;i < accNum;i++)
		delete accArr[i];
}

/*
컨트롤 클래스 AccountHandler 중심으로 변경된 main 함수
*/

int main(void)
{
	AccountHandler manager;	// AccountHandler 클래스의 객체
	int choice;	// 메뉴 번호선택 변수

	while (1)
	{
		manager.ShowMenu();
		cout << "선택: ";
		cin >> choice;
		cout << endl;

		switch (choice)
		{
		case MAKE:
			manager.MakeAccount();
			break;
		case DEPOSIT:
			manager.DepositMoney();
			break;
		case WITHDRAW:
			manager.WithdrawMoney();
			break;
		case INQUIRE:
			manager.ShowAllAccInfo();
			break;
		case EXIT:
			return 0;
		default:
			cout << "Illegal selection.." << endl;
		}
	}
	return 0;
}