#include "ArbiterTrace.h"

using namespace ArbiterMaintenance;
ArbiterTracer::TRACE_LEVEL  ArbiterTracer::TraceLevel	= ArbiterTracer::TRACE_LEVEL_INFO;
std::string                 ArbiterTracer::AppName	= APP_NAME[APP_NAME_SERVER];
std::string                 ArbiterTracer::ProcessName;
