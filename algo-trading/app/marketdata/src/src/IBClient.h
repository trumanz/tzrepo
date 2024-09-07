//
// Created by zck on 2024/9/1.
//

#ifndef IBCLIENT_H
#define IBCLIENT_H

#include "EWrapper.h"
#include "EReaderOSSignal.h"
#include "EReader.h"

#include <memory>
#include <vector>

#include "TestCppClient.h"

class EClientSocket;


#include "log.h"

#include "event/DataEvent.h"

//! [ewrapperimpl]
class IBClient : protected TestCppClient
{
private:
	std::string api_host;
	int api_port;
	int client_id;
public:
	IBClient(const std::string api_host, const int api_port, const int client_id);
	void setConnectOptions(const std::string& opt){TestCppClient::setConnectOptions(opt);}
	bool connect();
	bool isConnected()const { return TestCppClient::isConnected();}
	void processMessages() { TestCppClient::processMessages();}
	void requestBTCMktData();
protected:
	void tickByTickBidAsk(int reqId, time_t time, double bidPrice, double askPrice, Decimal bidSize, Decimal askSize, const TickAttribBidAsk& tickAttribBidAsk) override;
	void tickSize( TickerId tickerId, TickType field, Decimal size) override;

};



#endif //IBCLIENT_H
