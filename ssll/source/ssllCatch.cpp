#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "SSLL.h"

bool same_char( const char& a, const char& b ) { // argument for contains()
  return (a == b); 
}


TEST_CASE("ssll parameterless constructor", "Regular Constructor") {
	int a = 0;
	try { cop3530::SSLL<char> test; }
	catch (...) { a++; }
	REQUIRE(a==0);
}
TEST_CASE("ssll legal replace", "try legal replace") {
	cop3530::SSLL<int> test;
	test.insert(5,0);
	test.replace(4,0);
	REQUIRE(test[0] == 4);
}
TEST_CASE("ssll illegal replace", "try out of bounds replace") {
	int a = 0;
	cop3530::SSLL<int> test;
	test.insert(5,0);
	try { test.replace(4,5); }
	catch( const std::invalid_argument& err) { a++; }
	REQUIRE(a==1);
}
TEST_CASE("ssll legal insert", "try legal insert") {
	cop3530::SSLL<int> test;
	test.insert(5,0);
	REQUIRE(test[0] == 5);
}
TEST_CASE("ssll illegal insert", "try out of bounds insert") {
	int a = 0;
	cop3530::SSLL<int> test;
	try { test.insert(5,1); }
	catch( const std::invalid_argument& err) { a++; }
	REQUIRE(a==1);
}
TEST_CASE("ssll legal push_front", "try legal push_front") {
	cop3530::SSLL<int> test;
	test.insert(5,0);
	test.push_front(4);
	REQUIRE(test[0] == 4);
}
TEST_CASE("ssll legal push_back", "try legal push_back") {
	cop3530::SSLL<int> test;
	test.insert(5,0);
	test.push_back(4);
	REQUIRE(test[1] == 4);
}
TEST_CASE("ssll legal remove", "try legal remove") {
	cop3530::SSLL<int> test;
	test.insert(5,0);
	test.insert(4,1);
	test.remove(0);
	REQUIRE(test[0] == 4);
}
TEST_CASE("ssll illegal remove", "try out of bounds remove") {
	int a = 0;
	cop3530::SSLL<int> test;
	test.insert(5,0);
	test.insert(4,1);
	try { test.remove(-1); }
	catch( const std::invalid_argument& err) { a++; }
	REQUIRE(a==1);
}
TEST_CASE("ssll legal pop_front", "try legal pop_front") {
	cop3530::SSLL<int> test;
	test.insert(5,0);
	REQUIRE(test.pop_front() == 5);
}
TEST_CASE("ssll legal pop_back", "try legal pop_back") {
	cop3530::SSLL<int> test;
	test.insert(5,0);
	test.insert(4,1);
	REQUIRE(test.pop_back() == 4);
}
TEST_CASE("ssll legal item_at", "try legal item_at") {
	cop3530::SSLL<int> test;
	test.insert(5,0);
	test.insert(4,1);
	REQUIRE(test.item_at(1) == 4);
}
TEST_CASE("ssll illegal item_at", "try out of bounds item_at") {
	int a = 0;
	cop3530::SSLL<int> test;
	test.insert(5,0);
	test.insert(4,1);
	try { test.item_at(3); }
	catch( const std::invalid_argument& err) { a++; }
	REQUIRE(a == 1);
}
TEST_CASE("ssll is_empty", "try is_empty") {
	cop3530::SSLL<int> test;
	test.insert(5,0);
	test.insert(4,1);
	REQUIRE(test.is_empty() == false);
}
TEST_CASE("ssll clear", "try clear") {
	cop3530::SSLL<int> test;
	test.insert(5,0);
	test.insert(4,1);
	test.clear();
	REQUIRE(test.is_empty() == true);
}
TEST_CASE("ssll contains", "try contains") {
	cop3530::SSLL<char> test;
	test.insert('a',0);
	test.insert('b',1);
	REQUIRE(test.contains('a', same_char) == true);
	REQUIRE(test.contains('d', same_char) == false);
}
TEST_CASE("ssll print", "try print") {
	int a = 0;
	cop3530::SSLL<int> test;
	test.insert(5,0);
	test.insert(4,1);
	try { test.print(std::cout); }
	catch( ... ) { a++; }
	REQUIRE(a == 0);
}
TEST_CASE("ssll size", "try size") {
	cop3530::SSLL<int> test;
	test.insert(5,0);
	test.insert(4,1);
	REQUIRE(test.size() == 2);
}
TEST_CASE("ssll begin", "try begin") {
	int a = 0;
	cop3530::SSLL<int> test;
	test.insert(5,0);
	test.insert(4,1);
	try { cop3530::SSLL<int>::iterator iter = test.begin(); }
	catch( ... ) { a++; }
	REQUIRE(a == 0);
}
TEST_CASE("ssll end", "try end") {
	int a = 0;
	cop3530::SSLL<int> test;
	test.insert(5,0);
	test.insert(4,1);
	try { cop3530::SSLL<int>::iterator iter = test.end(); }
	catch( ... ) { a++; }
	REQUIRE(a == 0);
}
TEST_CASE("ssll const begin", "try const begin") {
	int a = 0;
	cop3530::SSLL<int> test;
	test.insert(5,0);
	test.insert(4,1);
	try { const cop3530::SSLL<int>::iterator iter = test.begin(); }
	catch( ... ) { a++; }
	REQUIRE(a == 0);
}
TEST_CASE("ssll const end", "try const end") {
	int a = 0;
	cop3530::SSLL<int> test;
	test.insert(5,0);
	test.insert(4,1);
	try { const cop3530::SSLL<int>::iterator iter = test.end(); }
	catch( ... ) { a++; }
	REQUIRE(a == 0);
}
TEST_CASE("ssll legal & illegal []", "try legal & illegal []") {
	int a = 0;
	cop3530::SSLL<int> test;
	test.insert(5,0);
	test.insert(4,1);
	try { test[3] = 5; }
	catch( const std::invalid_argument& err) { a++; }
	REQUIRE(a == 1);
	REQUIRE(test[0] == 5);
}
TEST_CASE("ssll const []", "try const []") {
	cop3530::SSLL<int> test;
	test.insert(5,0);
	test.insert(4,1);
	const int a = test[0];
	REQUIRE(a == 5);
}
TEST_CASE("ssll iter constructor", "Regular Constructor") {
	int a = 0;
	cop3530::SSLL<int> test;
	test.insert(5,0);
	test.insert(4,1);
	try { cop3530::SSLL<int>::SSLL_Iter i; }
	catch( ... ) { a++; }
	REQUIRE(a == 0);
}
TEST_CASE("ssll iter explicit constructor", "Explicit Constructor") {
	int a = 0;
	cop3530::SSLL<int> test;
	test.insert(5,0);
	test.insert(4,1);
	// begin uses the explicit constructor
	try { cop3530::SSLL<int>::SSLL_Iter i = test.begin(); }
	catch( ... ) { a++; }
	REQUIRE(a == 0);
}
TEST_CASE("ssll iter *", "try *") {
	cop3530::SSLL<int> test;
	test.insert(5,0);
	test.insert(4,1);
	cop3530::SSLL<int>::SSLL_Iter i = test.begin();
	REQUIRE(*i == 5);
}
TEST_CASE("ssll iter =", "try =") {
	cop3530::SSLL<int> test;
	cop3530::SSLL<int> test2;
	test.insert(5,0);
	test2.insert(4,0);
	cop3530::SSLL<int>::SSLL_Iter i = test.begin();
	cop3530::SSLL<int>::SSLL_Iter j = test2.begin();
	i = j;
	REQUIRE(*i == 4);
}
TEST_CASE("ssll iter ++", "try pre and post ++") {
	cop3530::SSLL<int> test;
	test.insert(5,0);
	test.insert(4,1);
	test.insert(4,1);
	cop3530::SSLL<int>::SSLL_Iter i = test.begin();
	i++;
	cop3530::SSLL<int>::SSLL_Iter k = ++i;
	REQUIRE(*k == 4);
}
TEST_CASE("ssll iter == and !=", "try == and !=") {
	cop3530::SSLL<int> test;
	test.insert(5,0);
	test.insert(4,1);
	cop3530::SSLL<int>::SSLL_Iter i = test.begin();
	cop3530::SSLL<int>::SSLL_Iter j = test.begin();
	REQUIRE(i == j);
	REQUIRE(!(i != j));
}
TEST_CASE("ssll const iter constructor", "Regular Constructor") {
	int a = 0;
	cop3530::SSLL<int> test;
	test.insert(5,0);
	test.insert(4,1);
	try { const cop3530::SSLL<int>::SSLL_Iter i; }
	catch( ... ) { a++; }
	REQUIRE(a == 0);
}
TEST_CASE("ssll const iter explicit constructor", "Explicit Constructor") {
	int a = 0;
	cop3530::SSLL<int> test;
	test.insert(5,0);
	test.insert(4,1);
	// begin uses the explicit constructor
	try { const cop3530::SSLL<int>::SSLL_Iter i = test.begin(); }
	catch( ... ) { a++; }
	REQUIRE(a == 0);
}
TEST_CASE("ssll const iter *", "try *") {
	cop3530::SSLL<int> test;
	test.insert(5,0);
	test.insert(4,1);
	const cop3530::SSLL<int>::SSLL_Iter i = test.begin();
	REQUIRE(*i == 5);
} /*
TEST_CASE("ssll const iter =", "try =") {
	cop3530::SSLL<int> test;
	cop3530::SSLL<int> test2;
	test.insert(5,0);
	test2.insert(4,0);
	const cop3530::SSLL<int>::SSLL_Iter i = test.begin();
	const cop3530::SSLL<int>::SSLL_Iter j = test2.begin();
	i = j;
	REQUIRE(*i == 4);
} 
TEST_CASE("ssll const iter ++", "try pre and post ++") {
	cop3530::SSLL<int> test;
	test.insert(5,0);
	test.insert(4,1);
	test.insert(4,1);
	const cop3530::SSLL<int>::SSLL_Iter i = test.begin();
	i++;
	const cop3530::SSLL<int>::SSLL_Iter k = ++i;
	REQUIRE(*k == 4);
} */
TEST_CASE("ssll const iter == and !=", "try == and !=") {
	cop3530::SSLL<int> test;
	test.insert(5,0);
	test.insert(4,1);
	const cop3530::SSLL<int>::SSLL_Iter i = test.begin();
	const cop3530::SSLL<int>::SSLL_Iter j = test.begin();
	REQUIRE(i == j);
	REQUIRE(!(i != j));
}