#include "ArbiterRC.h"


namespace ArbiterMaintenance
{
    ArbiterRC CalErrorCode(ArbiterTracer::ACTION currentAction)
    {
        CalErrorCode(currentAction, errno);
    }
    ArbiterRC CalErrorCode(ArbiterTracer::ACTION currentAction, int err)
    {
        return ArbiterRC(1000 * int(currentAction) + err);
    }
}
