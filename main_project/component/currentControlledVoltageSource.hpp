#ifndef CURRENTCONTROLLEDVOLTAGESOURCE_HPP
#define CURRENTCONTROLLEDVOLTAGESOURCE_HPP

#include <vector>
#include <string>

#include "controlledSource.hpp"

class CurrentControlledVoltageSource: public ControlledSource{
public:
    CurrentControlledVoltageSource(string _name, vector<string> args, vector<double> extraInfo);
    // CurrentControlledVoltageSource(string _name, double _voltage, int n1, int n2, int nc1, int nc2);
    ~CurrentControlledVoltageSource() = default;
};

#endif