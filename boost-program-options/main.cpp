#include <boost/program_options.hpp>
#include <iostream>
#include <map>

namespace bpo = boost::program_options;

enum class CustomType {
  foo,
  bar
};

void validate(boost::any& v,
              const std::vector<std::string>& values,
              CustomType* /*target_type*/, int)
{
  // Make sure no previous assignment to 'v' was made.
  bpo::validators::check_first_occurrence(v);

  const std::string& s = bpo::validators::get_single_string(values);

  if (s == "foo")
    v = boost::any(CustomType::foo);
  else if (s == "bar")
    v = boost::any(CustomType::bar);
  else
    throw bpo::invalid_option_value(s);
}

int main(int argc, char** argv)
{
  bpo::options_description desc("Command line parameters");

  desc.add_options()
    ("help,h", "Produce help message.")
    ("foobar", bpo::value<CustomType>(), "Custom type argument (foo, bar).")
    ("positionals", bpo::value<std::vector<std::string>>()->multitoken(), "Some positional argument.")
    ;

  bpo::positional_options_description p;
  p.add("positionals", -1);

  bpo::variables_map vm;

  try {
    bpo::store(bpo::command_line_parser(argc, argv).options(desc).positional(p).run(), vm);

    if (vm.count("help")) {
      std::cout << "Usage: " << argv[0] << " [options]" << std::endl;
      std::cout << desc;
      return 0;
    }

    bpo::notify(vm);
  } catch(bpo::error &err) {
    std::cerr << err.what() << std::endl;
    return -1;
  }

  if (vm.count("positionals") > 0) {
    const auto positionals = vm["positionals"].as<std::vector<std::string>>();
    std::cout << "Received " << positionals.size() << " positionals arguments: ";
    for(const auto& p : positionals) 
      std::cout << p << ' ';
    std::cout << std::endl;
  }

  if (vm.count("foobar") > 0) {
    std::map<CustomType, std::string> custom_str = {{CustomType::foo, "Foo"}, {CustomType::bar, "Bar"}};
    std::cout << "Custom arg is: " << custom_str[vm["foobar"].as<CustomType>()] << std::endl;
  }

  return 0;
}
