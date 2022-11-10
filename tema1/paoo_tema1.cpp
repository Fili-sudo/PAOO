#include <iostream>
using namespace std;

class Engine{
    private:
    float power;
    Engine(float power) : power(power) {}

    public:
    static Engine* getEngine(float power){
        return new Engine(power);
    }
    Engine& operator=(const Engine& rhs) {
        if (this != &rhs){
            this->power = rhs.power;
        }
        return *this;
    }
    Engine(const Engine& rhs) {
        this->power = rhs.power;
    }
    void toString(){
        cout<<"power:"<<power<<endl;
    }

};

class Car{
    public:
    Car(string colour, string brand, string fuelType, float enginePower) :
    colour(colour),
    brand(brand),
    fuelType(fuelType) {
        this->engine = Engine::getEngine(enginePower);
    }
    ~Car(){
        delete engine;
    }
    Car(const Car& rhs) {
        this->colour = rhs.colour;
        this->brand = rhs.brand;
        this->fuelType = rhs.fuelType;
        this->engine = rhs.engine;
    }
    Car& operator=(const Car& rhs) {
        if (this != &rhs){
            this->colour = rhs.colour;
            this->brand = rhs.brand;
            this->fuelType = rhs.fuelType;
            this->engine = rhs.engine;
        }
        return *this;
    }

    void toString(){
        cout<<"colour:"<<colour<<endl;
        cout<<"brand:"<<brand<<endl;
        cout<<"fuelType:"<<fuelType<<endl;
        this->engine->toString();
    }

    private:
    string colour;
    string brand;
    string fuelType;
    Engine* engine;

};

class Uncopyable {
    protected: // allow construction
    Uncopyable() {} // and destruction of
    ~Uncopyable() {} // derived objects...
    private:
    Uncopyable(const Uncopyable&); // ...but prevent copying
    Uncopyable& operator=(const Uncopyable&);
};

class Person : private Uncopyable{
    private:
    string id;
    string name;
    float height;

    public:
    Person(string id, string name, float height) :
    id(id),
    name(name),
    height(height) {}
    toString(){
        cout<<"this is a person named "<<name<<" that is "<<height<<" tall and can be identified by this id "<<id<<endl;
    }
};

int main() {
    Car c1("albastru", "mazda", "benzina", 3);
    Car c2(c1);
    Car c3("rosu", "bmw", "motorina", 10);

    cout<<endl;
    c1.toString();
    cout<<endl;
    c2.toString();
    cout<<endl;
    c3.toString();
    cout<<endl;
    c3 = c1;
    c3.toString();
    
    Person Ovi("5000427986675", "Ovidiu Bogosel", 1.75);
    Ovi.toString();
    
    
    return 0;
}