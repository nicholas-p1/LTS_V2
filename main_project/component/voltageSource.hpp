#ifndef VOLTAGESOURCE_HPP
#define VOLTAGESOURCE_HPP

#include <vector>
#include <string>

#include "component.hpp"
#include "waveform.hpp"

class VoltageSource: public Component{
private:
    int sourceType;

    //used for dc
    float voltage;

    Waveform voltageWaveform{};
public:
    VoltageSource(string _name, vector<string> args, vector<float> extraInfo);
    VoltageSource(string _name, float _voltage, int n1, int n2);
    ~VoltageSource() = default;

    void setupBasic(int n1, int n2);
    void setupDC(float voltage);

    void updateVals(float time);

    float ivAtNode(int n1, int n2, float v) const override;
    float divAtNode(int n1, int n2, int dn, float v) const override;

    float getVoltage() const override;

    vector<int> getNodes() const override;
};

#endif