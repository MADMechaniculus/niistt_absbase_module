#ifndef ABSTRACTGETPROC_H
#define ABSTRACTGETPROC_H

#include "proctypes.h"

/**
 * @brief Абстракция процессора GET запросов
 */
template <class CTRL>
class AbstractGETProc {
    CTRL * appPtr{nullptr};
public:
    AbstractGETProc() {};
    virtual processorProcRet_t process(std::string target, std::string rootPath, http::file_body::value_type & ansBody) = 0;
    void connect(CTRL * ptr) {
        this->appPtr = ptr;
    }
};

#endif // ABSTRACTGETPROC_H
