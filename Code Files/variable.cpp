#include "variable.h"

Variable::Variable() {

}
Variable::Variable(int _id, string _name, double _value) {
    id=_id;
    name=_name;
    value=_value;
    derivative=0;
    visit=false;
    isFirst=false;
    numTo=0;
}


void Variable::setFrom(Function *_from) {
    from=_from;
}

void Variable::addTo(Function *_to) {
    to.push_back(_to);
    numTo++;
}


