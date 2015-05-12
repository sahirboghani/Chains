#ifndef _SDAL_H_
#define _SDAL_H_

#include <iostream>
#include <stdexcept>

namespace cop3530 {	// namespace

	template<typename T>	// class template
	class SDAL {
	
	private:	// data members
		T* list;	// list
		int head;	// head index
		int tail;	// tail index
		int array_size;	// array size
		std::size_t list_size;	// list size
		
	public:
		class SDAL_Iter {
		public:
			typedef T value_type;
			typedef std::ptrdiff_t difference_type;
			typedef T& reference;
			typedef T* pointer;
			typedef std::forward_iterator_tag iterator_category;
			
			typedef SDAL_Iter self_type;
			typedef SDAL_Iter& self_reference;
		private:
			pointer here;	// pointer to current element iterator points to
		public:
			// construct a SDAL Iterator assigning T* here to NULL
			// unless a parameter is passed. 
			explicit SDAL_Iter(pointer start) : here(start) {}
			
			// construct a SDAL iterator that sets T* here to 
			// the same reference as src.here
			SDAL_Iter(const SDAL_Iter& src) : here(src.here) {}
			
			// return the data at the current location of the iterator
			// if data does not exist, throw an out_of_range exception
			reference operator*() const {
				if(here == NULL)
					throw std::out_of_range("Null reference");
				return *here;
			}
			// return a reference to the current location of the iterator
			// if data does not exist, throw an out_of_range exception
			pointer operator->() const {
				if(here == NULL)
					throw std::out_of_range("Null reference");
				return here;
			}
			
			// if it's not self-reference, change T* here 
			// to src.here. 
			self_reference operator=(const SDAL_Iter& src) {
					if(&src == this)										// check for self-assignment
						return *this;
					else {
						here = src.here;									// simply have here point to the here of SSLL_Const_Iter src
					}
			}
			
			// increment the iterator by simply moving here to the 
			// next element in the array
			self_reference operator++() { // preincrement
				++here;
				return *this;
			}
			
			// increment the iterator by simply moving here to the 
			// next element in the array, but return the iterator with the
			// state of the iterator before incrementing
			self_type operator++(int) {   // postincrement
				self_type results(*this);
				++here;
				return results;
			}
			
			// return whether or not the iterators point to
			// the same thing. 
			bool operator==(const SDAL_Iter& rhs) const {
				return here==rhs.here;
			}

			// return whether or not the iterators point to
			// the same thing. 
			bool operator!=(const SDAL_Iter& rhs) const {
				return here!=rhs.here;
			}
		}; // end SDAL_Iter
		
		
		class SDAL_Const_Iter {
		public:
			typedef T value_type;
			typedef std::ptrdiff_t difference_type;
			typedef const T& reference;
			typedef const T* pointer;
			typedef std::forward_iterator_tag iterator_category;
			
			typedef SDAL_Const_Iter self_type;
			typedef SDAL_Const_Iter& self_reference;
		private:
			const int *here;	// immutable T* instance field
		public:
			// construct a SDAL Iterator assigning T* here to NULL
			// unless a parameter is passed. 
			explicit SDAL_Const_Iter(pointer start) : here(start) {}
			
			// construct a SDAL iterator that sets T* here to 
			// the same reference as src.here
			SDAL_Const_Iter(const SDAL_Const_Iter& src) : here(src.here) {}
			
			// return the data at the current location of the iterator
			// if data does not exist, throw an out_of_range exception
			reference operator*() const {
				if(here == NULL)
					throw std::out_of_range("Null reference");
				return *here;
			}
			// return a reference to the current location of the iterator
			// if data does not exist, throw an out_of_range exception
			pointer operator->() const {
				if(here == NULL)
					throw std::out_of_range("Null reference");
				return here;
			}
			// if it's not self-reference, change T* here 
			// to src.here. 
			self_reference operator=(const SDAL_Const_Iter& src) {
					if(&src == this)										// check for self-assignment
						return *this;
					else {
						here = src.here;									// simply have here point to the here of SSLL_Const_Iter src
					}
			}
			
