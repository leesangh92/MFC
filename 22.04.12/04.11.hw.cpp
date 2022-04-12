//A, B를 입력받은 후, A/B(나누기)를 출력
//0으로 나누었을 때, 문자가 들어왔을 때 예외처리
//함수화하여 만들기

#include <iostream>
#include <vector>
using namespace std;

class Calc {
public:
	virtual int calc(const int a, const int b) = 0;
};
//class AddCalc : public Calc {
//public:
//	virtual int calc(const int a, const int b) override {
//		return a + b;
//	}
//};
//class SubCalc : public Calc {
//public:
//	virtual int calc(const int a, const int b) override {
//		return a - b;
//	}
//};
//class MulCalc : public Calc {
//public:
//	virtual int calc(const int a, const int b) override {
//		return a * b;
//	}
//};
class DivCalc : public Calc {
public:
	virtual int calc(const int a, const int b) override {
		if (b == 0) {
			cout << "나누는 수는 0이 될 수 없습니다. " << endl;
		}
		exit(-1);
		return a / b;
	}
};



//class Calc {
//public:
//	void Divide();
//};
//class Div : public Calc {
//public:
//	int Divide(int& A, int& B) {
//		if (B == 0) {
//			cout << "나누는 수는 0이 될 수 없습니다. " << endl;
//		}
//		exit(-1);
//		return A / B;
//	}
//};
//class Calculate {
//private:
//	vector<Calc*> array;
//
//public:
//	void DivCalc(Calc* pCalc) {
//		array.push_back(pCalc);
//	}
//	void Divide() {
//		for (auto& pCalc : array) {
//			pCalc->Divide();
//		}
//	}
//};
//void InitCalc(Calc* pCalc) {
//	Div div;
//	pCalc->Divide();
//}
//void RunCalc(Calc* pCalc) {
//	pCalc->Divide();
//}
//void ExitCalc(Calc* pCalc) {
//}



//void setVar(int &_A, int &_B) {
//	cout << "입력하신 값은 " << "A : " << _A << ", B : " << _B << "입니다." << endl;
//
//	cout << "A 값 ? : ";
//	cin >> _A;
//	cout << "B 값 ? : ";
//	cin >> _B;
//	
//	cout << "입력하신 값은 " << "A : " << _A << ", B : " << _B << "입니다." << endl;
//}
//void Divide() {
//
//}
//

int main()
{
	cout << "A 나누기 B 수행" << endl;
	//int A;
	//int B;

	int result = 0;
	//int a = 100;
	//int b = 0;

	Calc* pCalc = new DivCalc; // 클래스 객체 생성, 객체 메모리 할당
	//result = pCalc->calc(a, b); // 변수에 값 입력
	result = pCalc->calc(100, 0); // 직접 값 입력
	cout << result;
	delete pCalc;
	cout << "==============================" << endl;
	/*InitCalc(Calc * pCalc);
	RunCalc(Calc * pCalc);
	ExitCalc(Calc * pCalc);*/
	cout << "==============================" << endl;

	//setVar(A, B);
	//Divide();

	return 0;
}