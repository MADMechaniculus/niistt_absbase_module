#ifndef ABSTRACTPOSTPROC_H
#define ABSTRACTPOSTPROC_H

#include "proctypes.h"

/**
 * @brief Абстракция процессора POST запросов
 */
template <class CTRL>
class AbstractPOSTProc {
protected:
    CTRL * appPtr{nullptr};
public:
    AbstractPOSTProc() {};
    virtual processorProcRet_t process(std::string target, http::string_body::value_type & ansBody) = 0;

    void connect(CTRL * ptr) {
        this->appPtr = ptr;
    }
};

#endif // ABSTRACTPOSTPROC_H
