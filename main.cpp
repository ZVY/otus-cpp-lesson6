#include <iostream>
#include <map>

#include "CustomAllocator.h"
#include "CustomList.h"

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
		auto mapCustom = std::map<int, int, std::less<int>, CustomAllocator<std::pair<const int, int>, (Numb)>>{};
		for (size_t i = 0; i < Numb; ++i) {
			mapCustom[i] = factor(i);
			std::cout << i << " " << mapCustom[i] << std::endl;
		}
	}

	{
		CustomList<int> list;
		for (int i = 0; i < Numb; ++i)
		{
			list.append(i);
		}

		for (auto it = list.begin(); it != list.end(); ++it)
			std::cout << *it << std::endl;
	}

	{
		CustomList<int,CustomAllocator<int,Numb>> list;
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
