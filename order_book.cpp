#include<bits/stdc++.h>
using namespace std;

class Order {
    long long OrderId;
    long long Price;
    long long quantity;
    string type;
    public:
    Order()
    {
        cout<<"Enter OrderId,Price,quantity,type\n";

        cin>>OrderId;
        cin>>Price;
        cin>>quantity;
        cin>>type;
    }
        long long getOrderId() { return OrderId; }
        long long getPrice() { return Price; }
        long long getQuantity() { return quantity; }
        string getType() { return type; }
};

//existing PlaceOrder, UpdateOrder, CancelOrder classes

class OrderBook {
    //existing trades, buy, sell maps
    map<long long ,pair<long long,long long>,greater<long long>>buy;
    map<long long ,pair<long long,long long>,less<long long>>sell;

    public:
        void addOrder(Order order) {
            if (order.getType() == "buy") {
                // Add to buy map
                buy[order.getPrice()] = make_pair(order.getOrderId(), order.getQuantity());
            } else if (order.getType() == "sell") {
                // Add to sell map
                sell[order.getPrice()] = make_pair(order.getOrderId(), order.getQuantity());
            }

            // Attempt to match orders
            matchOrders();
        }

    private:
        void matchOrders() {
            //matching logic: match the highest buy with the lowest sell
            while (!buy.empty() && !sell.empty() && buy.begin()->first >= sell.begin()->first) {
                auto buyOrder = buy.begin();
                auto sellOrder = sell.begin();

                int minQunatity=min(buyOrder->second.second ,sellOrder->second.second);

                cout << "Matched Order: Buy ID " << buyOrder->second.first << " with Sell ID " << sellOrder->second.first << endl << endl;

                //Remove matched orders from book
                buyOrder->second.second-=minQunatity;
                sellOrder->second.second-=minQunatity;


                if(buyOrder->second.second==0)
                {
                    cout<<"Buy ID "<<buyOrder->second.first <<" fully executed\n\n";
                    buy.erase(buy.begin()++);
                }

                if(sellOrder->second.second==0)
                {
                    cout<<"Sell ID "<<sellOrder->second.first <<" fully executed\n\n";
                    sell.erase(sell.begin()++);
                }
                
            }
        }
};

int main() {
    OrderBook ob;
    // Add orders to the order book
    // Assuming Order constructor takes input from user

    while(true)
    {
        cout<<"1 : place order\n";
        cout<<"0 : exit";

        int a;
        cin>>a;

        if(a)
        ob.addOrder(Order());

        else break;
    }

    return 0;
}