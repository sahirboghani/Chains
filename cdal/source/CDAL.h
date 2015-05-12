#ifndef _CDAL_H_
#define _CDAL_H_

#include <iostream>
#include <stdexcept>

namespace cop3530 {	// namespace

	template<typename T>	// class template
	class CDAL {
	
	private:	// data members
		typedef struct Node {	// node struct
			T list[50];	// list
			Node* next;
		}* nodePtr;
		
		nodePtr head;	// head pointer
		int tail;	// index of last element
		std::size_t list_size;	// list size
	
	public:
		class CDAL_Iter {
		public:
			typedef T value_type;
			typedef std::ptrdiff_t difference_type;
			typedef T& reference;
			typedef T* pointer;
			typedef std::forward_iterator_tag iterator_category;
			
			typedef CDAL_Iter self_type;
			typedef CDAL_Iter& self_reference;
		private:
			nodePtr here;	// pointer to current node iterator points to
			int index;		// index of current element iterator references in array
		public:
			// construct a CDAL Iterator assigning T* here to NULL and index to 0
			// unless a parameter is passed. 
			explicit CDAL_Iter(nodePtr start = NULL) : here(start) { 
				index = 0;
			}
			
			// construct a SDAL iterator that sets T* here to 
			// the same reference as src.here and index to src.index
			CDAL_Iter(const CDAL_Iter& src) : here(src.here)  { index = src.index;}
			
			// return the data at the current location of the iterator
			// if data does not exist, throw an out_of_range exception
			reference operator*() const {
				if(here == NULL)
					throw std::out_of_range("Null reference");
				return here->list[index];
			}
			// return a reference to the current location of the iterator
			// if data does not exist, throw an out_of_range exception
			pointer operator->() const {
				if(here == NULL)
					throw std::out_of_range("Null reference");
				return here->list;
			}
			// if it's not self-reference, change T* here 
			// to src.here and index to src.index. 
			self_reference operator=(const CDAL_Iter& src) {
					if(&src == this)
						return *this;
					else {
						here = src.here;
						index = src.index;
					}
			}
			
			// increment the iterator by simply moving here to the 
			// next element in the array. If reached end of array and there is 
			// a next node, change here to next node and index to 0
			self_reference operator++() { // preincrement
				++index;
				if(index >= 50) {
					here = here->next;
					index = 0;
				}
				return *this;
			}
			// increment the iterator by simply moving here to the 
			// next element in the array, but return the iterator with the
			// state of the iterator before incrementing. If reached end of array and
			// there is a next node, change here to next node and index to 0
			self_type operator++(int) {   // postincrement
				self_type results(*this);
				if(index >= 50) {
					here = here->next;
					index = 0;
				}
				return results;
			}
			
			// return whether or not the iterators point to
			// the same thing.
			bool operator==(const CDAL_Iter& rhs) const {
				return (here == rhs.here && index == rhs.index);
			}
			
			// return whether or not the iterators point to
			// the same thing. 
			bool operator!=(const CDAL_Iter& rhs) const {
				return (here != rhs.here && index != rhs.index);
			}
		}; // end CDAL_Iter
		
		
		class CDAL_Const_Iter {
		public:
			typedef T value_type;
			typedef std::ptrdiff_t difference_type;
			typedef const T& reference;
			typedef const T* pointer;
			typedef std::forward_iterator_tag iterator_category;
			
			typedef CDAL_Const_Iter self_type;
			typedef CDAL_Const_Iter& self_reference;
		private:
			const pointer here;	// immutable T* instance field
			int index;	// index of current element iterator references in array
		public:
			// construct a CDAL Iterator assigning T* here to NULL and index to 0
			// unless a parameter is passed. 
			explicit CDAL_Const_Iter(pointer start = NULL) : here(start) {
				index = 0; 
			}
			
			// construct a SDAL iterator that sets T* here to 
			// the same reference as src.here and index to src.index
			CDAL_Const_Iter(const CDAL_Const_Iter& src) : here(src.here) { index = src.index;}
			
