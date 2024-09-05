//
// Created by zck on 2024/9/5.
//

#ifndef STAGE_H
#define STAGE_H

#include <iostream>


class Stage {

    enum class StageEnum {
        Dev,
        QA,
        Prod
    };
private:
    // Private constructor to prevent instantiation
    Stage() {
        std::cout << "Singleton instance Stage created" << std::endl;
    }

    // Delete copy constructor and assignment operator to prevent copying
    Stage(const Stage&) = delete;
    Stage& operator=(const Stage&) = delete;

public:
    // Static method that returns the single instance of the class
    static Stage& getInstance() {
        static Stage instance;  // Guaranteed to be created once and lazily instantiated
        return instance;
    }

    // Example method to demonstrate functionality
    void doSomething() {
        std::cout << "Doing something with Singleton instance" << std::endl;
    }
};


#endif //STAGE_H
