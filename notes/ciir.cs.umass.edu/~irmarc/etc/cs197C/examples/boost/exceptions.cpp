// Example taken from: 
// http://www.boost.org/doc/libs/1_46_0/libs/exception/doc/tutorial_transporting_data.html

#include <boost/exception/all.hpp>
#include <iostream>

typedef boost::error_info<struct tag_my_info,int> my_info; //(1)

struct my_error: virtual boost::exception, virtual std::exception { }; //(2)

void iWillNeverWork() {
  throw my_error() << my_info(42); //(3)
}

int main(int argc, char *argv[]) {
  try {
    iWillNeverWork();
  } catch(my_error & x ) {
    if( int const * mi=boost::get_error_info<my_info>(x) )
      std::cerr << "My info: " << *mi << std::endl;
  }
}
