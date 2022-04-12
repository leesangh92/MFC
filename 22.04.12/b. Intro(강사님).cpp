#include <iostream>
#include <vector>

using namespace std;

//마성일 : masungil2@daum.net
/*
오류 : 1. 구문 오류 : 컴파일러가 잡아줌 (시간이 많이 걸리지 않음)
       2. 논리 오류 : 개발자 디버깅을 통해서 잡는다(시간이 많이 걸림)
              
       read,  read/write

*/

//Windows Programming API(Application Programmig Interface)
//  
// class A {
//   virtual void func();
// };
// 
// class B : public A {
// 
// }
// 
// 
//MFC 

//콘솔프로그램 
//진입점 : main() 
//콘솔 출력 : cpp -> cout , c -> printf, 표준 출력장치 
//키보드 입력 : cpp -> cin , c -> scanf, gets(), getchar(), ... :  표준 입력장치 
//실행 루틴은 순차적으로 처리됨 



//윈도우프로그램(Win32 API) -> C style 작성
//진입점 : WinMain() 
//출력 : 윈도우에 출력 
//입력 : Mouse, keyboard
//프로그램 흐름에 대한 규칙이 약속되어 있음 
//순차적으로 동작 하지 않음 
//메시지를 통한 동작으로 수행됨 

//solid 개념 
/*
1. 단일 책임의 원칙 
2. 열림 닫힘의 원칙 
3. 리스코프 치환 원칙 
4. 인턴페이스 분리 원칙
5. 의존성 역전 원칙 
*/

/*
동물원 
고양이
강아지 
*/
class Animal {
public:
    virtual void speak() const = 0;
};

class Cat : public Animal {
public:
    virtual void speak() const override {
        cout << " 야옹 ~~~~" << endl;
    }
};

class Dog : public Animal {
public:
    virtual void speak() const override {
        cout << " 멍멍 ~~~~" << endl;
    }
};

//추가함 
class Cow : public Animal {
public:
    virtual void speak() const override {
        cout << " 음메 ~~~~" << endl;
    }
};

//기존 코드 
class Zoo {
private:
    //Cat cat;
    //Dog dog;
    ////추가함 
    //Cow cow;
    vector<Animal*> array;

public:
    void addAnimal(Animal* const pAnimal) {
        //pAnimal++; 포인터 변수를 이용해서 포인터를 변경하면 컴파일 오류 발생하게 설정 (const)
        array.push_back(pAnimal);
    }

    void speak() {
        //cat.cat_speak();
        //dog.dog_speak();
        ////추가함
        //cow.cow_speak();
        for (const auto& pAnimal : array) {
            pAnimal->speak();
        }
    }
};

//기존 library 사용 + 나의 기능 추가(main()의 작성은 내가) -> 응용 프로그램 작성 
//pointer -> indirect -> virtual function , 의존성 역전, ocp
//framework 이해, 코딩 방법

int sum(const int* const arr, const int size) {
    int sum = 0;
    //const int count = 10;
    //
    //count += 10;


    //arr[0] == *arr
    //*arr = 10;  //배열이 read/write 가능하면 OK
    //arr += 10;   //arr의 값이 write 됨 

//    arr++;
    for (int i = 0; i < size; i++) {
        sum += arr[i];
        //size++;
        //arr[i]++;
    }

    return sum;
}

int add(const int a, const int b) {
    return a + b;
}

int sub(const int a, const int b) {
    return a - b;
}

//typedef type 변수명; //변수명을 새로운 형으로 정의한다
//unsigned int UINT;

//unsigned int aaa;
//UINT bbb;

//int (*)(const int, const int);

typedef int (*FP_CALC)(const int, const int);
FP_CALC calc;


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

//ocp
int MyCalc(Calc& obj, const int a, const int b) {
    //변경되는 것 없음 , 새로운 기능 자연스럽게 실행 할 수 있는지?
    return obj.calc(a, b);
}

int main(int argc, char** argv)
{
    int a = 10; //atoi(argv[1]);
    int b = 20; //atoi(argv[2]);
    int c = 10;
    int d = 20;
    int e = 10;
    int f = 20;
    int sum;

    

    //컴파일 타임 
    //런타임 
//    sum = a + b; //정적인 코드 -> sum = 10 + 20;
    //debug -> 함수로 정상 동작함 : runtime시 계산함 , 디버깅 정보가 결과물 안에 포함됨 
    //release -> 최적화로 정적코드로 동작함 sum = 30
    //생성(exe 만들기)  : 일반적인 경우 debug 모드가 exe 생성시 좀더 빠르다
    //실행 : 일반적을 release 모드의 결과물이 빠르다 
    //크기 : debug 모드가 크다, release 모드가 보통 debug 모드 대비 1/4 정도 작다 
    //일반화 / 특별화 
    //pointer -> data pointer, function pointer
    int* p1 = &a;
    int* p2 = &b;

    sum = 10 + 20;

    sum = a + b;
    sum = c + d;
    sum = e + f;
    
    p1 = &a;
    p2 = &b;
    sum = *p1 + *p2;

    p1 = &c;
    p2 = &d;
    sum = *p1 + *p2;

    p1 = &e;
    p2 = &f;
    sum = *p1 + *p2;

    int result = 0;

    calc = add;
    result = calc(a, b);

    calc = sub;
    result = calc(a, b);

    //함수포인터 
    Calc* pCalc = new AddCalc();
    result = pCalc->calc(a, b); //a + b;
    delete pCalc;

    pCalc = new SubCalc();
    result = pCalc->calc(a, b); //a - b;
    delete pCalc;
    
    AddCalc addCalc;
    Calc& objA = addCalc;
    result = objA.calc(a, b); //a + b;

    SubCalc subCalc;
    Calc& objB = subCalc;
    result = objB.calc(a, b); //a - b;

    result = MyCalc(addCalc, a, b);
    result = MyCalc(subCalc, a, b);

    //새롭게 추가된 부분 
    MulCalc objC;
    result = MyCalc(objC, a, b);

    vector<Calc*> arr = {&addCalc, &objC, &subCalc};
    //for (auto& pCalc : arr) {
    for (int i = 0; i < arr.size();i++) {
        MyCalc(*arr[i], a, b);
    }
    for (auto& pCalc : arr) {
        MyCalc(*pCalc, a, b);
    }

    cout << a << " + " << b << " = " << sum << endl;

    Zoo zoo;
    Cat cat;
    Dog dog;
    Cow cow;

    zoo.addAnimal(&dog);
    zoo.addAnimal(&cat);
    zoo.addAnimal(&cow);

    zoo.speak();

    // 오류 : 1. 구문 오류 : 컴파일러가 잡아줌 (시간이 많이 걸리지 않음)
    //       2. 논리 오류 : 개발자 디버깅을 통해서 잡는다(시간이 많이 걸림)
    // read,  read/write 

    return 0;
}