#include "ArbiterRC.h"


namespace ArbiterMaintenance
{
    ArbiterRC CalErrorCode(ArbiterTracer::ACTION currentAction)
    {
        return ArbiterRC(1000 * int(currentAction) + errno);
    }
}
