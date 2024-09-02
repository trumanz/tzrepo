//
// Created by zck on 2024/9/1.
//

#ifndef DATAEVENT_H
#define DATAEVENT_H

#include <pqxx/pqxx>
#include <iostream>


class DataEvent {

};

class TickByTickBidAskData : public DataEvent {
public:
    time_t time;
    double bid_price;
    double ask_price;
    double bid_size;
    double ask_size;

    void insert_to_db() {
        try {
            // Establish a connection to the database
            pqxx::connection C("dbname=qa user=qa password=qa hostaddr=192.168.1.201 port=5432");
            if (C.is_open()) {
                std::cout << "Opened database successfully: " << C.dbname() << std::endl;
            } else {
                std::cerr << "Can't open database" << std::endl;
                return;
            }

            // Start a transaction block
            pqxx::work W(C);

            // Prepare SQL statement
            std::string sql = "INSERT INTO bid_ask_data (time, bid_price, ask_price, bid_size, ask_size) "
                              "VALUES ($1, $2, $3, $4, $5);";

            // Execute SQL query with parameters
            W.exec_params(sql,
                          this->time,
                          this->bid_price,
                          this->ask_price,
                          this->bid_size,
                          this->ask_size);

            // Commit the transaction
            W.commit();
            std::cout << "Record inserted successfully" << std::endl;

        } catch (const std::exception &e) {
            std::cerr << e.what() << std::endl;
        }
    }
};



#endif //DATAEVENT_H
