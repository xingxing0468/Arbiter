#ifndef ARBITERRC_H
#define ARBITERRC_H
#include "errno.h"
#include "ArbiterTrace.h"

extern int errno;
namespace ArbiterMaintenance
{
enum ArbiterRC
{
    ARBITER_OK          = 0,
};

ArbiterRC CalErrorCode(ArbiterTracer::ACTION currentAction);

}

#endif // ARBITERRC_H
