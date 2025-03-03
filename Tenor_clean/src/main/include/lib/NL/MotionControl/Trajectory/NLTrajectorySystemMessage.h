#pragma once
#include "lib/N/NCStandard.h"

#define NL_CATEGORY_MESSAGE_SYSTEM 1
#define NLMAKE_CATEGORIZED_MESSAGE(_id) ((NL_CATEGORY_MESSAGE_SYSTEM << 16) | ((_id) & 0xFFFF))

#define NL_MESSAGE_TRJ_START 1
#define NL_MESSAGE_TRJ_TIMEOUT 2
#define NL_MESSAGE_TRJ_ENDOFMESSAGE 3

#define NL_CATEGORIZED_MESSAGE_TRJ_START NLMAKE_CATEGORIZED_MESSAGE(NL_MESSAGE_TRJ_START)
#define NL_CATEGORIZED_MESSAGE_TRJ_TIMEOUT NLMAKE_CATEGORIZED_MESSAGE(NL_MESSAGE_TRJ_TIMEOUT)
#define NL_CATEGORIZED_MESSAGE_TRJ_ENDOFMESSAGE NLMAKE_CATEGORIZED_MESSAGE(NL_MESSAGE_TRJ_ENDOFMESSAGE)
