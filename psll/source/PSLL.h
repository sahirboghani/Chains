#ifndef _PSLL_H_
#define _PSLL_H_

#include <iostream>
#include <stdexcept>

namespace cop3530 {	// namespace

	template<typename T>	// class template
	
	class PSLL {
	
	private:	// data members
		typedef struct Node{	// Node struct
			T data;
			Node *next;
			T& ref() { return data;}
		}* nodePtr;
		
		nodePtr head;	// head pointer
		nodePtr tail;	// tail pointer
		nodePtr pool;	// pool 
		std::size_t list_size;	// size of list
		int pool_size;		// size of pool
		
	public:
	
		class PSLL_Iter {
		public:
			typedef T value_type;
			typedef std::ptrdiff_t difference_type;
			typedef T& reference;
			typedef T* pointer;
			typedef std::forward_iterator_tag iterator_category;
			
			typedef PSLL_Iter self_type;
			typedef PSLL_Iter& self_reference;
		private:
			nodePtr here;	// pointer to current node iterator points to
		public:
			// construct a PSLL Iterator assigning Node* here to NULL
			// unless a different value is passed. 
			explicit PSLL_Iter(nodePtr start = NULL) : here(start) {}
			
			// construct a PSLL iterator that sets Node* here to 
			// the same reference as src.here
			PSLL_Iter(const PSLL_Iter& src) : here(src.here) {}
			
			// return the data at the current location of the iterator
			// if data does not exist, throw an out_of_range exception
			reference operator*() const {
				if(here == NULL)
					throw std::out_of_range("Null reference");
				return here->data;
			}
			// return a reference to the current location of the iterator
			// if data does not exist, throw an out_of_range exception
			pointer operator->() const {
				if(here == NULL)
					throw std::out_of_range("Null reference");
				return here;
			}
			
			// if it's not self-reference, change Node* here 
			// to src.here.
			self_reference operator=(const PSLL_Iter& src) {
					if(&src == this)	// check for self assignment
						return *this;
					else {
						here = src.here;	// set here to src.here
					}
			}
			
			// increment the iterator by simply moving here to the 
			// next node in the list
			self_reference operator++() { // preincrement
				here = here->next;
				return *this;
			}
			
			// increment the iterator by simply moving here to the 
			// next node in the list, but return the iterator with the
			// state of the iterator before incrementing
			self_type operator++(int) {   // postincrement
				self_type results(*this);
				here = here->next;
				return results;
			}
			
			// return whether or not the iterators point to
			// the same thing. 
			bool operator==(const PSLL_Iter& rhs) const {
				return here==rhs.here;
			}
			
			// return whether or not the iterators point to
			// the same thing. 
			bool operator!=(const PSLL_Iter& rhs) const {
				return here!=rhs.here;
			}
		}; // end PSLL_Iter
		
		
		class PSLL_Const_Iter {
		public:
			typedef T value_type;
			typedef std::ptrdiff_t difference_type;
			typedef const T& reference;
			typedef const T* pointer;
			typedef std::forward_iterator_tag iterator_category;
			
			typedef PSLL_Const_Iter self_type;
			typedef PSLL_Const_Iter& self_reference;
		private:
			const nodePtr here;	// immutable Node* instance field
		public:
			// construct a PSLL Iterator assigning Node* here to NULL
			// unless a different value is passed. 
			explicit PSLL_Const_Iter(nodePtr start = NULL) : here(start) {}
			
			// construct a PSLL iterator that sets Node* here to 
			// the same reference as src.here
			PSLL_Const_Iter(const PSLL_Const_Iter& src) : here(src.here) {}
			
			// return the data at the current location of the iterator
			// if data does not exist, throw an out_of_range exception
			reference operator*() const {
				if(here == NULL)
					throw std::out_of_range("Null reference");
				return here->data;
			}
			// return a reference to the current location of the iterator
			// if data does not exist, throw an out_of_range exception
			pointer operator->() const {
				if(here == NULL)
					throw std::out_of_range("Null reference");
				return here;
			}
			// if it's not self-reference, change Node* here 
			// to src.here.
			self_reference operator=(const PSLL_Const_Iter& src) {
				if(&src == this)
						return *this;
					else {
						here = src.here;
					}
			}
			// increment the iterator by simply moving here to the 
			// next node in the list
			self_reference operator++() { // preincrement
				here = here->next;
				return *this;
			}
			// increment the iterator by simply moving here to the 
			// next node in the list, but return the iterator with the
			// state of the iterator before incrementing
			self_type operator++(int) {   // postincrement
				self_type results(*this);
				here = here->next;
				return results;
			}
			// return whether or not the iterators point to
			// the same thing.
			bool operator==(const PSLL_Const_Iter& rhs) const {
				return here==rhs.here;
			}
			// return whether or not the iterators point to
			// the same thing.
			bool operator!=(const PSLL_Const_Iter& rhs) const {
				return here!=rhs.here;
			}
		}; // end PSLL_Const_Iter
		
		
		//-----------------
		// types
		//------------------
		typedef std::size_t size_type;
		typedef T value_type;
		typedef PSLL_Iter iterator;
		typedef PSLL_Const_Iter const_iterator;
		//
		//		Constructors and Destructor
		//
		