			// return the data at the current location of the iterator
			// if data does not exist, throw an out_of_range exception
			reference operator*() const {
				if(here == NULL)
					throw std::out_of_range("Null reference");
				return here->list[index];
			}
			// return a reference to the current location of the iterator
			// if data does not exist, throw an out_of_range exception
			pointer operator->() const {
				if(here == NULL)
					throw std::out_of_range("Null reference");
				return here->list;
			}
			// if it's not self-reference, change T* here 
			// to src.here and index to src.index.
			self_reference operator=(const CDAL_Const_Iter& src) {
					if(&src == this)
						return *this;
					else {
						here = src.here;
						index = src.here;
					}
			}
			
			// increment the iterator by simply moving here to the 
			// next element in the array. If reached end of array and there is 
			// a next node, change here to next node and index to 0
			self_reference operator++() { // preincrement
				++index;
				if(index >= 50) {
					here = here->next;
					index = 0;
				}
				return *this;
			}
			// increment the iterator by simply moving here to the 
			// next element in the array, but return the iterator with the
			// state of the iterator before incrementing. If reached end of array and
			// there is a next node, change here to next node and index to 0
			self_type operator++(int) {   // postincrement
				self_type* results(*this);
				if(index >= 50) {
					here = here->next;
					index = 0;
				}
				return results;
			}
			
			// return whether or not the iterators point to
			// the same thing. 
			bool operator==(const CDAL_Const_Iter& rhs) const {
				return here==rhs.here;
			}
			// return whether or not the iterators point to
			// the same thing.
			bool operator!=(const CDAL_Const_Iter& rhs) const {
				return here!=rhs.here;
			}
		}; // end CDAL_Const_Iter
		
		
		//-----------------
		// types
		//------------------
		typedef std::size_t size_type;
		typedef T value_type;
		typedef CDAL_Iter iterator;
		typedef CDAL_Const_Iter const_iterator;
		
		CDAL() {	// constructor
			head = new Node();	// head = new node
			head->next = NULL;
			tail = -1;	// tail = -1, list size = 0
			list_size = 0;
		}
		// make hard copy of src's data
		CDAL(const CDAL& src) {	// copy constructor
			head = NULL;
			tail = -1;
			list_size = 0;
			*this = src;	// copy src's data
		}
		// destroy the list by deleting every node in the list
		// then set instance variables to appropriate values
		~CDAL() {
			nodePtr temp = head;
			while(temp != NULL) {
				temp = temp->next;
				delete head;
				head = temp;
			}
			tail = -1;
			list_size = 0;
			head = NULL;
		}
		// assignment operator overload. If not self-assignment,
		// clear contents and made hard copy of src's array
		CDAL& operator=(const CDAL& src) {
			if(&src == this)
				return *this;
			else {
				nodePtr temp2 = head;
				while(temp2 != NULL) {
					temp2 = temp2->next;
					delete head;
					head = temp2;
				}
				tail = -1;
				list_size = 0;
				head = NULL;
				nodePtr copyPtr = src.head;
				nodePtr temp;
				while(copyPtr != NULL) {
					if(head == NULL) {
						temp = new Node(*copyPtr);
						head = temp;
					} // if
					else {
						temp->next = new Node(*copyPtr);
						temp = temp->next;
					} // else
					copyPtr = copyPtr->next;
				} // while
			}
			tail = src.tail;
			list_size = src.list_size;
			return *this;
		}
		
		// replace data in array at 'position' with 'element'
		// if position is not valid, throw an invalid_argument exception 
		T replace(const T& element, int position) {
			if(position < 0 || position > list_size)
				throw std::invalid_argument("Position not in range");
			int temp = position;
			nodePtr tempPtr = head;
			while(temp/50 != 0) {
				tempPtr = tempPtr->next;
				temp /= 50;
			}
			T returnData = tempPtr->list[position%50];
			tempPtr->list[position%50] = element;
			return returnData;
		}
		
