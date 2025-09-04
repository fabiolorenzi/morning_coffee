#pragma once

#include <QObject>
#include <QRunnable>
#include <functional>

class LambdaWorker : public QObject, public QRunnable {
    Q_OBJECT
    
    public:
        explicit LambdaWorker(std::function<void()> func);
        void run() override;

    private:
        std::function<void()> func;
};