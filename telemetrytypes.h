#ifndef TELEMETRYTYPES_H
#define TELEMETRYTYPES_H

#include "niistt_base_module_global.h"

#include <cstdint>
#include <string>
#include <queue>
#include <sstream>
#include <string>

#include <boost/date_time.hpp>
#include <boost/thread.hpp>
#include <boost/atomic.hpp>

class NIISTT_BASE_MODULE_EXPORT TelemetryMessage {

    boost::posix_time::ptime timeStamp;
    std::string msg{""};

    TelemetryMessage(boost::posix_time::ptime timestamp, std::string message);

public:

    TelemetryMessage(const TelemetryMessage & msg);

    /**
     * @brief Создание телеметрической записи без возможности указания собственного времени
     * @param msg Сообщение, которое содержит запись
     * @return Экземпляр телеметрической записи
     */
    static TelemetryMessage createMessage(std::string msg);

    std::string serialize(void);
};

#endif // TELEMETRYTYPES_H
