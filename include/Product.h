#include <string>

using namespace std;

class Product{
public:
    Product(){}
    virtual ~Product(){};

    string name;
    string tag;
    float qty = 10;
    double price = 10;
    double basePrice = 10;
    unsigned long int consumption = 0;
    unsigned long int production = 0;
};
