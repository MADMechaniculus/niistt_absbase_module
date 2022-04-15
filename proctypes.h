#ifndef PROCTYPES_H
#define PROCTYPES_H

#include <string>
#include <boost/beast.hpp>

namespace http = boost::beast::http;

typedef std::pair<bool, std::string> processorProcRet_t;

#endif // PROCTYPES_H
