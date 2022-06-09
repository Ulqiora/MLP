#pragma once
namespace s21{
class INeuron{
protected:
    double _value;
public:
    virtual double getValue() =  0;
    virtual void setValue(double& otherValue) = 0;
};


class NeuronClassic : public INeuron{
public:
    void setValue(double& otherValue) override;
    double getValue() override;
};

class NeuronBios : public INeuron{
public:
    NeuronBios(double otherValue=1.0);
    double getValue() override;
};
}    //    namespace s21
