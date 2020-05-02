//Can driver includes
#include "Can.h"

#include "CanIf_Cbk.h"

#include "Can_PBcfg.h"

#include <stdbool.h>

#include "C:/Keil/EE319Kware/inc/hw_can.h"
#include "C:/Keil/EE319Kware/inc/hw_ints.h"
#include "C:/Keil/EE319Kware/inc/hw_memmap.h"
#include "Can.h"
#include "C:/Keil/EE319Kware/driverlib/gpio.h"
#include "C:/Keil/EE319Kware/driverlib/interrupt.h"
#include "C:/Keil/EE319Kware/driverlib/pin_map.h"
#include "C:/Keil/EE319Kware/driverlib/sysctl.h"
#include "C:/Keil/EE319Kware/driverlib/uart.h"
#include "C:/Keil/Labware/utils/uartstdio.h"

#include "C:/Keil/EE319Kware/inc/hw_types.h"
#include "C:/Keil/EE319Kware/driverlib/debug.h"
#include "C:/Keil/Labware/driverlib/fpu.h"
#include "Rom.h"



//Configure Can controller to receive messages on the specified receive object
void Prepare_Receiver(uint32 receive_object) {
	tCANMsgObject sCANMessage;
	uint8_t pui8MsgData[8];

	//
	// Initialize a message object to be used for receiving CAN messages with
	// any CAN ID.  In order to receive any CAN ID, the ID and mask must both
	// be set to 0, and the ID filter enabled.
	//
	sCANMessage.ui32MsgID = 0;
	sCANMessage.ui32MsgIDMask = 0;
	sCANMessage.ui32Flags = MSG_OBJ_RX_INT_ENABLE | MSG_OBJ_USE_ID_FILTER;
	sCANMessage.ui32MsgLen = 8;

	//
	// Now load the message object into the CAN peripheral.  Once loaded the
	// CAN will receive any message on the bus, and an interrupt will occur.
	// Use message object 1 for receiving messages (this is not the same as
	// the CAN ID which can be any value in this example).
	//
	CANMessageSet(CAN0_BASE, receive_object, &sCANMessage, MSG_OBJ_TYPE_RX);
}

/**
 * Initialize software and hardware configurations for one CAN controller.
 *
 * @param canx_config			----- CAN controller configuration
 */
void Can_InitController(Can_ControllerConfigType *canx_config) {
	
	// Enable GPIO port
	SysCtlPeripheralEnable(canx_config->ui32GpioPeripheral);
	
	// Configure the GPIO pin muxing to select CAN functions for the pins.
	GPIOPinConfigure(canx_config->ui32RxPinConfig);
	GPIOPinConfigure(canx_config->ui32TxPinConfig);
	
	// Enable the alternate function on the GPIO pins.
	GPIOPinTypeCAN(canx_config->ui32Port, canx_config->ui8Pins);
	
	// Enable the CAN peripheral.
	SysCtlPeripheralEnable(canx_config->ui32CanPeripheral);
	
	// Initialize the CAN controller.
	CANInit(canx_config->ui32CanBase);
	
	// Set up the bit rate for the CAN bus.
	CANBitRateSet(canx_config->ui32CanBase, SysCtlClockGet(), canx_config->ui32BitRate);
	
	// Enable the CAN for operation.
	CANEnable(canx_config->ui32CanBase);
	
	//Check if the controller wants to receive messages. If so, configure it.
	if(canx_config->receive_object != -1) {
		Prepare_Receiver(canx_config->receive_object);
	}
	
}

/**
 * Initialize software and hardware configurations for all attached CAN controllers.
 *
 * @param Config			----- CAN driver configuration
 */
void Can_Init(const Can_ConfigType* Config) {
	int i=0;
	for( i=0; i<2; i++) {
		if(Config->canx_config[i]) {
			Can_InitController(Config->canx_config[i]);
		}
	}
	
}

/**
 *  Perform polling of TX confirmation, and send confirmation to CanIf
 */
void Can_MainFunction_Write(void) {
	while((CANStatusGet(CAN0_BASE, CAN_STS_TXREQUEST) & 1)) {}
	//Send confirmation to CanIf	
}

