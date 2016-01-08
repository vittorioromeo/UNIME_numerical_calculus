#include "nc_cpp.hpp"
#include <boost/program_options.hpp>
#include <iostream>

namespace po = boost::program_options;

int main(int ac, char** av)
{
    // Declare the supported options.
    po::options_description desc("Allowed options");
    desc.add_options() // .
        ("fn", po::value<int>(), "function index")
        ("sn", po::value<int>(), "sample number");

    po::variables_map vm;
    po::store(po::parse_command_line(ac, av, desc), vm);
    po::notify(vm);

    if(vm.count("fn"))
    {
        auto val = vm["fn"].as<int>();
        std::cout << "Selected" << val << ".\n";
    }
    else
    {
        std::cout << "Devi selezionare una delle seguenti funzioni.\n";
    }
}