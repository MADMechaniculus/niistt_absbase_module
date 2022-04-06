#ifndef TELEMETRYTYPES_H
#define TELEMETRYTYPES_H

#include "niistt_base_module_global.h"

#include <cstdint>
#include <string>
#include <queue>
#include <sstream>

#include <boost/date_time.hpp>
#include <boost/thread.hpp>

class NIISTT_BASE_MODULE_EXPORT TelemetryMessage {

    boost::posix_time::ptime timeStamp;
    std::string msg;

    TelemetryMessage(boost::posix_time::ptime timestamp, std::string message) : \
        timeStamp(timestamp), msg(message) {}

public:

    TelemetryMessage(const TelemetryMessage & msg) {
        this->msg = msg.msg;
        this->timeStamp = msg.timeStamp;
    }

    /**
     * @brief Создание телеметрической записи без возможности указания собственного времени
     * @param msg Сообщение, которое содержит запись
     * @return Экземпляр телеметрической записи
     */
    static TelemetryMessage createMessage(std::string msg) {
        return TelemetryMessage(boost::posix_time::second_clock::local_time(), msg);
    }

    std::string serialize(void) {
        std::ostringstream time;
        time << this->timeStamp;
        std::string ret = "[" + time.str() + "] -> " + this->msg;
        return ret;
    }
};

#endif // TELEMETRYTYPES_H