/**
 *  Perform polling of RX indication, read the message from RX buffers, and send it to CanIf
 * @param Msg[] 			----- 1 to 8 bytes received message
 * @param SduLength  	----- Message length
 * @param id  				----- Can Id
 * @param hoh 				----- Pin Id
 * @param driverId  	----- Id of driver that received the message
 * @return 						----- result status
 */
void Can_To_CanIf(uint8_t Msg[], PduLengthType SduLength, uint32_t id , uint16 hoh , uint8 ControllerID) {
	//uint8_t Msg[] = "from CAN drv to CANIF";
	const PduInfoType L_PDU = {
		.SduDataPtr = Msg,
		.SduLength = SduLength
	};
	Can_HwType Mailbox;
	Mailbox.CanId = (uint16)id;
	Mailbox.Hoh = hoh;
	Mailbox.ControllerId = ControllerID;
	CanIf_RxIndication(&Mailbox, &L_PDU);
}

/**
 *  Perform polling of RX indication, read the message from RX buffers, and send it to CanIf
 */
void Can_MainFunction_Read(void) {
	
	while((CANStatusGet(CAN0_BASE, CAN_STS_NEWDAT) & 1) == 0) {}

	tCANMsgObject sCANMessage;
	uint8_t pui8MsgData[8];
	sCANMessage.pui8MsgData = pui8MsgData;
	
	//
	// Read the message from the CAN.  Message object number 1 is used
	// (which is not the same thing as CAN ID).  The interrupt clearing
	// flag is not set because this interrupt was already cleared in
	// the interrupt handler.
	//
	CANMessageGet(CAN0_BASE, 1, &sCANMessage, 0);

	//
	// Check to see if there is an indication that some messages were
	// lost.
	//
	if(sCANMessage.ui32Flags & MSG_OBJ_DATA_LOST)
	{
			UARTprintf("CAN message loss detected\n");
	}

	//
	// Print out the contents of the message that was received.
	//
	UARTprintf("A new message arrived to Can driver!\n");
	UARTprintf("Msg ID=0x%08X len=%u data=0x",
						 sCANMessage.ui32MsgID, sCANMessage.ui32MsgLen);
	unsigned int uIdx;
	for(uIdx = 0; uIdx < sCANMessage.ui32MsgLen; uIdx++)
	{
			UARTprintf("%02X ", pui8MsgData[uIdx]);
	}
	UARTprintf("\n");
	
	//Send message to CanIf
	Can_To_CanIf(pui8MsgData, sCANMessage.ui32MsgLen, sCANMessage.ui32MsgID , 
							 CanConfig.canx_config[0]->pin_id, CanConfig.canx_config[0]->controller_id);
}

/**
 * Transmit PDU to CAN bus
 *
 * @param hth 				----- hardware transmit handle (HTH)
 * @param pduInfo  		----- PDU (protocol data unit), consists of: CanIf Id, Can Id, data, DLC
 * @return 						----- result status
 */
Can_ReturnType Can_Write(Can_HwHandleType hth, Can_PduType *pduInfo) {
	
	UARTprintf("Can got a message; hth: %d, CanId: %d, PrivateID: %d, Length: %d, Data: ", 
							hth, pduInfo->id, pduInfo->swPduHandle, pduInfo->length);
	int i=0;
	for(i=0; i<pduInfo->length; i++) {
		UARTprintf("%02X ", pduInfo->sdu[i]);
	}
	UARTprintf("\n");
	
	//Get CAN controller's base address
	uint32 CAN_BASE = Can_Bases[Can_Controllers[hth]];
	
	//Build the CAN message
  tCANMsgObject sCANMessage;
	sCANMessage.ui32MsgID = pduInfo->id;
  sCANMessage.ui32MsgIDMask = 0;
  sCANMessage.ui32MsgLen = pduInfo->length;
  sCANMessage.pui8MsgData = pduInfo->sdu;
	
	// Send the CAN message using object number 1 (not the same thing as CAN ID).
	// This function will cause the message to be transmitted right away.
	CANMessageSet(CAN_BASE, 1, &sCANMessage, MSG_OBJ_TYPE_TX);
	Can_MainFunction_Write();
	UARTprintf("all is ok\n");
	return CAN_OK;
}