			// increment the iterator by simply moving here to the 
			// next element in the array
			self_reference operator++() { // preincrement
				++here;
				return *this;
			}
			// increment the iterator by simply moving here to the 
			// next element in the array, but return the iterator with the
			// state of the iterator before incrementing
			self_type operator++(int) {   // postincrement
				self_type results(*this);
				++here;
				return results;
			}
			// return whether or not the iterators point to
			// the same thing. 
			bool operator==(const SDAL_Const_Iter& rhs) const {
				return here==rhs.here;
			}
			// return whether or not the iterators point to
			// the same thing.
			bool operator!=(const SDAL_Const_Iter& rhs) const {
				return here!=rhs.here;
			}
		}; // end SDAL_Const_Iter
		
		
		//-----------------
		// types
		//------------------
		typedef std::size_t size_type;
		typedef T value_type;
		typedef SDAL_Iter iterator;
		typedef SDAL_Const_Iter const_iterator;
		
		SDAL() {						// default constructor
			head = -1;					// head and tail = -1
			tail = -1;
			array_size = 50;			// array size 50
			list_size = 0;				// list size 0
			list = new T[50];
			
		}						
		SDAL(int a_size) {
			if(a_size < 1)
				throw std::invalid_argument("Size must be > 0");
			list = new T[a_size];		// allocate new array of size parameter
			head = -1;					// head and tail = 0			
			tail = -1;
			list_size = 0;				// list size 0
			array_size = a_size;		// array size a_size
		}
		// copy constructor, make hard copy of src. 
		SDAL(const SDAL& src) {			// copy constructor
			head = -1;
			tail = -1;
			array_size = 0;
			list_size = 0;
			*this = src;				// copy all data over
		}
		~SDAL() {						// destructor
			delete list;				// delete array
			list = NULL;
			head = -1;					// head and tail = -1
			tail = -1;					// array and list size = 0
			list_size = 0;
			array_size = 0;
		}
		// assignment operator overload. If not self-assignment,
		// clear contents and made hard copy of src's array
		SDAL& operator=(const SDAL& src) {
			if(&src == this)
				return *this;
			else {
				clear();
				list = new T[src.array_size];
				int temp = src.head;
				while(temp <= src.tail) {
					list[temp] = src.item_at(temp);
					temp++;
				}
				head = src.head;	// update instance fields
				tail = src.tail;
				array_size = src.array_size;
				list_size = src.list_size;
			}
		}
		// replace data in array at 'position' with 'element'
		// if position is not valid, throw an invalid_argument exception 
		T replace(const T& element, int position) {
			if(position < 0 || position > list_size)
				throw std::invalid_argument("Position not in range");
			T returnData = list[position];
			list[position] = element;
			return returnData;
		}
		
		// first update list in case it is full
		// insert data 'element' in array slot 'position'
		// push all elements at current 'position' and after by 1
		// and increase list size by 1
		// throw invalid_argument exception if 'position' is invalid
		void insert(const T& element, int position) {
			if(position < 0 || position > list_size)
				throw std::invalid_argument("Invalid parameters");
			update_list();
			if(is_empty()) {
				list[position] = element;
				head = 0;
				tail = 0;
				list_size++;
				return;
			}
			if(position == array_size) {
				list[position] = element;
				tail++;
				list_size++;
				return;
			}
			
			for(int i = tail; i >= position; i--) {
				list[i+1] = list[i];
			}
			tail++;
			list[position] = element;
			list_size++;
		}
		
