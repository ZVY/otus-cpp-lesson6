#pragma once

#include <memory>

template<typename T, typename _Alloc = std::allocator<T>>
class CustomList 
{
	private:
		struct Node
		{
			Node() : m_next(nullptr) { }
			Node(const T& t) : data(t), m_next(nullptr) { }

			T data;

			Node* m_next;
		};

		Node* m_head;
		using Alloc = typename _Alloc::template rebind<Node>::other;
		Alloc allocList;

	public:	
		CustomList() : m_head(nullptr) {}	
		~CustomList()
		{			
			while (m_head) {
				
				Node* newHead = m_head->m_next;
			
				allocList.destroy(m_head);
				allocList.deallocate(m_head, 1);
				
				m_head = newHead;	
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
			}
		}	

		Iterator begin() const {
			return Iterator(m_head);
		}	

		Iterator end() const {
			return Iterator(nullptr);
		}

		size_t size () const {
			size_t s = 0;
			for (Iterator it = begin(); it != end(); ++it) {
				++s;
			}

			return s;
		}	
};
