#ifndef TELEMETRYFLOW_H
#define TELEMETRYFLOW_H

#include "niistt_base_module_global.h"
#include "telemetrytypes.h"

class NIISTT_BASE_MODULE_EXPORT TelemetryFlow
{
    std::queue<TelemetryMessage> msgQueue;
    boost::mutex queueMx;

    boost::atomic<bool> empty{true};

public:
    TelemetryFlow();

    bool isEmpty(void) const;

    /**
     * @brief Забираем первое в очереди сообщение
     * @return Экземпляр сообщения
     */
    TelemetryMessage dequeue(void);

    /**
     * @brief Добавление записи в поток телеметрии
     * @param msg Ссылка на экземпляр записи
     */
    void enqueue(TelemetryMessage & msg);

    /**
     * @brief Добавление записи в поток телеметрии
     * @param msg Rvalue экземпляр записи
     */
    void enqueue(TelemetryMessage && msg);
};

#endif // TELEMETRYFLOW_H
