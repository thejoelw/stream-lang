#ifndef STREAM_H
#define STREAM_H

#include <vector>

#include "astfunction.h"

class AstFunction;

class Stream
{
public:
    Stream();

    void apply_from(AstFunction *func); // this <- func
    void flow_from(AstFunction *func); // this <= func

    void set_applies_to(Stream *stream);
    void set_applies_from(Stream *stream);
    void set_flows_to(Stream *stream);

protected:
    std::vector<AstFunction*> funcs;

    std::vector<Stream*> applies_to;
    std::vector<Stream*> applies_from;
    std::vector<Stream*> flows_to;
};

#endif // STREAM_H
