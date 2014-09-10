#ifndef STREAM_H
#define STREAM_H

#include <vector>
#include <string>

class Object;

class Stream
{
public:
    Stream()
    {}

    Stream *apply_to(Object *func); // this -> func
    Stream *apply_from(Object *func); // this <- func
    void flow_from(Object *func); // this <= func

    void set_applies_to(Stream *stream, Stream *out); // this -> func
    void set_applies_from(Stream *stream, Stream *out); // this <- func
    void set_flows_to(Stream *stream); // this => func
    void set_flows_from(Stream *stream); // this <= func

    std::vector<Object*> &get_vector() {return funcs;}

    std::string to_string();

protected:
    std::vector<Object*> funcs;

    std::vector<Stream*> applies_to;
    std::vector<Stream*> applies_from;
    std::vector<Stream*> flows_to;
};

#endif // STREAM_H
