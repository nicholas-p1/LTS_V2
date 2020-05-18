#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include <vector>
#include <string>

#include "enums.hpp"

using namespace std;

class Component
{
protected:
    string name;
    vector<int> nodes;
    vector<componentType> types; //indicates functionality of subComponents
    int subComponents;
public:
    Component(string _name);
    virtual ~Component() = 0; //destructor of base class should be virtual (purely virtual as component should be abstract)

    virtual double getConductance() const;
    virtual float getVoltage() const;
    virtual double getCurrent() const; //For complex components, this returns the current through the companion model's current source rather than through the whole component
    virtual double getTotalCurrent(float voltage, int order = 1); //For complex components, this return the current through the whole component

    string getName() const;
    virtual vector<int> getNodes() const = 0;


    // this should be used to update the value of the voltage and current accross a component after an iteration
    virtual void updateVals(float newVoltage, float newCurrent, int order);
    // this should be used to update the time of the time dependant components or update nonlinear components (passing voltage)
    virtual void updateVals(float time_or_voltage);

    float getValue(string val) const;
    vector<componentType> getTypes() const;
};

#endif
