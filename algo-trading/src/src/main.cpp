/* Copyright (C) 2019 Interactive Brokers LLC. All rights reserved. This code is subject to the terms
* and conditions of the IB API Non-Commercial License or the IB API Commercial License, as applicable. */

#include "StdAfx.h"

#include <stdio.h>
#include <stdlib.h>

#include <chrono>
#include <thread>

#include "TestCppClient.h"

const unsigned MAX_ATTEMPTS = 50;
const unsigned SLEEP_TIME = 10;
#include "IBClient.h"
#include "log.h"





/* IMPORTANT: always use your paper trading account. The code below will submit orders as part of the demonstration. */
/* IB will not be responsible for accidental executions on your live account. */
/* Any stock or option symbols displayed are for illustrative purposes only and are not intended to portray a recommendation. */
/* Before contacting our API support team please refer to the available documentation. */
int main(int argc, char** argv)
{
    //const char* host = argc > 1 ? argv[1] : "";
    //int port = argc > 2 ? atoi(argv[2]) : 0;
    //if (port <= 0)
    //    port = 7497;

    std::vector< std::tuple<const char*, int> > ib_api_servers;
    ib_api_servers.emplace_back("192.168.1.201", 7497); //remote paper, win,
    ib_api_servers.emplace_back("*", 7497); //local paper

    init_logging();

    const char* connectOptions = argc > 3 ? argv[3] : "";
    int clientId = 0;

    for (unsigned attempt = 0; attempt < MAX_ATTEMPTS; attempt++) {
        printf( "Attempt %u of %u\n", attempt, MAX_ATTEMPTS);

        auto api_server = ib_api_servers[attempt % ib_api_servers.size()];
        const char* host = std::get<0>(api_server);
        int port = std::get<1>(api_server);
        IBClient client(host, port, clientId);

        if( connectOptions) {
            client.setConnectOptions( connectOptions);
        }

        client.connect();
        client.requestBTCMktData();
        uint64_t i = 0;
        while( client.isConnected()) {
            printf("loop %llu\n", i++);
            client.processMessages();
        }

        printf( "Sleeping %u seconds before next attempt\n", SLEEP_TIME);
        std::this_thread::sleep_for(std::chrono::seconds(SLEEP_TIME));
    }

    printf ( "End of C++ Socket Client Test\n");
}

