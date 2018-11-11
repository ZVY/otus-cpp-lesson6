#include <iostream>
#include <vector>
#include <map>
#include <array>
#include <memory>

/*
template<typename T, size_t Size = 10>
struct CustomAllocator 
{
    using value_type = T;

    using pointer = T*;
    using const_pointer = const T*;
    using reference = T&;
    using const_reference = const T&;
		
	std::unique_ptr<unsigned char[]> data;

	//custom_allocator()
	//	: data(std::make_unique<unsigned char[]>(sizeof(value_type) * Size))
	//{
	//	//std::cout << "Allocator default ctor: " << this << std::endl;
	//}

	template <typename U, size_t> friend class CustomAllocator;


	
    template<typename U>
    struct rebind
	{	
		using other = CustomAllocator<U, Size>;
    };

    T *allocate(std::size_t n) {
        std::cout << __FUNCTION__ << "[ -A- n = " << n << "]" << n * sizeof(T) * Size << std::endl;
		
		if (data == nullptr)
		{
			data = std::move(std::make_unique<unsigned char[]>(sizeof(value_type) * Size));
		}

		auto p = std::malloc(n * sizeof(T));
        if (!p)
            throw std::bad_alloc();

        return reinterpret_cast<T *>(p);
    }

    void deallocate(T *p, std::size_t n) {
        //std::cout << __FUNCTION__ << "[n = " << n << "]" << std::endl;
        //std::free(p);
    }

    template<typename U, typename ...Args>
    void construct(U *p, Args &&...args) {
        std::cout << __FUNCTION__ << std::endl;
		new(p) U(std::forward<Args>(args)...);
    };

    //void destroy(T *p) {
        //std::cout << __FUNCTION__ << std::endl;
        //p->~T();
    //}

	
};
*/


template <typename T, size_t Size = 10>
class CustomAllocator
{
	public:
		using value_type = T;
		using pointer = T * ;

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

	private:
		std::array<value_type, Size> data;
		size_t index = 0;
};

int factor(int x) {
	if (!x)
		return 1;
	else
		return x * factor(x - 1);
}

int main(int, char *[]) 
{
	/*{
		auto mapStandard = std::map<int, int>{};
		for (size_t i = 0; i < 10; ++i) {
			mapStandard[i] = factor(i);
			std::cout << mapStandard[i] << std::endl;
		}
	}*/	
	
	//std::cout << factor(9);
	{
		auto mapCustom = std::map<int, int, std::less<int>, CustomAllocator<std::pair<const int, int>, 11>>{};
		for (size_t i = 0; i < 10; ++i) {
			mapCustom[i] = factor(i);
			std::cout << mapCustom[i] << std::endl;
		}
	}

	system("pause");

    return 0;
}
