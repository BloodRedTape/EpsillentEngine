#ifndef OBJECTS_PROTOCOL
#define OBJECTS_PROTOCOL

#include "core/net/protocol.hpp"
#include "core/guid.hpp"
enum Events : uint64{
    NullEvent   = 0,
    ObjectNew   = 1,
    ObjectDel   = 2
};

#define EventCode(Num) ((protocol::EventCode)Num)


#endif