		// remove the element at position 'position' and patch up the
		// list to reflect this change. Update list after removal according to 
		// stated conditions. Throw an invalid_argument 
		// exception if 'position' is not a valid position in the list
		T remove(int position) {
			if(position < 0 || position > list_size)
				throw std::invalid_argument("Position not in range");
			T returnData = list[position];
			if(position == 0 && tail == 0) {
				list[position] = 0; // is actually "= NULL"
				head = -1;
				tail = -1;
				list_size--;
				return returnData;
			}
			if(position == tail) {
				list[tail--] = 0; // is actually "= NULL"
				list_size--;
				update_list();
				return returnData;
			}
			for(int i = position; i < tail; i++) {
				list[i] = list[i+1];
			}
			list[tail--] = 0; // is actually "= NULL"
			list_size--;
			update_list();
			return returnData;
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
		
		// remove the first element in the array and
		// return it
		T pop_front() {
			return remove(0);
		}	
		// remove the last element in the array and
		// return it
		T pop_back() {
			return remove(list_size-1);
		}
		
		// return the element at array 'position' without removing it
		// throw invalid_argument if position is out of bounds
		T item_at(int position) const {
			if(position < 0 || position > list_size)
				throw std::invalid_argument("Position not in range");
			if(is_empty())
				return 0; // is actually "= NULL"
			return list[position];
		}
		
		// create an iterator who's T* here points to first element in the array
		iterator begin() {
			return SDAL_Iter(list); 
		}
		// create an iterator who's T* here points to one past last element in the array
		iterator end() {
			return SDAL_Iter(list + list_size);
		}
		// create a const iterator who's T* here points to first element in the array
		const_iterator begin() const {
			return SDAL_Const_Iter(list);
		}
		// create a const iterator who's T* here points to one past last element in the array
		const_iterator end() const {
			return SDAL_Const_Iter(list + list_size);
		}
		
		// clear the list by setting every element to NULL and setting
		// head & tail = -1 and list_size to 0 and update list according to conditions
		void clear() {
			for(int i = 0; i < size(); i++) 
				list[i] = 0; // is actually "= NULL"
			head = -1;
			tail = -1;
			list_size = 0;
			update_list();
		}
		// return if list is empty or not (if head = -1)
		bool is_empty() const {
			return head == -1;
		}
		// return size of list
		size_t size() const {
			return list_size;
		}
		// check if there exists an element in the array equal to 
		// 'element' using the 'equals' method for comparison
		bool contains(const T& element, bool equals(const T& a, const T&b)) const {
			int temp = head;
			while(temp <= tail) {
				if(equals(list[temp], element))
					return true;
				temp++;
			}
			return false;
		}
		
		// update list method: if insert is called and array is full, allocate new
		// array of size 150% original. If array size>99 and list size < half of array size
		// allocate new array of size 50% original. Then copy over elements and deallocate original 
		void update_list() {
			int actual_list_size = list_size;
			int actual_array_size = array_size;
			if(tail == array_size-1) {
				T temp[(int)(array_size*1.5)];
				for(int i = 0; i < array_size; i++) {
					temp[i] = list[i];
				}
				delete list;
				list = temp;
				list_size = actual_list_size;
				head = 0;
				array_size = (int)(actual_array_size * 1.5);
			}
			
			if(array_size > 99 && list[array_size/2 + 1] == 0) {
				T temp[(int)(array_size*.5)];
				for(int i = 0; i < list_size; i++) {
					temp[i] = list[i];
				}
				delete list;
				list_size = actual_list_size;
				list = temp;
				head = 0;
				array_size = (int)(actual_array_size *.5);
			}
		}
		// return an ostream& containing a print of the list's elements
		std::ostream& print(std::ostream& out) const {
			if(is_empty()) {
				out << "<empty list>";
				out << std::endl;
			}
			else {
				int temp = head;
				out << "[" << list[temp] << "]";
				temp++;
				while(temp <= tail) {
					out << ",[" << list[temp] << "]";
					temp++;
				}
				out << std::endl;
			}	
			return out;
		}
		
		// return a reference to the T data in array at 'position'
		// throw invalid_argument exception if position is invalid
		T& operator[](int position) {
			if(position < 0 || position > list_size)
				throw std::invalid_argument("Position not in range");
			return list[position];
		}
		// return a const reference to the T data in array at 'position'
		// throw invalid_argument exception if position is invalid
		T const& operator[](int position) const {
			if(position < 0 || position > list_size)
				throw std::invalid_argument("Position not in range");
			return list[position];
		}
	}; // class SSLL
} // namespace cop3530

#endif //_SDAL_H_