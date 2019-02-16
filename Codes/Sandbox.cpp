/*
DOCUMENT CODE "Sandbox.cpp"
CREATION DATE 2017-05-18
SIGNATURE CODE_SANDBOX
TOPIC 沙箱 用来写一些没用的测试性东西
*/

#include "Overall.hpp"

//Check if this code file is enabled for testing.
#ifdef CODE_SANDBOX

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cmath>

#include <functional>

using namespace std;


template<typename ClassType, typename ValType, typename GetterReturnType = ValType, typename SetterParamType = ValType>
class PropertyWrapper {
public:
	template<typename Getter, typename Setter>
	PropertyWrapper(Getter getter, Setter setter) :
		getterFunc(getter), setterFunc(setter) {}

	const ValType& operator = (const ValType& right) {
		setterFunc(thisPtr, right);
		return right;
	}

	operator ValType(){
		return getterFunc(thisPtr);
	}

	void setThisPtr(ClassType* thisPtr) {
		this->thisPtr = thisPtr;
	}

private:
	ClassType* thisPtr;
	function<GetterReturnType(ClassType*)> getterFunc;
	function<void(ClassType*, SetterParamType)> setterFunc;
};

#define PROPERTY(classname, getter, setter, name)     \
static_assert(is_member_function_pointer<getter>::value && is_member_function_pointer<setter>::value); \
PropertyWrapper<classname, remove_cv<remove_reference<decltype(getter)>>, decltype(getter), decltype(setter)> name(getter, setter)


class Target {
public:
	Target() :
		intWrapper(&Target::getInt, &Target::setInt) {}

	void setInt(int i) { cout << "setInt() called, prevVal=" << val << ", i=" << i << endl; val = i; }
	int getInt() { cout << "getInt() called, val=" << val << endl; return val; }

	void setString(const string& str) { cout << "setString() called" << endl; this->str = str; }
	const string& getString() { cout << "getSTring() called" << endl; return str; }

	PropertyWrapper<Target, remove_cv<remove_reference<decltype(&Target::getInt)>>, decltype(&Target::getInt), decltype(&Target::setInt)> intWrapper;


private:
	int val;
	string str;
};


class A {
public:
	void initalaize(...) {
		
	}
};

class B {
public:

	template<typename... Args>
	shared_ptr<B> create(Args... args) {
		auto p = make_shared<B>();
		p->initalaize(args...);
		return p;
	}

private:
	B() {}
	void initalaize(...) {

	}

};



int main(int argc, char* argv[]) {

	auto a = make_shared<A>();
	a->initalaize(34,5643,1234);



	return 0;
}


#endif
