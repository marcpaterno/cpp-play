#include "type_name.hh"

#include <fplus/fplus.hpp>

#include <iostream>
#include <string>

int
main()
{
  std::string team = "Our team is great. I love everybody I work with.";
  std::cout << "There actually are this many 'I's in team: "
            << fplus::count("I", fplus::split_words(false, team)) << '\n';

  std::cout << "Type of std::string is: " << type_name<std::string>() << '\n';
}
