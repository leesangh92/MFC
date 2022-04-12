#include <iostream>
#include <vector>
using namespace std;

//int sum(int* arr, int size) {
int sum(const int* const arr, const int size) { // const는 바로 다음에 나오는 기호를 상수로 만든다 (const int* const arr // *(arr배열의 첫 번째 값)을 상수화, arr를 상수화)
	int sum = 0;
	//arr[0] == *arr; // 배열의 첫번째 값
	//*arr = 10; // 배열의 첫 번째 값을 변경
	//arr += 10; // 할당된 배열이 아닌 다른 배열을 사용하게 된다

	//arr++; // 주소가 바뀜
	for (int i = 0; i < size; i++) {
		sum += arr[i];
		//arr++ // error
		//size++; // error
		cout << "sum = " << sum << endl;
	}
	return sum;
}

//solid 개념
//1. Single Responsibility(단일 책임의 원칙) - 하나의 클래스는 하나의 역할만 하도록
//2. Open / Closed(열림 / 닫힘의 원칙) - 새로운 기능이 추가되어도 기존의 코드가 수정되어서는 안된다 -> Indirect(간접)
//3. Liskov Substitution(리스코프 치환의 원칙)
//4. Interface Segregation(인터페이스 분리 원칙)
//5. Dependency Inversion(의존성 역전 원칙)

class Cat {
public:
	void cat_speak() {
		cout << "야옹~" << endl;
	}
};
class Dog {
public:
	void dog_speak() {
		cout << "멍멍~" << endl;
	}
};
class Cow {
public:
	void cow_speak() {
		cout << "음메~" << endl;
	}
};
class Zoo {
private:
	Cat cat;
	Dog dog;
	Cow cow;
public:
	void speak() {
		dog.dog_speak();
		cat.cat_speak();
		cow.cow_speak();
	}
};

class Animal {
public:
	virtual void speak() const = 0; // 함수의 멤버를 수정할 경우 구문 오류
};
class Cat : public Animal{
public:
	virtual void speak() const override {
		cout << "야옹~" << endl;
	}
};
class Dog : public Animal {
public:
	virtual void speak() const override {
		cout << "멍멍~" << endl;
	}
};
class Cow : public Animal {
public:
	void speak() const override {
		cout << "음메~" << endl;
	}
};
class Zoo {
private:
	vector<Animal*> array;

public:
	void addAnimal(Animal* const pAnimal) {
		array.push_back(pAnimal);
	}
	void speak() {
		for (const auto& pAnimal : array) {
			pAnimal->speak();
		}
	}
};

// c style
int add(const int a, const int b) {
	return a + b;
}
int sub(const int a, const int b) {
	return a - b;
}
class Calc {
public:
	virtual int calc(const int a, const int b) = 0;
};
class AddCalc : public Calc {
public:
	virtual int calc(const int a, const int b) override {
		return a + b;
	}
};
class SubCalc : public Calc {
public:
	virtual int calc(const int a, const int b) override {
		return a - b;
	}
};
class MulCalc : public Calc {
public:
	virtual int calc(const int a, const int b) override {
		return a * b;
	}
};
// c style
int MyCalc(Calc& obj, const int a, const int b) {
	// 변경되는 것 없음. 새로운 기능 자연스럽게 실행할 수 있음 >> OCP
	return obj.calc(a, b);
}


bool InitInstance(Zoo* pZoo) { // 메인함수는 그대로 두고, 설정이 필요한 부분을 이곳에서 수정
	Cat cat;
	Dog dog;
	Cow cow;
	pZoo->addAnimal(&cat);
	pZoo->addAnimal(&dog);
	pZoo->addAnimal(&cow);
	return true;
}
bool Run(Zoo* pZoo) {
	pZoo->speak();
	return true;
}
bool ExitInstance(Zoo* pZoo) {
	return true;
}

