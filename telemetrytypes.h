#ifndef TELEMETRYTYPES_H
#define TELEMETRYTYPES_H

#include <cstdint>
#include <string>
#include <queue>
#include <sstream>
#include <string>

#include <boost/date_time.hpp>
#include <boost/thread.hpp>
#include <boost/atomic.hpp>

class TelemetryMessage {

    boost::posix_time::ptime timeStamp;
    std::string msg{""};

    /**
     * @brief Закрытый конструктор для обеспечения однозначности формирования timestamp
     * @param timestamp Временная метка
     * @param message Сообщение
     */
    TelemetryMessage(boost::posix_time::ptime timestamp, \
                     std::string message);

public:
    /**
     * @brief Конструктор копирования
     * @param msg Экземпляр из которого будет произведено копирование
     */
    TelemetryMessage(const TelemetryMessage & msg);

    /**
     * @brief Создание телеметрической записи без возможности указания собственного времени
     * @param msg Сообщение, которое содержит запись
     * @return Экземпляр телеметрической записи
     */
    static TelemetryMessage createMessage(std::string msg);

    /**
     * @brief Преобразование в строку
     * @return Строка сообщения с временной меткой
     */
    std::string stringify(void);
};

#endif // TELEMETRYTYPES_H
