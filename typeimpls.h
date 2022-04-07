#ifndef TYPEIMPLS_H
#define TYPEIMPLS_H

#include <boost/function.hpp>

#include <future>
#include <functional>
#include <queue>
#include <string>

/**
 * @brief Тип задания для модуля
 */
typedef std::pair<std::promise<void>, boost::function<void()>> taskPh_t;

#endif // TYPEIMPLS_H
