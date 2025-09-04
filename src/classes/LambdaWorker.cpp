#include "LambdaWorker.h"

LambdaWorker::LambdaWorker(std::function<void()> func) : func(func) {
    setAutoDelete(true);
}

void LambdaWorker::run() {
    func();
}