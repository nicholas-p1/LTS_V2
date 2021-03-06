#ifndef RESISTOR_HPP
#define RESISTOR_HPP

#include <vector>
#include <string>

#include "component.hpp"

class Resistor: public Component{
private:
    float conductance;
public:
    Resistor(string _name, vector<string> args, vector<float> extraInfo);
    ~Resistor() = default;

    double ivAtNode(int n1) override;
    double divAtNode(int n, int dn) override;

    float getConductance() const override;

    string getTotalCurrentString(const VectorXd &x, int highestNodeNumber, float voltage = 0, int order = 1)  override;
};

#endif