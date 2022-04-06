#ifndef TELEMETRYFLOW_H
#define TELEMETRYFLOW_H

#include "niistt_base_module_global.h"
#include "telemetrytypes.h"

class NIISTT_BASE_MODULE_EXPORT TelemetryFlow
{
    std::queue<TelemetryMessage> msgQueue;
    boost::mutex queueMx;

    boost::atomic<bool> empty;

public:
    TelemetryFlow();

    bool isEmpty(void) const {
        return empty;
    }

    /**
     * @brief Забираем первое в очереди сообщение
     * @return Экземпляр сообщения
     */
    TelemetryMessage dequeue(void) {
        boost::lock_guard<boost::mutex>(this->queueMx);
        if (empty)
            throw std::runtime_error("Flow queue is empty");
        TelemetryMessage msg(this->msgQueue.front());
        this->msgQueue.pop();
        empty.store(this->msgQueue.empty());
        return msg;
    }

    void enqueue(TelemetryMessage & msg) {
        boost::lock_guard<boost::mutex>(this->queueMx);
        this->msgQueue.emplace(msg);
        empty.store(this->msgQueue.empty());
    }

    void enqueue(TelemetryMessage && msg) {
        boost::lock_guard<boost::mutex>(this->queueMx);
        this->msgQueue.emplace(std::move(msg));
        empty.store(this->msgQueue.empty());
    }
};

#endif // TELEMETRYFLOW_H
