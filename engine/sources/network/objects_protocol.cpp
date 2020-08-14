#include "network/objects_protocol.hpp"
#include <string.h>

EventObjectNew::EventObjectNew(){
    memset(this,0,sizeof(EventObjectNew));
    type = protocol::DatagramType::Event;
    code.event = EventCode(Events::ObjectNew);
}

EventObjectDelete::EventObjectDelete(){
    memset(this,0,sizeof(EventObjectDelete));
    type = protocol::DatagramType::Event;
    code.event = EventCode(Events::ObjectDelete);
}

EventObjectTranslate::EventObjectTranslate(){
    memset(this,0,sizeof(EventObjectTranslate));
    type = protocol::DatagramType::Event;
    code.event = EventCode(Events::ObjectTranslate);
}

OriginatorEvent::OriginatorEvent(uint16 code){
    memset(this,0,sizeof(OriginatorEvent));
    event_code = code;
}