#include <iostream>
#include "PSLL.h"

bool same_char( const char& a, const char& b ) { // argument for contains()
  return (a == b); 
}

void in_list( const cop3530::PSLL<char>& list, char c, std::ostream& out ) {
  out << c << " is " << (list.contains( c, same_char ) ? "" : "not ")
	    << "in the list ";
  list.print( out );
  out << std::endl;
}

int main() {

cop3530::PSLL<char> l;
  l.print(std::cout);
  l.insert('x',0);
  std::cout << std::endl;
  l.print(std::cout);
  l.push_back('y');
  std::cout << std::endl;
  l.print(std::cout);
  std::cout << std::endl;
  std::cout << l.item_at(0);
  std::cout << l.item_at(1);
  std::cout << std::endl;
  l.print(std::cout);
  std::cout << l.size();
  
  l.print( std::cout ); 
  std::cout << std::endl;
  l.insert( 'x', 0 );
  l.print( std::cout ); 
  std::cout << std::endl;
  l.insert( 'Y', 0 );
  l.print( std::cout ); std::cout << std::endl;

  
  in_list( l, 'X', std::cout );
  in_list( l, 'Y', std::cout );
  in_list( l, 'x', std::cout );
  in_list( l, 'X', std::cout );
  
  
  return 0;
}