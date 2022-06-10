
#include "date.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <cstdint>
#include <ratio>
#include <limits>
#include <type_traits>
#include "rclock.hpp"

int main(){

	using namespace date;
	using namespace std;
	namespace ch = std::chrono;
	constexpr static int start = 0;

	std::cout <<"\n\n";
	auto tp_d = impl::clock_t::now(); std::cout << "double un-init: " << tp_d <<"\n";
	auto tp_f = impl::clock_t::now(); std::cout  << "float  un-init: " << tp_f <<"\n";
	auto tp_l = impl::clock_t::now(); std::cout   << "long   un-init: " << tp_l <<"\n";

	std::istringstream in{"2000-01-01 12:34:56.1234567891"};

	//in >> date::parse("%F %T", tp_d ); std::cout <<"double    init: " << tp_d <<"\n"; in.seekg( start );
	//in >> date::parse("%F %T", tp_f ); std::cout <<"float     init: " << tp_f <<"\n"; in.seekg( start );
	//in >> date::parse("%F %T", tp_l ); std::cout <<"long      init: " << tp_l <<"\n"; in.seekg( start );
	std::cout<<"\n rounding of double: \n";
	std::cout << date::floor<days>( tp_d ) << "\n";
	std::cout << date::floor<ch::hours>( tp_d ) << "\n";
	std::cout << date::floor<ch::minutes>( tp_d ) << "\n";
	std::cout << date::floor<ch::seconds>( tp_d ) << "\n";
	std::cout << date::floor<ch::milliseconds>( tp_d ) << "\n";
	std::cout << date::floor<ch::microseconds>( tp_d ) << "\n";

	std::cout<<"\n rounding of float: \n";
	std::cout << date::floor<days>( tp_f ) << "\n";
	std::cout << date::floor<ch::hours>( tp_f ) << "\n";
	std::cout << date::floor<ch::minutes>( tp_f ) << "\n";
	std::cout << date::floor<ch::seconds>( tp_f ) << "\n";
	std::cout << date::floor<ch::milliseconds>( tp_f ) << "\n";
	std::cout << date::floor<ch::microseconds>( tp_f ) << "\n";

	std::cout<<"\n rounding of long: \n";
	std::cout << date::floor<days>( tp_l ) << "\n";
	std::cout << date::floor<ch::hours>( tp_l ) << "\n";
	std::cout << date::floor<ch::minutes>( tp_l ) << "\n";
	std::cout << date::floor<ch::seconds>( tp_l ) << "\n";
	std::cout << date::floor<ch::milliseconds>( tp_l ) << "\n";
	std::cout << date::floor<ch::microseconds>( tp_l ) << "\n";
}
