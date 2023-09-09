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
	cout << "-----------------test1：声明----------------------" << endl;
	// 声明一个指向A类的shared_ptr指针 _ptr1
	shared_ptr<A> _ptr1;

	cout << "-----------------test2：构造函数传入A*----------------------" << endl;

	// 定义一个指针A类的shared_ptr指针 _ptr2
	shared_ptr<A> _ptr2(new A(2));
	// The count of _ptr2 = 1
	cout << "The count of _ptr2 = " << _ptr2.use_count() << endl; 

	cout << "-----------------test3：不存在从A*到shared_ptr<A> 的类型转换----------------------" << endl;

	/*
	* 不存在从A*到shared_ptr<A> 的类型转换
	* 可以将shared_ptr<A>理解成一个class
	A* a = new A();
	shared_ptr<A> _ptr3 = a;
	*/

	cout << "-----------------test4：使用make_shared<A>()函数返回shared_ptr指针----------------------" << endl;

	shared_ptr<A> _ptr4 = make_shared<A>(4);
	// The count of _ptr4 = 1
	cout << "The count of _ptr4 = " << _ptr4.use_count() << endl;

	cout << "-----------------test5：构造函数传入A*----------------------" << endl;

	A* a = new A(5);
	// 调用构造函数，计数器为1
	shared_ptr<A> _ptr5(a);
	// The count of _ptr5 = 1
	cout << "The count of _ptr5 = " << _ptr5.use_count() << endl;

	cout << "-----------------test6：拷贝构造函数----------------------" << endl;

	// 调用拷贝构造函数，计数加1
	shared_ptr<A> _ptr6 = _ptr5;
	// The count of _ptr6 = 2
	cout << "The count of _ptr6 = " << _ptr6.use_count() << endl;

	cout << "-----------------test7：赋值运算符----------------------" << endl;

	// 声明一个shared_ptr指针
	shared_ptr<A> _ptr7;
	// 通过赋值运算符指向同一个对象，计数器加1
	_ptr7 = _ptr6;
	// The count of _ptr7 = 3
	cout << "The count of _ptr7 = " << _ptr7.use_count() << endl;

	cout << "-----------------test8：拷贝构造函数----------------------" << endl;

	// 使用拷贝构造函数，计数器加1
	shared_ptr<A> _ptr8(_ptr7);
	// The count of _ptr8 = 4
	cout << "The count of _ptr8 = " << _ptr8.use_count() << endl;

	cout << "-----------------test9：分别调用构造函数生成shared_ptr，指向同一个对象----------------------" << endl;
	cout << "计数器都为1，当shared_ptr生命周期结束的时候，会调用析构函数，会重复释放内存，导致错误" << endl;

	// 两个智能指针都指向a9，使得重复释放内存，导致错误
	// 因为两个调用的都是构造函数，计数器的值都初始化为1，尽管指向的是同一片地址
	A* a9 = new A(9);
	shared_ptr<A> _ptr9(a9);
	//shared_ptr<A> _ptr10(a9);
	cout << "The count of _ptr9 = " << _ptr9.use_count() << endl;
	//cout << "The count of _ptr10 = " << _ptr10.use_count() << endl;

	cout << "-----------------test11：不能使用栈内存对shared_ptr指针进行初始化----------------------" << endl;
	cout << "因为当shared_ptr生命周期结束的时候，会调用析构函数，会delete掉指向的内存空间，而delete栈空间会导致错误" << endl;

	// 不能用栈内存对shared_ptr进行初始化
	A a11(11);
	//shared_ptr<A> _ptr11(&a11);

	cout << "-----------------test12：不能用shared_ptr的内部成员函数get()获取内部指针来给其他shared_ptr进行初始化----------------------" << endl;
	cout << "初始化是调用构造函数，计数器的值会初始化为1，在智能指针生命周期结束的时候，会差重复释放内存，导致错误" << endl;
	
	A* a12 = new A(12);
	shared_ptr<A> _ptr12(a12);
	//shared_ptr<A> _ptr13(_ptr12.get());
	

	cout << "-----------------test14----------------------" << endl;

	// C++17后 shared_ptr可以管理数组
	shared_ptr<int[]> _ptr14(new int[10]());
	*(_ptr14.get() + 1) = 14;
	cout << *(_ptr14.get() + 1) << endl;


	cout << "-----------------test15：使用智能指针管理数组----------------------" << endl;

	// 能编译
	shared_ptr<int> _ptr15(new int[10]());
	int* temp = _ptr15.get() + 1; // 不建议保存get函数返回的地址
	*(_ptr15.get() + 1) = 15;
	cout << "*temp = " << *temp << endl; // *temp = 15
	_ptr15.reset(); // 将智能指针释放，能够释放整个数组，而不是只释放一个int
	cout << "*temp = " << *temp << endl; // *temp = -572662307

	return 0;  
}










