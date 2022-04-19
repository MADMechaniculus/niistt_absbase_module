#ifndef TELEMETRYFLOW_H
#define TELEMETRYFLOW_H

#include "telemetrytypes.h"

/**
 * @brief Класс реализующий телеметрический поток сообщений
 */
class TelemetryFlow
{
protected:
    /**
     * @brief Очередь сообщений потока телеметрии
     */
    std::queue<TelemetryMessage> msgQueue;

    /**
     * @brief Мьютекс очереди сообщений
     */
    boost::mutex queueMx;

    /**
     * @brief Флаг присутствия данных в очереди сообщений
     */
    boost::atomic<bool> empty{true};

public:
    /**
     * @brief Конструктор телеметрического потока
     */
    TelemetryFlow();

    /**
     * @brief ПОлучение состояния очереди
     * @return True - пусто, false - данные наличествуют
     */
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