		// set head, tail, and pool to NULL
		// set pool and list sizes to 0
		PSLL() {
			head = NULL;
			tail = NULL;
			pool = NULL;
			list_size = 0;
			pool_size = 0;
		}
		// copy constructor. Make hard copy of src
		PSLL(const PSLL& src) {
			head = NULL;
			tail = NULL;
			pool = NULL;
			*this = src;
		}
		// destructor
		// first clear the list into the pool
		// then delete the entire pool
		~PSLL() {
			clear();
			nodePtr temp = pool;
			while(temp != NULL) {
				temp = temp->next;
				delete pool;
				pool = temp;
			}
			pool = NULL;
			list_size = 0;
			pool_size = 0;
		}
		
		// assignment operator overload. If not self-assignment,
		// make hard copy of src's list and pool
		PSLL& operator=(const PSLL& src) {
			if(&src == this)
				return *this;
			else {
				clear();	// clear list nodes into pool then delete pool
				nodePtr temp = pool;
				while(temp != NULL) {
					temp = temp->next;
					delete pool;
					pool = temp;
				}
				pool = NULL;
				nodePtr copyPtr = src.head;
				while(copyPtr != NULL) {	// copy until reaching NULL (last element)
					if(head == NULL) {
						temp = new Node(*copyPtr);
						head = temp;
					} // if
					else {
						temp->next = new Node(*copyPtr);
						temp = temp->next;
					} // else
					if(copyPtr->next == NULL)
						tail = temp;
					copyPtr = copyPtr->next;
				} // while
				
				copyPtr = src.pool;	// copy pool
				while(copyPtr != NULL) {
						if(pool == NULL) {
							temp = new Node(*copyPtr);
							pool = temp;
						}
						else {
							temp->next = new Node(*copyPtr);
							temp = temp->next;
						}
						copyPtr = copyPtr->next;
				}
			} // else
			list_size = src.list_size;	// update list size
			pool_size = src.pool_size;	// update pool size
			update_list();
			return *this;
		}
		
		// replace data in node at 'position' with 'element'
		// if position is not valid, throw an invalid_argument exception 
		T replace(const T& element, int position) {
			if(position < 0 || position > list_size)
				throw std::invalid_argument("Position not in range");
			nodePtr tempPtr = head;
			while(position != 0) {
				tempPtr = tempPtr->next;
				position--;
			} // while
			T tempData = tempPtr->data;
			tempPtr->data = element;
			return tempData;
		}
		
		// insert a node with data 'element' in 'position'
		// push all nodes at current 'position' and after by 1
		// throw invalid_argument exception if 'position' is invalid
		void insert(const T& element, int position) {
			if(position < 0 || position > list_size)
				throw std::invalid_argument("Invalid parameters");
			if(pool == NULL) {	// if no pool nodes to use, create node
				nodePtr newNode = new Node();
				newNode->next = NULL;
				newNode->data = element;
				if(is_empty()) {	// if list is empty update head, tail, and list size
					head = newNode;
					tail = newNode;
					list_size++;
					return;
				}
				if(position != 0) {	
					nodePtr temp = head;
					while(position-1 != 0) {	// go to node previous to 'position'
						temp = temp->next;
						position--;
					} // while
					newNode->next = temp->next;	// insert and patch list
					temp->next = newNode;
				} // if
				else {
					newNode->next = head;
					head = newNode;
				} // else
				list_size++;	// update size of list
				return;
			}
			if(is_empty()) {	// if pool is not empty, use pool node instead of creating new node
				nodePtr newNode = pool;
				newNode->next = NULL;
				newNode->data = element;
				head = newNode;
				tail = newNode;
				return;
			}
			nodePtr newNode = pool;
			pool = pool->next;
			newNode->next = NULL;
			newNode->data = element;
			if(position != 0) {
				nodePtr temp = head;
				while(position-1 != 0) {
					temp = temp->next;
					position--;
				} // while
				newNode->next = temp->next;
				temp->next = newNode;
			} // if
			else {
				newNode->next = head;
				head = newNode;
			} // else
			list_size++;
			pool_size--;
			update_list();	// update list with desired conditions
		} // insert
		
		// insert a node with data 'element' to front of list
		// if element is not type T, throw invalid_argument exception
		void push_front(const T& element) {
			insert(element, 0);
		} // push_front
		
		// insert a node with data 'element' to end of list
		// if element is not type T, throw invalid_argument exception
		void push_back(const T& element) {
			insert(element, list_size);
		} // push_back
		
