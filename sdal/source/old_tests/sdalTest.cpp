#include <iostream>
#include "SDAL.h"

bool same_char( const char& a, const char& b ) { // argument for contains()
  return (a == b); 
}

void in_list( const cop3530::SDAL<char>& list, char c, std::ostream& out ) {
  out << c << " is " << (list.contains( c, same_char ) ? "" : "not ")
	    << "in the list ";
  list.print( out );
  out << std::endl;
}

int main() {

cop3530::SDAL<char> m;
  
  cop3530::SDAL<char> l;

  l.print( std::cout ); 
  std::cout << std::endl;
  l.insert( 'x', 0 );
  l.print( std::cout ); 
  std::cout << std::endl;
  l.insert( 'Y', 0 );
  l.print( std::cout ); std::cout << std::endl;
  
  m.push_front('a');
  m.push_back('b');
  m.print( std::cout );
  m.insert('b', 1);
  m.print( std::cout );
  m.replace('c', 2);
  m.print( std::cout );
  std::cout <<std::endl;
  m.print( std::cout ); 	
  std::cout <<m.pop_back();
  std::cout <<std::endl;
  m.print(std::cout);
  
  
  return 0;
}