#include "ws/requests/Requests.hpp"
#include "ws/requests/RequestsBuilder.hpp"
#include "ws/requests/RequestsHelper.hpp"

namespace BNB
{
    namespace WS
    {
        namespace Account
        {
            class Information : public IRequest
            {
            public:
                Information();
                std::string dump() const override;
            };

        }
        
    }
}
    
    // class Account
    // {
    // public:
    //     static request information();
    //     static request unfilledOrderCount();
    //     static request orderHistory();
    //     static request allOrderHistory();
    //     static request tradeHistory();
    //     static request preventedMatches();
    //     static request allocations();
    //     static request commissionRates();
    // };

