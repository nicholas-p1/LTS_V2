#ifndef DIODE_HPP
#define DIODE_HPP

#include "component.hpp"

class Diode: public Component{
private:
	static constexpr float vt = 25e-3f; //Constants for now. Could determine from netlist later on
	static constexpr float is = 1e-14f;
	double compCurrent; //Value of the current source in the companion model
	// float compVoltage; //value of the voltage across the diode
	double compConductance; //Conductance of the resistor in the companion model

public:
	Diode(string name, vector<string> args, vector<float> extraInfo);
	Diode(string _name, float l, int n1, int n2, float timeStep, int order);
	~Diode() = default;

	// float getIs() const;
	// float getVt() const;
	vector<int> getNodes() const ;
	double getConductance() const override;
	double getCurrent() const override;
	double getTotalCurrent(float voltage, int order = 1) override;
	
	//voltage = voltage across diode (v_n1 - v_n2)
	void updateVals(float time_or_voltage) override;
};

#endif