		// find the appropriate node in list where position is and insert 
		// 'element' there. Then patch list to reflect change and update list size
		// and tail. Throw invalid_argument exception if 'position' is invalid
		void insert(const T& element, int position) {
			if(position < 0 || position > list_size)
				throw std::invalid_argument("Invalid parameters");
			nodePtr tempPtr = head;
			int last_array = tail/50 + 1;						// number of nodes/arrays
			
			if((tail + 1) % 50 == 0 && tail > 0) {				// if the last array is full create a new one
				while(tempPtr->next != NULL) 
					tempPtr = tempPtr->next;
				tempPtr->next = new Node();
				last_array++;									// number of nodes/arrays has increased by 1
			}
			
			int change_array = position/50 + 1;					// node/array in which element is being placed
			tempPtr = head;
			T temp;
			
			if(position == list_size) {
				for(int i = position/50; i>0; i--)
					tempPtr = tempPtr->next;
				tempPtr->list[position%50] = element;
				tail++;
				list_size++;
				return;
			}
			for(int i = last_array; i > change_array; i--) {	// traverse nodes from last to right before change_array backwards
				tempPtr = head;
				for(int j = 1; j < i-1; j++)					// send tempPtr to node corresponding to i-1
					tempPtr = tempPtr->next;
				temp = tempPtr->list[49];						// set temp to last value in array right before the one we push
				tempPtr = tempPtr->next;						// go to array that is about to get pushed
				
				for(int j = 49; j > 0; j--) 					// push every value by 1 except the first
					tempPtr->list[j] = tempPtr->list[j-1];
					
				tempPtr->list[0] = temp;						// first value is equal to last value of previous node's array
			}
			tempPtr = head;										
			for(int j = 1; j < change_array; j++)				// send tempPtr to node where element is to be inserted
				tempPtr = tempPtr->next;
			
			for(int i = 49; i > position % 49; i--) 			// push values that come after the insert position by 1
				tempPtr->list[i] = tempPtr->list[i-1];
			
			tempPtr->list[position%50] = element;				// insert element in it's position
			
			tail++;												// update tail
			list_size++;										// update list_size
		} // insert
		
		// remove the element at position 'position' and patch up the
		// list to reflect this change. Update list after removal according to 
		// stated conditions. Throw an invalid_argument 
		// exception if 'position' is not a valid position in the list
		T remove(int position) {
			if(position < 0 || position > list_size)
				throw std::invalid_argument("Position not in range");
			nodePtr tempPtr = head;								// temporary node pointers to go through the nodes/arrays
			nodePtr tempPtr2;
			
			int last_array = tail/50 + 1;						// number of nodes/arrays
			int change_array = position/50 + 1;					// node/array in which element is being removed from
			T returnData;										// what will be removed and returned
			
			for(int i = position/50; i>0; i--)					// send tempPtr to node where position is
				tempPtr = tempPtr->next;	
			
			for(int i = change_array; i < last_array; i++) {	// traverse nodes from the one we will remove T from to the last node
				if(i == change_array) {							// * when we are at the array where position exists
					returnData = tempPtr->list[position%50];		// * get T which will be removed
					for(int j = position%50; j < 49; j++)		// * pull elements in that array from 
						tempPtr->list[j] = tempPtr->list[j+1];	//   position to end-1 by 1
					tempPtr2 = tempPtr;							//  	
					tempPtr = tempPtr->next;					// give the last value of this array the first value of the next one
					tempPtr2->list[49] = tempPtr->list[0];		//
				}
				
				else {											// every other array before the last one
					for(int j = 0; j < 49; j++) 
						tempPtr->list[j] = tempPtr->list[j+1];	// pull elements in that array from beginning to end-1 by 1
					tempPtr2 = tempPtr;							
					tempPtr = tempPtr->next;					
					tempPtr->list[49] = tempPtr->list[0];			// give the last value of this array the first value of the next one
				}
			}
			
			if(change_array == last_array) {					// if the position is in the last array
				returnData = tempPtr->list[position%50];			// 
				for(int i = position%50; i < tail % 50; i++) 	// pull elements in array from position to tail by 1
					tempPtr->list[i] = tempPtr->list[i+1];		//
				tempPtr->list[tail%50] = 0;					// should be "=NULL" 
			}
			else {												// if we just need to fix the last array and it doesn't include position
				for(int i = 0; i < tail % 49 - 1; i++)			// pull elements from start of list to tail by 1
					tempPtr->list[i] = tempPtr->list[i+1];		//
				tempPtr->list[tail%50] = 0;					// should be "=NULL"
			}
			
			tail--;
			list_size--;
			
			return returnData;
		}
		// remove the first element in the array and
		// return it
		T pop_front() {
			return remove(0);
		}
		// remove the last element in the array and
		// return it
		T pop_back() {
			return remove(tail);
		}
		// insert 'element' to front of array
		// if element is not type T, throw invalid_argument exception
		void push_front(const T& element) {
			insert(element, 0);
		}
		// insert 'element' to end of array
		// if element is not type T, throw invalid_argument exception
		void push_back(const T& element) {
			insert(element, list_size);
		}
		// return the element at array 'position' without removing it
		// throw invalid_argument if position is out of bounds
		T item_at(int position) const {
			if(position < 0 || position > list_size)
				throw std::invalid_argument("Position not in range");
			T returnData;
			nodePtr tempPtr = head;
			for(int i = position/50; i>0; i--)
				tempPtr = tempPtr->next;
			return tempPtr->list[position%50];
		}
		// create an iterator who's Node* here points to first node in the list
		iterator begin() {
			return CDAL_Iter(head); 
		}
		// create an iterator who's Node* here points to NULL (one past last element in list)
		iterator end() {
			return CDAL_Iter();
		}
		// create a const iterator who's Node* here points to first node in the list
		const_iterator begin() const {
			return CDAL_Const_Iter(head);
		}
		// create a const iterator who's Node* here points to NULL (one past last element in list)
		const_iterator end() const {
			return CDAL_Const_Iter();
		}
		
