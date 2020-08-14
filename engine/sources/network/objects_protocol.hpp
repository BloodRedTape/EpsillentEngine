#ifndef OBJECTS_PROTOCOL
#define OBJECTS_PROTOCOL

#include "core/net/protocol.hpp"
#include "core/guid.hpp"
#include "SFML/System/Vector2.hpp"

enum Events : uint64{
    NullEvent               = 0,
    ObjectNew               = 1,
    ObjectDelete            = 2,
    ObjectOriginatorEvent   = 3,
    ObjectVar               = 4,
    ObjectTranslate         = 5,
    EngineCodesCount
};


#define EventCode(Num) ((protocol::EventCode)Num)


struct EventObjectNew: public protocol::Header{
    GUID guid;
    sf::Vector2f position;
    char class_name[DATAGRAM_DATA_SIZE-sizeof(GUID)-sizeof(sf::Vector2f)];
    EventObjectNew();
};
struct EventObjectDelete: public protocol::Header{
    GUID guid;
    EventObjectDelete();
};
struct EventObjectTranslate: public protocol::Header{
    GUID guid;
    sf::Vector2f position;
    EventObjectTranslate();
};

struct OriginatorEvent{
    uint16 event_code;
    byte data[DATAGRAM_DATA_SIZE-sizeof(GUID)-sizeof(uint16)];
    OriginatorEvent(uint16 code = 0);
};


struct EventObjectOriginator: public protocol::Header{
    GUID guid;
    OriginatorEvent content;
};


#endif