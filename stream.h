#ifndef STREAM_H
#define STREAM_H

#include <vector>

#include "closure.h"

class Stream
{
public:
    Stream()
    {}

    void apply_from(Closure *func); // this <- func
    void flow_from(Closure *func); // this <= func

    void set_applies_to(Stream *stream, Stream *out);
    void set_applies_from(Stream *stream, Stream *out);
    void set_flows_to(Stream *stream, Stream *out);

protected:
    std::vector<Closure*> funcs;

    std::vector<Stream*> applies_to;
    std::vector<Stream*> applies_from;
    std::vector<Stream*> flows_to;
};

#endif // STREAM_H