		// remove the first node in the list and
		// return the data it contained
		T pop_front() {
			return remove(0);
		}
		// remove the last node in the list and
		// return the data it contained
		T pop_back() {
			return remove(list_size-1);
		}
		
		// remove the node at position 'position' and patch up the
		// list to reflect this change. Throw an invalid_argument 
		// exception if 'position' is not a valid position in the list
		T remove(int position) {
			if(position < 0 || position > list_size)
				throw std::invalid_argument("Position not in range");
			nodePtr tempPtr = head;
			if(position == 0) {
				T temp = head->data;
				nodePtr tempPtr = head->next;
				head->next = pool;
				pool = head;
				head = tempPtr;
				if(head == NULL)
					tail = NULL;
				list_size--;
				pool_size++;
				return temp;
			} // if
			int temp = 0;
			while(temp < position-1) {
				tempPtr = tempPtr->next;
				temp++;
			} // while

			T returnData = tempPtr->next->data;
			nodePtr tempPtr2 = tempPtr->next->next;
			tempPtr->next->next = pool;
			pool = tempPtr->next;
			tempPtr->next = tempPtr2;
			if(position == list_size)
				tail = tempPtr;
			list_size--;
			pool_size++;
			return returnData;
		} // remove
		
		// return the data at node 'position' without removing it
		// throw invalid_argument if position is out of bounds
		T item_at(int position) const {
			if(position < 0 || position > list_size)
				throw std::invalid_argument("Position not in range");
			if(position == 0)
				return head->data;
			if(position == list_size-1)
				return tail->data;
			nodePtr temp = head;
			while(position != 0) {
				temp = temp->next;
				position--;
			}
			return temp->data;
		}
		
		// create an iterator who's Node* here points to first element in list
		iterator begin() {
			return PSLL_Iter(head); 
		}
		// create an iterator who's Node* here points to NULL (one past last element in list)
		iterator end() {
			return PSLL_Iter();
		}
		// create a const iterator who's Node* here points to first element in list
		const_iterator begin() const {
			return PSLL_Const_Iter(head);
		}
		// create a const iterator who's Node* here points to NULL (one past last element in list)
		const_iterator end() const {
			return PSLL_Const_Iter();
		}
		// return if the list is empty of not (if head points to anything or not)
		bool is_empty() const {
			return head == NULL;
		}
		// return size of the list
		size_t size() const {
			return list_size;
		}
		// clear the list by sending every node in list to the pool and setting head
		// and tail to NULL, list size to 0, and pool size to new size
		void clear() {
			nodePtr temp = pool;
			if(temp != NULL) {
				while(temp->next != NULL)
					temp = temp->next;
			}
			pool = head;
			head = NULL;
			tail = NULL;
			pool_size += list_size;
			list_size = 0;
		} // clear
		
		// if list has 100 or more elements and pool has more elements than list
		// deallocate half of the pool nodes
		void update_list() {
			if(list_size > 99 && pool_size > list_size) {
				nodePtr temp = pool;
				while(pool_size != list_size/2) {
					pool = pool->next;
					delete temp;
					temp = pool;
					pool_size--;
				}
			}
		}
		
		// check if there exists a Node in the list who's data is the same as 
		// 'element' using the 'equals' method for comparison
		bool contains(const T& element, bool equals(const T& a, const T& b)) const {
			nodePtr temp = head;
			while(temp != NULL) {
				if(equals(temp->data, element))
					return true;
				temp = temp->next;
			}
			return false;
		}
		
		// return an ostream& containing a print of the list's elements
		std::ostream& print(std::ostream& out) const {
			if(is_empty()) {
				out << "<empty list>";
				out << std::endl;
			}
			else {
				nodePtr temp = head;
				out << "[" << temp->data << "]";
				temp = temp->next;
				while(temp != NULL) {
					out << ",[" << temp->data << "]";
					temp = temp->next;
				}
				out << std::endl;
			}	
			return out;
		}
		
		// return a reference to the T data in node at 'position'
		// throw invalid_argument exception if position is invalid
		T& operator[](int position) {
			if(position < 0 || position > list_size)
				throw std::invalid_argument("Position not in range");
			if(position == 0)	// if first node
				return head->ref();
			if(position == list_size-1)	// if last node
				return tail->ref();
			nodePtr temp = head;
			while(position != 0) {	// every other node
				temp = temp->next;
				position--;
			}
			return temp->ref();
		}
		// return a const reference to the T data in node at 'position'
		// throw invalid_argument exception if position is invalid
		T const& operator[](int position) const {
			if(position < 0 || position > list_size)
				throw std::invalid_argument("Position not in range");
			if(position == 0)	// if first node
				return head->ref();
			if(position == list_size-1)	// if last node
				return tail->ref();
			nodePtr temp = head;
			while(position != 0) {	// every other node
				temp = temp->next;
				position--;
			}
			return temp->ref();
		}
	}; // class
} // namespace cop3530
#endif //_PSLL_H_