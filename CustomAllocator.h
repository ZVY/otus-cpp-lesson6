#pragma once
#include <array>

template <typename T, size_t Size = 10>
class CustomAllocator
{
	public:
		using value_type = T;
		using pointer = T* ;
		using reference = T&;
		using const_reference = const T&;

		template <class U>
		struct rebind {
			using other = CustomAllocator<U, Size>;
		};

		CustomAllocator() : index(0) {};
		~CustomAllocator() = default;

		pointer allocate(std::size_t n)
		{
			if (n == 0)
				return nullptr;

			if (index + n > Size)
				throw std::bad_alloc();

			pointer currPointer = &data[index];
			index += n;
			return currPointer;
		}

		template <typename ... Args >
		void construct(T* p, Args&& ... args)
		{
			new(p) T(std::forward <Args>(args) ...);
		}

		void deallocate(pointer, std::size_t n)
		{
			index -= n;
		}

		void destroy(T *p)
		{
			p->~T();
		}

	private:
		std::array<value_type, Size> data;
		size_t index = 0;
};
