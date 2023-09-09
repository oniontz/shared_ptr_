#include <iostream>
using namespace std;

class A {
public:
	int a;
	A() :a(0) {
		cout << "---------construct----------" << endl;
		cout << "a = " << a << endl;
		cout << "construct A!!!" << endl;
	}
	A(int a) : a(a) {
		cout << "---------construct----------" << endl;
		cout << "a = " << a << endl;
		cout << "construct A!!!" << endl;
	}
	~A()
	{
		cout << "---------destroy----------" << endl;
		cout << "a = " << a << endl;
		cout << "destroy A!!!" << endl;
	}
};

int main() {
	cout << "-----------------test1������----------------------" << endl;
	// ����һ��ָ��A���shared_ptrָ�� _ptr1
	shared_ptr<A> _ptr1;

	cout << "-----------------test2�����캯������A*----------------------" << endl;

	// ����һ��ָ��A���shared_ptrָ�� _ptr2
	shared_ptr<A> _ptr2(new A(2));
	// The count of _ptr2 = 1
	cout << "The count of _ptr2 = " << _ptr2.use_count() << endl; 

	cout << "-----------------test3�������ڴ�A*��shared_ptr<A> ������ת��----------------------" << endl;

	/*
	* �����ڴ�A*��shared_ptr<A> ������ת��
	* ���Խ�shared_ptr<A>����һ��class
	A* a = new A();
	shared_ptr<A> _ptr3 = a;
	*/

	cout << "-----------------test4��ʹ��make_shared<A>()��������shared_ptrָ��----------------------" << endl;

	shared_ptr<A> _ptr4 = make_shared<A>(4);
	// The count of _ptr4 = 1
	cout << "The count of _ptr4 = " << _ptr4.use_count() << endl;

	cout << "-----------------test5�����캯������A*----------------------" << endl;

	A* a = new A(5);
	// ���ù��캯����������Ϊ1
	shared_ptr<A> _ptr5(a);
	// The count of _ptr5 = 1
	cout << "The count of _ptr5 = " << _ptr5.use_count() << endl;

	cout << "-----------------test6���������캯��----------------------" << endl;

	// ���ÿ������캯����������1
	shared_ptr<A> _ptr6 = _ptr5;
	// The count of _ptr6 = 2
	cout << "The count of _ptr6 = " << _ptr6.use_count() << endl;

	cout << "-----------------test7����ֵ�����----------------------" << endl;

	// ����һ��shared_ptrָ��
	shared_ptr<A> _ptr7;
	// ͨ����ֵ�����ָ��ͬһ�����󣬼�������1
	_ptr7 = _ptr6;
	// The count of _ptr7 = 3
	cout << "The count of _ptr7 = " << _ptr7.use_count() << endl;

	cout << "-----------------test8���������캯��----------------------" << endl;

	// ʹ�ÿ������캯������������1
	shared_ptr<A> _ptr8(_ptr7);
	// The count of _ptr8 = 4
	cout << "The count of _ptr8 = " << _ptr8.use_count() << endl;

	cout << "-----------------test9���ֱ���ù��캯������shared_ptr��ָ��ͬһ������----------------------" << endl;
	cout << "��������Ϊ1����shared_ptr�������ڽ�����ʱ�򣬻�����������������ظ��ͷ��ڴ棬���´���" << endl;

	// ��������ָ�붼ָ��a9��ʹ���ظ��ͷ��ڴ棬���´���
	// ��Ϊ�������õĶ��ǹ��캯������������ֵ����ʼ��Ϊ1������ָ�����ͬһƬ��ַ
	A* a9 = new A(9);
	shared_ptr<A> _ptr9(a9);
	//shared_ptr<A> _ptr10(a9);
	cout << "The count of _ptr9 = " << _ptr9.use_count() << endl;
	//cout << "The count of _ptr10 = " << _ptr10.use_count() << endl;

	cout << "-----------------test11������ʹ��ջ�ڴ��shared_ptrָ����г�ʼ��----------------------" << endl;
	cout << "��Ϊ��shared_ptr�������ڽ�����ʱ�򣬻����������������delete��ָ����ڴ�ռ䣬��deleteջ�ռ�ᵼ�´���" << endl;

	// ������ջ�ڴ��shared_ptr���г�ʼ��
	A a11(11);
	//shared_ptr<A> _ptr11(&a11);

	cout << "-----------------test12��������shared_ptr���ڲ���Ա����get()��ȡ�ڲ�ָ����������shared_ptr���г�ʼ��----------------------" << endl;
	cout << "��ʼ���ǵ��ù��캯������������ֵ���ʼ��Ϊ1��������ָ���������ڽ�����ʱ�򣬻���ظ��ͷ��ڴ棬���´���" << endl;
	
	A* a12 = new A(12);
	shared_ptr<A> _ptr12(a12);
	//shared_ptr<A> _ptr13(_ptr12.get());
	

	cout << "-----------------test14----------------------" << endl;

	// C++17�� shared_ptr���Թ�������
	shared_ptr<int[]> _ptr14(new int[10]());
	*(_ptr14.get() + 1) = 14;
	cout << *(_ptr14.get() + 1) << endl;


	cout << "-----------------test15��ʹ������ָ���������----------------------" << endl;

	// �ܱ���
	shared_ptr<int> _ptr15(new int[10]());
	int* temp = _ptr15.get() + 1; // �����鱣��get�������صĵ�ַ
	*(_ptr15.get() + 1) = 15;
	cout << "*temp = " << *temp << endl; // *temp = 15
	_ptr15.reset(); // ������ָ���ͷţ��ܹ��ͷ��������飬������ֻ�ͷ�һ��int
	cout << "*temp = " << *temp << endl; // *temp = -572662307

	return 0;
}










