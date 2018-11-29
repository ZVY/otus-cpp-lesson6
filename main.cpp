#include <iostream>
#include <map>

#include "ReservAllocator.h"
#include "UnidirectLinkedList.h"

int factor(int x) {
	if (!x)
		return 1;
	else
		return x * factor(x - 1);
}

const int Numb = 10;

int main(int, char *[]) 
{
	{
		auto mapStandard = std::map<int, int>{};
		for (size_t i = 0; i < Numb; ++i) {
			mapStandard[i] = factor(i);
			std::cout << i << " " << mapStandard[i] << std::endl;
		}
	}
		
	{
		// for MSVS need Numb+1 (!)
		auto mapCustom = std::map<int, int, std::less<int>, ReservAllocator<std::pair<const int, int>, (Numb)>>{};
		for (size_t i = 0; i < Numb; ++i) {
			mapCustom[i] = factor(i);
			std::cout << i << " " << mapCustom[i] << std::endl;
		}
	}

	{
		UnidirectLinkedList<int> list;
		for (int i = 0; i < Numb; ++i)
		{
			list.append(i);
		}

		for (auto it = list.begin(); it != list.end(); ++it)
			std::cout << *it << std::endl;
	}

	{
		UnidirectLinkedList<int,ReservAllocator<int,Numb>> list;
		for (int i = 0; i < Numb; ++i)
		{
			list.append(i);
		}

		for (auto it = list.begin(); it != list.end(); ++it)
			std::cout << *it << std::endl;
	}
			
	//system("pause");

    return 0;
}
