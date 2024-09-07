//
// Created by zck on 2024/9/5.
//

#ifndef STAGE_H
#define STAGE_H

#include <iostream>

class Stage {
public:
    enum class StageEnum {
        Dev,
        QA,
        PROD
    };
    StageEnum satge_value = Dev;
    static Stage& getInstance() {
        static Stage instance;
        return instance;
    }

    StageEnum stage() {
    }

private:
    // Private constructor to prevent instantiation
    Stage() {
        std::cout << "Singleton instance Stage created" << std::endl;
        const char* stage_env = std::getenv("ALGO_TRADING_STAGE");
        if(stage_env == nullptr) {
            return;
        }
        if(std::string("QA") == stage_env) {
             this->satge_value = QA;
        } else if (std::string("PROD") == stage_env) {
            this->satge_value = PROD;
        }
    }
    Stage(const Stage&) = delete;
    Stage& operator=(const Stage&) = delete;

};


#endif //STAGE_H
