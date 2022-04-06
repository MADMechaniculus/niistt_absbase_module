#ifndef ABSTRACTBASEMODULE_H
#define ABSTRACTBASEMODULE_H

#include "niistt_base_module_global.h"

#include "typeimpls.h"
#include "telemetryflow.h"

class NIISTT_BASE_MODULE_EXPORT AbstractBaseModule
{
protected:
    std::queue<taskPh_t> taskQueue;
    std::mutex queueMx;
    std::atomic<bool> stopFlag{false};

    /**
     * @brief Указатель на телеметрический поток, куда будет скидываться вся телеметрия модуля
     */
    TelemetryFlow * tlmFlow{nullptr};

    /**
     * @brief Обработка запросов в очереди запросов приложения
     */
    void processQueue(int err);

public:
    AbstractBaseModule();

    virtual int init() = 0;
    virtual int start() = 0;
    virtual int deinit() = 0;

    /**
     * @brief Прерывание работы модуля
     */
    void stop();

    /**
     * @brief Проверка состояния модуля
     * @return True - остановлен, false - нет
     */
    bool isStoped(void) const;

    /**
     * @brief Добавление задачи для приложения в очередь задач
     * @param func Задача для приложения
     * @return Future на результат выполнения задачи
     */
    std::future<void> pushTask(std::function<void()> &&func);

    /**
     * @brief Связыание модуля с потоком телеметрии
     * @param ptr Указатель на поток телеметрии
     */
    void connectTlmFlow(TelemetryFlow * ptr);

};

#endif // ABSTRACTBASEMODULE_H
