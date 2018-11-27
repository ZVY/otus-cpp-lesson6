#pragma once

#include <memory>

template<typename T, typename _Alloc = std::allocator<T>>
class UnidirectLinkedList 
{
	private:
		struct Node
		{
			Node() : m_next(nullptr) { }
			Node(const T& t) : data(t), m_next(nullptr) { }

			T data;

			Node *m_next;
		};

		Node *m_head;
		int size = 0;
		using Alloc = typename _Alloc::template rebind<Node>::other;
		Alloc allocList;

	public:	
		UnidirectLinkedList() : m_head(nullptr) {}	
		~UnidirectLinkedList()
		{	
			Node *curr = m_head;
			for(int i = 0; i <= (size-1);)
			{
				if (i == (size - 1))
				{					
					allocList.destroy(curr);
					allocList.deallocate(curr, 1);
					curr = m_head;
					i = 0;
					size--;					
				}
				else
				{
					++i;
					curr = curr->m_next;
				}			
			}
		}

	public:
		class Iterator
		{
			public:
				Iterator(Node* node) : m_node(node) { }
						
				bool operator==(const Iterator& other) const {
					if (this == &other) {
						return true;
					}
					return m_node == other.m_node;
				}
						
				bool operator!=(const Iterator& other) const {
					return !operator==(other);
				}
						
				T operator*() const {
					if (m_node) {
						return m_node->data;
					} 
					return T();
				}
					
				void operator++() {
					if (m_node) {
						m_node = m_node->m_next;
					} 
				}

				Node *m_node;
		};	

		template <typename...Args>
		void append(Args&&... value) 
		{
			auto node = allocList.allocate(1);
			allocList.construct(node, std::forward<Args>(value)...);

			if (node) 
			{				
				node->m_next = m_head;
				m_head = node;
				size++;
				std::cout << "+" << m_head->data << std::endl;

			}
		}	

		Iterator begin() const {
			return Iterator(m_head);
		}	

		Iterator end() const {
			return Iterator(nullptr);
		}			
};