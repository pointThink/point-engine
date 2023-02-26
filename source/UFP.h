#pragma once

#include "Core.h"

namespace PE
{
	class ENGINE_API UFP
	{
		public:
		void Call() {}
		bool IsNullPtr() {return true;}
		void SetNullPtr() {}
	};

	class ENGINE_API FunctionPointer : public UFP
	{
		void (*pointer)();

		public:
		FunctionPointer(void (*pointer)());
		void Call();

		bool IsNullPtr();
		void SetNullPtr();
	};

	template<typename T>
	class ENGINE_API MethodPointer : public UFP
	{
		public:
		MethodPointer(T * object, void (T::*function_pointer)());
		void Call();
		bool IsNullPtr();
		void SetNullPtr();

		private:
		T * object_pointer;
		void (T::*function_pointer)();
	};
}
