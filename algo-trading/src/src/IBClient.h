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





//! [ewrapperimpl]
class IBClient : public EWrapper
{
private:
	std::string api_host;
	int api_port;
	int client_id;
public:
	IBClient(const std::string api_host, const int api_port, const int client_id);
	bool connect();
	void requestBTCMktData();


//below code from example
//! [ewrapperimpl]
public:
	~IBClient();

	void setConnectOptions(const std::string&);
	void processMessages();

public:

	void disconnect() const;
	bool isConnected() const;
private:
    void pnlOperation();
    void pnlSingleOperation();
	void tickDataOperation();
	void tickOptionComputationOperation();
	void delayedTickDataOperation();
	void marketDepthOperations();
	void realTimeBars();
	void marketDataType();
	void historicalDataRequests();
	void optionsOperations();
	void accountOperations();
	void orderOperations();
	void ocaSamples();
	void conditionSamples();
	void bracketSample();
	void hedgeSample();
	void contractOperations();
	void marketScanners();
	void fundamentals();
	void bulletins();
	void testAlgoSamples();
	void financialAdvisorOrderSamples();
	void financialAdvisorOperations();
	void testDisplayGroups();
	void miscelaneous();
	void reqFamilyCodes();
	void reqMatchingSymbols();
	void reqMktDepthExchanges();
	void reqNewsTicks();
	void reqSmartComponents();
	void reqNewsProviders();
	void reqNewsArticle();
	void reqHistoricalNews();
	void reqHeadTimestamp();
	void reqHistogramData();
	void rerouteCFDOperations();
	void marketRuleOperations();
	void continuousFuturesOperations();
    void reqHistoricalTicks();
    void reqTickByTickData();
	void whatIfSamples();
	void ibkratsSample();
	void wshCalendarOperations();

	void reqCurrentTime();

public:
	// events
	#include "EWrapper_prototypes.h"


private:
	void printContractMsg(const Contract& contract);
	void printContractDetailsMsg(const ContractDetails& contractDetails);
	void printContractDetailsSecIdList(const TagValueListSPtr &secIdList);
	void printBondContractDetailsMsg(const ContractDetails& contractDetails);

private:
	//! [socket_declare]
	EReaderOSSignal m_osSignal;
	EClientSocket * const m_pClient;
	//! [socket_declare]
	State m_state;
	time_t m_sleepDeadline;

	OrderId m_orderId;
	std::unique_ptr<EReader> m_pReader;
    bool m_extraAuth;
	std::string m_bboExchange;
};



#endif //IBCLIENT_H