int main(int argc, char** argv) {
	//int size = 10;
	const int size = 10; // 읽기만 하는 상수이므로 const로 고정시켜준다 // 논리적인 오류를 구문 오류로 쉽게 확인할 수 있게 해준다
	const int arr[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	int sum = 0;
	for (int i = 0; i < size; i++) {
		sum += arr[i];
		//size++; // error
		cout << "sum = " << sum << endl;
	}
	//오류 1. 구문 오류(syntax) - 컴파일러가 잡아줌 / 2. 논리 오류 - 개발자가 디버깅을 통해서 잡음
	//선언 시 read, read/write 두 개를 구분하여 read만 하는 선언문에는 const 키워드를 넣어준다 

	Zoo zoo;
	Cat cat;
	Dog dog;
	Cow cow;
	zoo.speak();
	zoo.addAnimal(&dog);
	zoo.addAnimal(&cat);
	zoo.addAnimal(&cow);

	Zoo zoo;
	InitInstance(&zoo);
	Run(&zoo);
	ExitInstance(&zoo);

	int a = 10;
	int b = 20;
	int sum;
	int a = atoi(argv[1]);
	int b = atoi(argv[2]);
	//컴파일 타임
	//런타임
	sum = 10 + 20; // 정적인 코드 // 컴파일 타임
	sum = a + b; // 정적인 코드 // 컴파일 타임
				 // (atoi)동적인 코드 // 런타임 // 실행할 때마다 결과 값이 바뀔 수 있다
	sum = add(a, b);
	//debug -> 함수로 정상 동작 : 런타임 시 계산
	//release -> 최적화 정적 코드로 계산
	cout << a << " + " << b << " = " << sum << endl;

	// 일반화 / 특수화
	int* p1 = &a;
	int* p2 = &b;
	int* p;

	// int (*)(const int, const int); // 함수 포인터
	typedef int (*FP_CALC)(const int, const int); // 함수 포인터 재정의
	FP_CALC calc; // calc : 포인트 변수명

	//typedef type 변수명 : 변수명을 새로운 자료형으로 정의
	typedef int (*p)(const int a, const int b);
	//typedef oldtype newtype;
	//(typedef) unsigned int UINT;

	typedef int(*FP_CALC(const int, const int));
	FP_CALC calc;

	unsigned int aaa;
	//UINT bbb;

	int result = 0;
	// c style
	result = add(a, b); // add 함수 : 컴파일 때 결정되는 함수
	result = sub(a, b);
	// 함수명에 대해서 특별화

	calc = add;
	result = calc(a, b); // 실행 중에 결졍(그 윗줄에서 정의되는 함수에 따라 달라짐)
	calc = sub;
	result = calc(a, b);

	// cpp style
	Calc* pCalc = new AddCalc();
	result = pCalc->calc(a, b); // a+b
	delete pCalc;

	pCalc = new SubCalc();
	result = pCalc->calc(a, b); // a-b
	delete pCalc;

	AddCalc addCalc;
	Calc& objA = addCalc;
	result = objA.calc(a, b);

	SubCalc subCalc;
	Calc& objB = subCalc;
	result = objB.calc(a, b);

	// c style
	result = MyCalc(addCalc, a, b); // MyCalc가 고정했을 때 일반화
	result = MyCalc(subCalc, a, b);

	// 새롭게 추가된 부분
	MulCalc mulCalc;
	result = MyCalc(mulCalc, a, b);
	// 기존의 코드를 변경하지 않음

	vector<Calc*> arr = { &addCalc, &subCalc, &mulCalc };
	// 전달해주는 순서에 따라 달라짐
	/*for (int i = 0; i < arr.size(); i++) {
		MyCalc(arr[i], a, b);
	}*/
	for (auto& pCalc : arr) {
		MyCalc(*pCalc, a, b); // 런타임에 의해 결정
	}
	return 0;
}

//기존의 library 사용 + 나만의 기능 추가(main()의 작성) -> 응용 프로그램 작성
// pointer -> indirect -> virtual function, 의존성 역전, ocp
// framework 이해

//Handler
//
//int a;
//char ch;
//string name;
//Zoo zoo;
//
////void 포인터(일반화), int 포인터(특별화), char 포인터(특별화)
//&a -> void*, int *
//&ch -> void*, char*
//
//typedef void* HANDLE // void 포인터를 handle로 줌
