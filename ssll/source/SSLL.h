#ifndef _SSLL_H_
#define _SSLL_H_

#include <iostream>
#include <stdexcept>

namespace cop3530 {			// namespace
	
	template <typename T>		// class template
	
	class SSLL {
	
	private:					// data members
		typedef struct Node{	// Node struct
			T data;
			Node *next;
			T& ref() { return data;}
		}* nodePtr;
		
		nodePtr head;			// head pointer
		nodePtr tail;			// tail pointer
		std::size_t list_size;		// size of list
		
		
	public:					
		
		class SSLL_Iter {
		public:
			typedef T value_type;
			typedef std::ptrdiff_t difference_type;
			typedef T& reference;
			typedef T* pointer;
			typedef std::forward_iterator_tag iterator_category;
			
			typedef SSLL_Iter self_type;
			typedef SSLL_Iter& self_reference;
		private:
			nodePtr here;	// pointer to current node iterator points to
		public:
			// construct a SSLL Iterator assigning Node* here to NULL
			// unless a different value is passed. 
			explicit SSLL_Iter(nodePtr start = NULL) : here(start) {}	// explicit constructor; set Node* here to parameter start 
			// construct a SSLL iterator that sets Node* here to 
			// the same reference as src.here
			SSLL_Iter(const SSLL_Iter& src) : here(src.here) {}			// constructor; set Node* here to whatever src.here points to
			
			// return the data at the current location of the iterator
			// if data does not exist, throw an out_of_range exception
			reference operator*() const {								// return data at current node
				if(here == NULL)
					throw std::out_of_range("Null reference");
				return here->data;
			}
			
			// return a reference to the current location of the iterator
			// if data does not exist, throw an out_of_range exception
			pointer operator->() const {								// return reference to current node
				if(here == NULL)
					throw std::invalid_argument("Null reference");
				return here;
			}
			
			// if it's not self-reference, change Node* here 
			// to src.here. 
			self_reference operator=(const SSLL_Iter& src) {			// assignment operator 
					if(&src == this)										// check for self-assignment
						return *this;
					else {
						here = src.here;									// simply have here point to the here of SSLL_Const_Iter src
					}
			}
			
			// increment the iterator by simply moving here to the 
			// next node in the list
			self_reference operator++() { 								// preincrement operator overload
				here = here->next;										// simply move to the next Node in the list
				return *this;											// return this iterator
			}
			
			// increment the iterator by simply moving here to the 
			// next node in the list, but return the iterator with the
			// state of the iterator before incrementing
			self_type operator++(int) {   								// postincrement operator overload
				self_type results(*this);								// make a temporary iterator of current state
				here = here->next;										// move here to the next Node in the list
				return results;											// return the temporary iterator
			}
			
			// return whether or not the iterators point to
			// the same thing. 
			bool operator==(const SSLL_Iter& rhs) const {				// equality overload
				return here==rhs.here;									// check if iterators' here are pointing to same element
			}
			// return whether or not the iterators point to
			// the same thing. 
			bool operator!=(const SSLL_Iter& rhs) const {				// inequality overload
				return here!=rhs.here;									// check if iterators' here are not pointing to same element
			}
		}; // end SSLL_Iter
		
		
		class SSLL_Const_Iter {
		public:
			typedef T value_type;
			typedef std::ptrdiff_t difference_type;
			typedef const T& reference;
			typedef const T* pointer;
			typedef std::forward_iterator_tag iterator_category;
			
			typedef SSLL_Const_Iter self_type;
			typedef SSLL_Const_Iter& self_reference;
		private:
			const nodePtr here;	// immutable Node* instance field
		public:
		
			// construct a SSLL Iterator assigning Node* here to NULL
			// unless a different value is passed. If valid, set it to that
			// value, else throw an invalid_argument exception
			explicit SSLL_Const_Iter(nodePtr start) : here(start) {}	// explicit constructor; set Node* here to start
			
			// construct a SSLL iterator that sets Node* here to 
			// the same reference as src.here
			SSLL_Const_Iter(const SSLL_Const_Iter& src) : here(src.here) {}	// constructor; set Node* here to src's here
			
			// return the data at the current location of the iterator
			// if data does not exist, throw an out_of_range exception
			reference operator*() const {								// return data at current node
				if(here == NULL)
					throw std::out_of_range("Null reference");
				return here->data;
			}
			// return a reference to the current location of the iterator
			// if data does not exist, throw an out_of_range exception
			pointer operator->() const {								// return reference to current node
				if(here == NULL)
					throw std::out_of_range("Null reference");
				return here;
			}
			
			// if it's not self-reference, change Node* here 
			// to src.here. 
			self_reference operator=(const SSLL_Const_Iter& src) {
					if(&src == this)										// self-assignment check
						return *this;
					else {
						here = src.here;									// set here to src's here
					}
			}
			
			// increment the iterator by simply moving here to the 
			// next node in the list
			self_reference operator++() { 								// preincrement operator; move here to next node in list
				here = here->next;
				return *this;
			}
			// increment the iterator by simply moving here to the 
			// next node in the list, but return the iterator with the
			// state of the iterator before incrementing
			self_type operator++(int) {   								// postincrement operator; 
				self_type results(*this);								// create temporary iterator of current state
				here = here->next;										// move here to next node in list
				return results;											// return temporary iterator
			}
			
