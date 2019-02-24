#ifndef PAINT_SUBJECT
#define PAINT_SUBJECT

#include "IPaintObservor.h"

class IPaintSubject{
    public:
        virtual void notifyAll() = 0;
        virtual void registerPaintObservor(IPaintObservor *observor) = 0;
};
#endif
