#include <boost/python.hpp>
#include <boost/python/list.hpp>
#include <boost/python/extract.hpp>
#include <string>
#include <sstream>
#include <vector>
#include "../../number_converter.h"

struct World
{
    std::string set(std::string msg) { 
        int result = proccessNumber((char*) msg.c_str());
        // char * a = decimal_to_roman(13);
        mMsg = msg; 
        return std::to_string(result);
    }
    int romanToDecimal(std::string msg) { 
        int result = proccessNumber((char*) msg.c_str());
        return result;
    }
    std::string decimalToRoman(int num) { 
        char * a = decimal_to_roman(num);
        return a;
    }

    void many(boost::python::list msgs) {
        long l = len(msgs);
        std::stringstream ss;
        for (long i = 0; i<l; ++i) {
            if (i>0) ss << ", ";
            std::string s = boost::python::extract<std::string>(msgs[i]);
            ss << s;
        }
        mMsg = ss.str();
    }
    std::string greet() { 
        return mMsg; 
    }
    std::string mMsg;
};

using namespace boost::python;

BOOST_PYTHON_MODULE(classes)
{
    class_<World>("World")
        .def("greet", &World::greet)
        .def("set", &World::set)
        .def("decimalToRoman", &World::decimalToRoman)
        .def("romanToDecimal", &World::romanToDecimal)
        .def("many", &World::many)
    ;
};

