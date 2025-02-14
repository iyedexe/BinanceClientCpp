#pragma once
#include <string>
#include <set>
#include "ws/WebSocketListener.hpp"
#include "ws/requests/IRequests.hpp"

namespace BNB
{
    namespace WS
    {
        using RequestId = std::string;
        class ApiClient: public WebSocketListener
        {
        public:
            ApiClient(const std::string& wsEndpoint);
            virtual ~ApiClient();

            void start();
            void stop();

            // response is request IDs
            RequestId sendRequest(const IRequest& request)
            {
                writeWS(request.dump());
                RequestId requestId = request.getId();
                pendingRequests_.insert(requestId);
                return requestId;
            }
            nlohmann::json getResponseForId(const RequestId& id);
            nlohmann::json getLastUpdate();

            
        protected:
            void onMessage(websocketpp::connection_hdl hdl, websocketpp::client<websocketpp::config::asio_client>::message_ptr msg) override;
            void onClose(websocketpp::connection_hdl hdl);
            void onFail(websocketpp::connection_hdl hdl);

        private:
            std::set<RequestId> pendingRequests_;
            std::string wsEndpoint_;  

            std::queue<nlohmann::json> updateQueue_;
            std::mutex updateMutex_;
            std::condition_variable updateCond_;

            std::map<RequestId, nlohmann::json> requestResponses_;
            std::mutex responseMutex_;
            std::condition_variable responseCond_;

        };

    }
}
