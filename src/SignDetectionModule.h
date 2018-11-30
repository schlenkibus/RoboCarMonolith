#pragma once


class SignDetectionModule {
public:
    enum class Object {
        Stop = 1, Block = 2, None = 0
    };
    SignDetectionModule() = default;
    Object getPrediction();
};