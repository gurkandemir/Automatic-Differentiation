#include "function.h"
#include "math.h"
#include "iostream"
Function::Function(int _id, string _name) {
    id=_id;
    name=_name;
    isDouble=false;
    isCycle=false;
}


/*Function::~Function() {
    delete output;
    for (auto it = inputs.begin(); it != inputs.end(); it++) {
        delete *it;
    }
}*/

void Function::addInput(Variable *input) {
    inputs.push_back(input);
    if(inputs.size()==2) {
        isDouble = true;
        isCycle=true;
    }
}

void Function::setOutput(Variable *_output) {
    output=_output;
}

Addition::Addition(int _id, string _name) : Function(_id,_name) {
    id=_id;
    name=_name;
}

void Addition::doForward() {
    output->value = inputs[0]->value + inputs[1]->value;
}

void Addition::doBackward() {
    inputs[0]->derivative += output->derivative;
    inputs[1]->derivative += output->derivative;
}

Multiplication::Multiplication(int _id, string _name) : Function(_id,_name) {
    id=_id;
    name=_name;
}
void Multiplication::doForward() {
    this->output->value = this->inputs[0]->value * this->inputs[1]->value;
}

void Multiplication::doBackward() {
    inputs[0]->derivative += inputs[1]->value * output->derivative;
    inputs[1]->derivative += inputs[0]->value * output->derivative;
}

Subtraction::Subtraction(int _id, string _name)  : Function(_id,_name){
    id=_id;
    name=_name;
}
void Subtraction::doForward() {
    output->value = inputs[0]->value - inputs[1]->value;
}

void Subtraction::doBackward() {
    inputs[0]->derivative += output->derivative;
    inputs[1]->derivative += -1 * output->derivative;
}

Division::Division(int _id, string _name)  : Function(_id,_name){
    id=_id;
    name=_name;
}
void Division::doForward() {
    output->value = inputs[0]->value / inputs[1]->value;
}

void Division::doBackward() {
    inputs[0]->derivative += (1.0 / inputs[1]->value) * output->derivative;
    inputs[1]->derivative += ((-1.0 * inputs[0]->value) / (inputs[1]->value * inputs[1]->value)) * output->derivative;
}

Sine::Sine(int _id, string _name)  : Function(_id,_name){
    id=_id;
    name=_name;
}
void Sine::doForward() {
    output->value = sin(inputs[0]->value);
}

void Sine::doBackward() {
    inputs[0]->derivative += cos(inputs[0]->value) * output->derivative;
}

Cosine::Cosine(int _id, string _name)  : Function(_id,_name){
    id=_id;
    name=_name;
}
void Cosine::doForward() {
    output->value = cos(inputs[0]->value);
}

void Cosine::doBackward() {
    inputs[0]->derivative += -1.0 * sin(inputs[0]->value) * output->derivative;
}

Tangent::Tangent(int _id, string _name)  : Function(_id,_name){
    id=_id;
    name=_name;
}
void Tangent::doForward() {
    output->value = tan(inputs[0]->value);
}

void Tangent::doBackward() {
    inputs[0]->derivative += (1.0 / (cos(inputs[0]->value) * cos(inputs[0]->value))) * output->derivative;
}

Identity::Identity(int _id, string _name)  : Function(_id,_name){
    id=_id;
    name=_name;
}
void Identity::doForward() {
    output->value = inputs[0]->value;
}

void Identity::doBackward() {
    inputs[0]->derivative += output->derivative;
}

ArcCosine::ArcCosine(int _id, string _name)  : Function(_id,_name){
    id=_id;
    name=_name;
}
void ArcCosine::doForward() {
    output->value = acos(inputs[0]->value);
}

void ArcCosine::doBackward() {
    inputs[0]->derivative += -1 * (1.0 / sqrt(1 - pow(inputs[0]->value,2))) * output->derivative;
}

ArcSine::ArcSine(int _id, string _name)  : Function(_id,_name){
    id=_id;
    name=_name;
}
void ArcSine::doForward() {
    output->value = asin(inputs[0]->value);
}

void ArcSine::doBackward() {
    inputs[0]->derivative += 1 * (1.0 / sqrt(1 - pow(inputs[0]->value,2))) * output->derivative;
}

ArcTangent::ArcTangent(int _id, string _name)  : Function(_id,_name){
    id=_id;
    name=_name;
}
void ArcTangent::doForward() {
    output->value = atan(inputs[0]->value);
}

void ArcTangent::doBackward() {
    inputs[0]->derivative += 1.0 / (1 + pow(inputs[0]->value,2)) * output->derivative;
}

Exponential::Exponential(int _id, string _name)  : Function(_id,_name){
    id=_id;
    name=_name;
}
void Exponential::doForward() {
    output->value = exp(inputs[0]->value);
}

void Exponential::doBackward() {
    inputs[0]->derivative += exp(inputs[0]->value) * output->derivative;
}

Log::Log(int _id, string _name)  : Function(_id,_name){
    id=_id;
    name=_name;
}
void Log::doForward() {
    output->value = log(inputs[0]->value);
}

void Log::doBackward() {
    inputs[0]->derivative += (1.0 / inputs[0]->value) * output->derivative;
}

Log10::Log10(int _id, string _name)  : Function(_id,_name){
    id=_id;
    name=_name;
}
void Log10::doForward() {
    output->value = log10(inputs[0]->value);
}

void Log10::doBackward() {
    inputs[0]->derivative += (1.0 / inputs[0]->value) * log10(exp(1)) * output->derivative;
}

Sqrt::Sqrt(int _id, string _name)  : Function(_id,_name){
    id=_id;
    name=_name;
}
void Sqrt::doForward() {
    output->value = sqrt(inputs[0]->value);
}

void Sqrt::doBackward() {
    inputs[0]->derivative += (1.0 / (2 * sqrt(inputs[0]->value))) * output->derivative;
}

Power::Power(int _id, string _name)  : Function(_id,_name){
    id=_id;
    name=_name;
}
void Power::doForward() {
    output->value = pow(inputs[0]->value,inputs[1]->value);
}

void Power::doBackward() {
    inputs[0]->derivative += inputs[1]->value * (pow(inputs[0]->value,inputs[1]->value-1)) * output->derivative;
    inputs[1]->derivative += pow(inputs[0]->value, inputs[1]->value) * (log(inputs[0]->value)) * output->derivative;
}

