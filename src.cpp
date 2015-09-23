// EnterLeaveTest.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"

#include <string>
#include <memory>

#define $logme FunctionLifeContext<Logger> __logger(__FUNCTION__	
#define $param(...) FunctionLifeContext<Param<__VA_ARGS__>, __VA_ARGS__> __param(__FUNCTION__,
#define $$(name, ...) $##name __VA_ARGS__);

template <typename T, typename ...ARG>
class FunctionLifeContext {
public:
	FunctionLifeContext(){}
	FunctionLifeContext(const std::string &name, ARG ...args) :
		name(name), obj(new T()){
		obj->OnEnter(name, args...);
	}
	virtual ~FunctionLifeContext() {
		obj->OnLeave(name);
	}

private:
	std::string name;
	std::unique_ptr<T> obj;
};

template <typename ...ARG>
class IFunctionLifeContext {
public:
	virtual void OnEnter(const std::string &fname, ARG ...arg) {};
	virtual void OnLeave(const std::string &fname, ARG ...arg) {};
};

class Logger : IFunctionLifeContext<> {
public:
	virtual void OnEnter(const std::string &fname) {
		printf("Enter %s\n", fname.c_str());
	}

	virtual void OnLeave(const std::string &fname){
		printf("Leave %s\n", fname.c_str());
	}
};

void foo(int a,int b, int c);

#include <stdarg.h>
#include <iostream>
#include <functional>
#include <array>

template <typename ...ARG>
class Param : IFunctionLifeContext<ARG...> {
public:
	virtual void OnEnter(const std::string &fname, ARG ...arg) {
		print(arg...);

	}

	virtual void OnLeave(const std::string &fname) {
		printf("Leave %s\n", fname.c_str());
	}

private:
	template<typename T>
	void print(T v) {
		std::cout << v;
	}
	template<typename T, typename... Args>
	void print(T first, Args... args) {
		std::cout << first;
		print(args...);
	}
};

void foo(int a, int b, int c) { $$(logme) $$(param(int, int, int), a, b, c);

}

int main()
{

	foo(5,5,2);

    return 0;
}

