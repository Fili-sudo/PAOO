#include <iostream>
using namespace std;


class Feline{

    public:
    Feline(string furColor, string provenience, float weight) : 
    furColor(furColor), 
    provenience(provenience),
    weight(weight) { }

    Feline& operator=(const Feline& rhs) {
        if (this != &rhs){
            this->furColor = rhs.furColor;
            this->provenience = rhs.provenience;
            this->weight = rhs.weight;
        }
        return *this;
    }
    Feline(const Feline& rhs) {
        this->furColor = rhs.furColor;
        this->provenience = rhs.provenience;
        this->weight = rhs.weight;
    }

    void identity(){
        cout<<"I am a feline"<<endl;
    }
    void sound(){

    }
    void description(){
        cout<<"I am a/an "<<furColor<<" feline from "<<provenience<<" weighting "<<weight<<"kg"<<endl;
    }

    protected:
    string getFurColor(){
        return furColor;
    }
    string getProvenience(){
        return provenience;
    }
    float getWeight(){
        return weight;
    }

    private:
    string furColor;
    string provenience;
    float weight;
};

class Cat : public Feline{
    public:
    Cat(string furColor, string provenience, float weight, bool isDomestic) :
    Feline(furColor, provenience, weight),
    isDomestic(isDomestic) {}

    Cat(const Cat& rhs) : 
    Feline(rhs),
    isDomestic(rhs.isDomestic) {}

    Cat& operator=(const Cat& rhs) {
        if (this != &rhs){
            Feline::operator=(rhs);
            isDomestic = rhs.isDomestic;
        }
        return *this;
    }

    void identity(){
        cout<<"I am a cat"<<endl;
    }
    void sound(){
        cout<<"miaaau"<<endl;
        
    }
    void description(){
        string domesticStatus = "domestic";
        if(!isDomestic){
            domesticStatus = "undomestic";
        }
        cout<<"I am a "<<getFurColor()<<" "
        <<domesticStatus<<" cat from "
        <<getProvenience()<<" weighting "
        <<getWeight()<<"kg"<<endl;
    }

    private:
    bool isDomestic;
};

int main(){

    Feline feline = Feline("orange", "Africa", 200);
    Cat cat = Cat("spotted", "Egypt", 4, true);
    Cat copyCat = Cat(cat);
    Cat copyCat2 =  cat;
    feline.identity();
    feline.description();
    cat.identity();
    cat.description();
    cat.sound();
    copyCat.description();
    copyCat2.description();
    
    return 0;
}