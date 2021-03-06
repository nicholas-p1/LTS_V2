#include <string>
#include <vector>
#include <iostream>
#include "inductor.hpp"

Inductor::Inductor(string name, vector<string> args, vector<float> extraInfo)
    :Component{name}
{
    nodes = processNodes({args[0], args[1]});

	nodalVoltages = {0,0};

	int order = 1;
	subComponents = 2;
	compCurrent = 0; // Refers to the current of the companion model current source, however is used opposite in direction to standard current source convention in updateVals for simplicity of coding. getCurrent returns the correct value and direction.
	prevTotalCurrent=0;
	compVoltage = 0; //Refers to voltage across the inductor after the previous timestep's voltage calculation.

	inductance = getValue(args[2]);
	timeStep = extraInfo[0];

	if(order==1){ //Conductance of the inductor will be the same as the companion model even at T=0 
		compConductance = timeStep/(2.0*inductance);
	}else{
		cerr << "Unsupported integration method order" <<endl;
		exit(1);
	}

	types.push_back(componentType::conductanceSource);
	types.push_back(componentType::currentSource);
	types.push_back(componentType::vcUpdatable);
	types.push_back(componentType::nonVoltageSource);
}

float Inductor::getConductance() const{
	return compConductance;
}

float Inductor::getCurrent() const{
	return -compCurrent; //So it's in the right direction, as current source points towards negative.
}

string Inductor::getTotalCurrentString(const VectorXd &x, int highestNodeNumber, float voltage, int order) {
	voltage = nodalVoltages[0] - nodalVoltages[1];

	if(order == 1){ //companion model from Trapezoidal numerical integration method
		float res= voltage*compConductance + compConductance*compVoltage +prevTotalCurrent; //
		prevTotalCurrent = res;
		return to_string(res); //negative as current flows from n1 to n2 of inductor
	}else{
		cerr << "Unsupported integration method order" <<endl;
		exit(1);
	}
}

void Inductor::updateVals(float newVoltage, float newCurrent, int order){
	if(order==1){ //using companion model for the trapezoid integration method.		
		compCurrent =(2.0*compConductance*newVoltage)+compCurrent;

		compVoltage = newVoltage;
	}else{
		cerr << "Unsupported integration method order" <<endl;
		exit(1);
	}
}

void Inductor::setTimeStep(double _timeStep){
	timeStep = _timeStep;

	//use the new timeStep to update conductance
	compConductance = timeStep/(2.0*inductance);
}

void Inductor::initCompCurrent(float _current){
	compCurrent = _current;
	prevTotalCurrent = _current;
}

double Inductor::ivAtNode(int n){
	return compCurrent * (n==nodes[0] ? 1 : -1);
}
double Inductor::divAtNode(int n, int dn){
	return compConductance * (n==nodes[0] ? -1 : 1) * (dn==nodes[0] ? -1 : 1);
}
