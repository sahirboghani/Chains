#include <iostream>
#include "CDAL.h"

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

  cop3530::CDAL<char> l;

  l.print( std::cout ); 
  std::cout << std::endl;
  l.insert( 'x', 0 );
  l.print( std::cout ); 
  std::cout << std::endl;
  l.insert( 'Y', 0 );
  std::cout << "test1";
  l.clear();
  l.print( std::cout ); 
  
  
  return 0;
}