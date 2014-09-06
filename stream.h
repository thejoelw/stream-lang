#ifndef STREAM_H
#define STREAM_H

#include <vector>

class Closure;

class Stream
{
public:
    Stream()
    {}

    Stream *apply_to(Closure *func); // this -> func
    Stream *apply_from(Closure *func); // this <- func
    void flow_from(Closure *func); // this <= func

    void set_applies_to(Stream *stream, Stream *out); // this -> func
    void set_applies_from(Stream *stream, Stream *out); // this <- func
    void set_flows_to(Stream *stream); // this => func

protected:
    std::vector<Closure*> funcs;

    std::vector<Stream*> applies_to;
    std::vector<Stream*> applies_from;
    std::vector<Stream*> flows_to;
};

#endif // STREAM_H