		// return if list is empty or not (if head = -1)
		bool is_empty() const{
			return list_size == 0;
		}
		
		// return size of list
		size_t size() const {
			return list_size;
		}
		// clear the list by setting all elements in all arrays to NULL
		// then update list according to conditions
		void clear() {
			nodePtr temp = head;
			while(temp != NULL) {
				for(int i = 0; i < 50; i++) {
					temp->list[i] = 0; // should be "=NULL"
				}
				temp = temp->next;
			}
			list_size = 0;
			head = NULL;
			//update_list();
			tail = -1;
		} // clear
		
		// update list method: if more than half of the arrays are unused
		// deallocate half the unused items
		void update_list() {
			int last_array = tail/50 + 1;						// number of nodes/arrays
			int check_array = last_array % 2 == 0 ? last_array / 2 + 1 : last_array / 2 + 2; // "middle"ish array that we want to check 
			nodePtr temp = head;
			for(int i = check_array-1; i > 0; i--) 
				temp = temp->next;
			if(temp->list[0] != 0)
				return;
			nodePtr temp2 = temp;
			for(int i = check_array; i <= last_array; i++) {
				temp = temp->next;
				delete temp2;
				temp2 = temp;
			}			
		}
		
		// check if there exists an element in the arrays equal to 
		// 'element' using the 'equals' method for comparison
		bool contains(const T& element, bool equals(const T& a, const T& b)) const {
			nodePtr temp = head;
			while(temp != NULL) {
				for(int i = 0; i < 50; i++) 
					if(equals(temp->list[i], element))
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
				out << "[" << temp->list[0] << "]";
				if(tail > 49) {
					for(int i = 1; i < 50; i++)
						out << ",[" << temp->list[i] << "]";
					temp = temp->next;
					while(temp->next != NULL) {
						for(int i = 0; i < 50; i++)
							out << ",[" << temp->list[i] << "]";
						temp = temp->next;
					}
					for(int i = 0; i <= tail%50; i++)
						out << ",[" << temp->list[i] << "]";
				}
				else 
					for(int i = 1; i <= tail; i++)
						out << ",[" << temp->list[i] << "]";
			}
			out << std::endl;
			return out;
		}
		
		// return a reference to the T data in array at 'position'
		// throw invalid_argument exception if position is invalid
		T& operator[](int position) {
			if(position < 0 || position > list_size)
				throw std::invalid_argument("Position not in range");
			T returnData;
			nodePtr tempPtr = head;
			for(int i = position/50; i>0; i--)
				tempPtr = tempPtr->next;
			return tempPtr->list[position%50];
		}
		// return a const reference to the T data in array at 'position'
		// throw invalid_argument exception if position is invalid
		T const& operator[](int position) const {
			if(position < 0 || position > list_size)
				throw std::invalid_argument("Position not in range");
			T returnData;
			nodePtr tempPtr = head;
			for(int i = position/50; i>0; i--)
				tempPtr = tempPtr->next;
			return tempPtr->list[position%50];
		}
	}; // class CDAL
} // namespace cop3530

#endif // _CDAL_H_