			// return whether or not the iterators point to
			// the same thing.
			bool operator==(const SSLL_Const_Iter& rhs) const {			// check if iterators' here point to same node
				return here==rhs.here;
			}
			// return whether or not the iterators point to
			// the same thing.
			bool operator!=(const SSLL_Const_Iter& rhs) const {			// check if iterators' here point to same node
				return here != rhs.here;
			}
		}; // end SSLL_Const_Iter
		
		
		//-----------------
		// types
		//------------------
		typedef std::size_t size_type;
		typedef T value_type;
		typedef SSLL_Iter iterator;
		typedef SSLL_Const_Iter const_iterator;

								// constructors & destructor
		SSLL() {				
			head = NULL;		// set head and tail to null
			tail = NULL;
			list_size = 0;		// list has size 0
		}
		// copy constructor. Make hard copy of src
		SSLL(const SSLL& src) {	// copy constructor
			head = NULL;
			tail = NULL;
			*this = src;
		}
		~SSLL() {
			clear(); 			// delete all data
		}
		
		// assignment operator overload. If not self-assignment,
		// make hard copy of src's list
		SSLL& operator=(SSLL& src) { 	// overload operator =
			if(&src == this)				// check for self-assignment
				return *this;
			else {							
				clear();					// otherwise clear all data
				nodePtr copyPtr = src.head; // copy data from src argument
				nodePtr temp;
				while(copyPtr != NULL) {	// copy until reaching null(last element)
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
			} // else
			list_size = src.list_size;	// copy list size
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
		} // replace
		
		// insert a node with data 'element' in 'position'
		// push all nodes at current 'position' and after by 1
		// throw invalid_argument exception if 'position' is invalid
		void insert(const T& element, int position) {
			if(position < 0 || position > list_size)
				throw std::invalid_argument("Invalid parameters");
			nodePtr newNode = new Node();
			newNode->next = NULL;
			newNode->data = element;
			if(position != 0) {
				if(position == list_size) {
					tail->next = newNode;
					tail = newNode;
					list_size++;
					return;
				}
				nodePtr temp = head;
				while(position-1 != 0) {
					temp = temp->next;
					position--;
				} // while
				newNode->next = temp->next;
				temp->next = newNode;
			} // if
			else {
				if(is_empty()) {
					head = newNode;
					tail = newNode;
				}
				else{
					newNode->next = head;
					head = newNode;
				} // else
			} // else
			list_size++;
		} // insert
		
		// insert a node with data 'element' to front of list
		void push_front(const T& element) {
			insert(element, 0);
		} // push_front
		
		// insert a node with data 'element' to end of list
		void push_back(const T& element) {
			insert(element, list_size);
		} // push_back
		
		// remove the first node in the list and
		// return the data it contained
		T pop_front() {
			return remove(0);
		} // pop_front
		
		// remove the last node in the list and
		// return the data it contained
		T pop_back() {
			return remove(list_size-1);
		} // pop_back
		
		// remove the node at position 'position' and patch up the
		// list to reflect this change. Throw an invalid_argument 
		// exception if 'position' is not a valid position in the list
		T remove(int position) {
			if(position < 0 || position > list_size)
				throw std::invalid_argument("Position not in range");
			nodePtr tempPtr = head;
			if(position == 0) {	// if removing first position
				T temp = head->data;	
				nodePtr tempPtr = head->next;
				delete head;
				head = tempPtr;	// advance head by one (will become NULL if end of list)
				list_size--;	// list size decremented
				return temp;	// return data at 'position'
			} // if
			int temp = 0;
			while(temp < position-1) {	// go to node previous to one that will be removed
				tempPtr = tempPtr->next;
				temp++;
			} // while

			T returnData = tempPtr->next->data;	// get data to be returned
			nodePtr tempPtr2 = tempPtr->next->next;	
			delete tempPtr->next;		
			tempPtr->next = tempPtr2;	// patch up list
			if(position == list_size-1)	// if removed last element
				tail = tempPtr;			// tail is updated
			list_size--;				// update list size
			return returnData;			// return data at 'position'
		} // remove
		
		// return the data at node 'position' without removing it
		// throw invalid_argument if position is out of bounds
		T item_at(int position) const {
			if(position < 0 || position > list_size)
				throw std::invalid_argument("Position not in range");
			if(position == 0)	// if first node
				return head->data;
			if(position == list_size-1)	// if last node
				return tail->data;
			nodePtr temp = head;
			while(position != 0) {	// every other node
				temp = temp->next;
				position--;
			}
			return temp->data;
		} 
		
		// create an iterator who's Node* here points to first element in list
		iterator begin() {
			return SSLL_Iter(head); 
		}
		// create an iterator who's Node* here points to NULL (one past last element in list)
		iterator end() {
			return SSLL_Iter();
		}
		// create a const iterator who's Node* here points to first element in list
		const_iterator begin() const {
			return SSLL_Const_Iter(head);
		}
		// create a const iterator who's Node* here points to NULL (one past last element in list)
		const_iterator end() const {
			return SSLL_Const_Iter();
		}
		// return if the list is empty of not (if head points to anything or not)
		bool is_empty() const {
			return head == NULL;
		} // is_empty
		
		// clear the list by deleting every node in the list 
		// then setting head and tail to NULL and list size to 0
		void clear() {
			nodePtr temp = head;
			while(temp != NULL) {
				temp = temp->next;
				delete head;
				head = temp;
			} // while
			head = NULL;
			tail = NULL;
			list_size = 0;
		} // clear
		
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
		
		// return size of the list
		size_t size() const {
			return list_size;
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
	}; // end class SSLL.h 
} // end namespace cop3530
#endif // _SSLL_H_

			