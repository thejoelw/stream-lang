#ifndef VECTORSTREAM_H
#define VECTORSTREAM_H

#include <vector>

#include "stream.h"
#include "element.h"

template <typename ElementType>
class VectorStream : public Stream<ElementType> {
private:
    std::vector<ElementType> data;
};

#endif // VECTORSTREAM_H
