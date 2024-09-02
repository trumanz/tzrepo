/* Copyright (C) 2019 Interactive Brokers LLC. All rights reserved. This code is subject to the terms
 * and conditions of the IB API Non-Commercial License or the IB API Commercial License, as applicable. */

#include "StdAfx.h"

#include "IBClient.h"

#include "EClientSocket.h"
#include "EPosixClientSocketPlatform.h"

#include "Contract.h"
#include "Order.h"
#include "OrderState.h"
#include "Execution.h"
#include "CommissionReport.h"
#include "ContractSamples.h"
#include "OrderSamples.h"
#include "ScannerSubscription.h"
#include "ScannerSubscriptionSamples.h"
#include "executioncondition.h"
#include "PriceCondition.h"
#include "MarginCondition.h"
#include "PercentChangeCondition.h"
#include "TimeCondition.h"
#include "VolumeCondition.h"
#include "AvailableAlgoParams.h"
#include "FAMethodSamples.h"
#include "CommonDefs.h"
#include "AccountSummaryTags.h"
#include "Utils.h"

#include <stdio.h>
#include <chrono>
#include <iostream>
#include <thread>
#include <ctime>
#include <fstream>
#include <cstdint>


const int PING_DEADLINE = 2; // seconds
const int SLEEP_BETWEEN_PINGS = 30; // seconds

///////////////////////////////////////////////////////////
// member funcs
//! [socket_init]
IBClient::IBClient(const std::string _api_host, const int _api_port, const int _client_id) :
      api_host(_api_host), api_port(_api_port), client_id(_client_id)
{
}


bool IBClient::connect()
{
	auto host = this->api_host.c_str();
	auto port = this->api_port;
	auto clientId = this->client_id;
	return this->TestCppClient::connect(host, port, clientId);
}


void IBClient::requestBTCMktData()
{

	Contract contract;
    contract.symbol = "BTC";
    contract.secType = "CRYPTO"; // "CRYPTO" for cryptocurrencies
    contract.exchange = "PAXOS"; // or "COINBASE", "KRAKEN", etc.
    contract.currency = "USD";   // Assuming you're interested in BTC/USD

	TickerId id = 2001;
	std::string genericTicks = "";
    bool snapshot = false;
	bool regulatorySnaphsot = false;
    m_pClient->reqMktData(id, contract, genericTicks, snapshot, regulatorySnaphsot, TagValueListSPtr());
    m_pClient->reqTickByTickData(20003, contract, "BidAsk", 0, false);

}

//! [tickbytickbidask]
void IBClient::tickByTickBidAsk(int reqId, time_t time, double bidPrice, double askPrice, Decimal bidSize, Decimal askSize, const TickAttribBidAsk& tickAttribBidAsk) {
    LOG_INFO("Tick-By-Tick. ReqId: %d, TickType: BidAsk, Time: %s, BidPrice: %s, AskPrice: %s, BidSize: %s, AskSize: %s, BidPastLow: %d, AskPastHigh: %d",
        reqId, ctime(&time), Utils::doubleMaxString(bidPrice).c_str(), Utils::doubleMaxString(askPrice).c_str(),
           decimalStringToDisplay(bidSize).c_str(), decimalStringToDisplay(askSize).c_str(), tickAttribBidAsk.bidPastLow, tickAttribBidAsk.askPastHigh);

	TickByTickBidAskData data;
	data.time = time;
	data.bid_price = bidPrice;
	data.ask_price = askPrice;
	data.ask_size = __bid64_to_binary64(askSize,0, nullptr);
	data.bid_size = __bid64_to_binary64(bidSize,0, nullptr);;
	data.insert_to_db();
	BOOST_LOG_TRIVIAL(info) << "This is an info message";
}
//! [tickbytickbidask]
