#ifndef PDUR_TYPES_H_
#define PDUR_TYPES_H_

#include "ComStack_Types.h"
#include "PduR_PbCfg.h"


typedef uint16_t PduR_PBConfigIdType;

//PDUR States
typedef enum{
  PDUR_UNINIT,
  PDUR_ONLINE,
  PDUR_REDUCED
}PduR_StateType;

//PDU Source
typedef struct{
  const PduIdType SourcePduHandleId;
  Pdu_Type * SrcPduRef;
}PduRSrcPdu_type;

//PDU Destination
typedef struct{
  const PduIdType DestPduHandleId;
  Pdu_Type * DestPduRef;
}PduRDestPdu_type;

//PDU Routing Path
typedef struct{
  PduRSrcPdu_type * PduRSrcPduRef;
  PduRDestPdu_type * PduRDestPduRef;
}PduRRoutingPath_type;

//PDUR Configuration
typedef struct PduR_PBConfig{
  PduR_PBConfigIdType PduRConfigurationId;
  //Maximum number of routing paths in all tables
  const uint16_t PduRMaxRoutingPathCnt;
  //Array of pointers to the routing paths and routing table
  PduRRoutingPath_type ** RoutingPaths;
}PduR_PBConfigType;

#endif