/*******************************************************************************
File name: MessageFunctions.h                                               ****
File description:   Include EUSART P2P groups functions definitions.        ****
MCU:                PIC18F45k22                                             ****
Date modified: 28/01/2018 16:14.                                            ****
Author: RoeeZ (Comm-IT).                                                    ****
****************************************************************************** */

#ifndef MESSAGEFUNCTIONS_H
#define	MESSAGEFUNCTIONS_H

#include "GroupsCommon.h"
#include "SystemStatus.h"
#include "LedsApp.h"
#include "AdcApp.h"

#define NUMBER_OF_MESSAGE_GROUPS    (6)

void GroupRx(MSG_REQUEST request, char* data);
void GroupTx(MSG_REQUEST request, char* data);
void GroupCommon(MSG_REQUEST request, char* data);

// Message groups array;
void (*groupsArray[NUMBER_OF_MESSAGE_GROUPS])() = 
{
    GroupRx,
    GroupTx,
    GroupCommon,
};

#endif	/* MESSAGEFUNCTIONS_H */

