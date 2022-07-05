#pragma once
#include<iostream>
using namespace std;
template<class T>
class sharedptr {
private:
	T* ptr;
	int* count;//引用计数

public:
	sharedptr(T* ptr = nullptr) :ptr(ptr)
	{
		if (this->ptr == nullptr) {
			count = new int(0);
		}
		else {
			count = new int(1);
		}
	}
	sharedptr(sharedptr& ptr) {
		if (this != &ptr) {
			(*ptr.count)++;
			this->ptr = ptr.ptr;
			this->count = ptr.count;
			
		}

	}
	//移动构造

	sharedptr(sharedptr&& ptr) {
		
			this->ptr = ptr.ptr;
			this->count = ptr.count;
			ptr.count = nullptr;
			ptr.ptr = nullptr;
	}
	//移动赋值
	sharedptr& operator=(const sharedptr&& ptr) {
		if (count != ptr.count) {
			swap(this, ptr);
		}
		return *this;
	}
	//运算符重载
	sharedptr& operator=(sharedptr& ptr) {
		if (count == ptr.count) {
			return *this;
		}
		//考虑到空对象调用这个函数   他的count为0
		// 因为this->count在堆上，不管不好
		// 左计数减1
		(*this->count)--;
		// nullptr 的 count 为 -1 ， 但是delete nullptr可以
		if ((*this->count) <= 0) {
			delete this->count;
			delete this->ptr;
		}

		//接下来是浅拷贝
		(*ptr.count)++;
		this->count = ptr.count;
		this->ptr = ptr.ptr;
		
		return *this;

	}
	~sharedptr() {
		(*this->count)--;
		//当引用计数为负数时就释放内存
		if ((*this->count) <= 0) {
			delete count;
			delete ptr;
		}
	}
	T& operator*() {
		return *(this->ptr);
	}
	T& operator->() {
		return this->ptr;
	}
	int getcount() {
		return *this->count;
	}

};
template<class T>
class uniqueptr {
private:
	T* ptr;
	uniqueptr(const uniqueptr&) = delete;
	uniqueptr& operator=(const uniqueptr&) = delete;
public:
	uniqueptr(T* ptr=NULL) :ptr(ptr) {}
	~uniqueptr() {
		if (ptr != NULL) {
			delete ptr;
			ptr = NULL;
		}
	}
	T* get() {// 获取资源，调用方应该只使用不释放，否则会两次delete资源
		return this->ptr;
	}
	//1. 释放源资源，指向新资源
	void reset(T*ptr) {
		if (ptr != NULL) {
			delete ptr;
			ptr = NULL;
		}
		this->ptr = ptr;
		
	}
	//返回资源，放弃对资源的管理
	T* release() {
		T* p = this->ptr;
		this->ptr = NULL;
		return p;
	}
	//// 是否持有资源
	operator bool() const {
		return ptr != NULL;
	}
	T& operator * ()
	{
		return *ptr;
	}

	T* operator -> ()
	{
		return ptr;
	}
};