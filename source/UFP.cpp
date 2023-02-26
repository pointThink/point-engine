#include "UFP.h"

PE::FunctionPointer::FunctionPointer(void (*function_pointer)())
{
	this->pointer = function_pointer;
}

void PE::FunctionPointer::Call()
{
	pointer();
}

bool PE::FunctionPointer::IsNullPtr()
{
	return pointer == nullptr;
}

void PE::FunctionPointer::SetNullPtr()
{
	pointer = nullptr;
}

template<typename T>
PE::MethodPointer<T>::MethodPointer(T* object, void (T::*function_pointer)())
{
	this->object_pointer = object;
	this->function_pointer = function_pointer;
}

template<typename T>
void PE::MethodPointer<T>::Call()
{
	(object_pointer->*function_pointer)();
}

template<typename T>
bool PE::MethodPointer<T>::IsNullPtr()
{
	return function_pointer == nullptr;
}

template<typename T>
void PE::MethodPointer<T>::SetNullPtr()
{
	function_pointer = nullptr;
}
