#pragma once

#define WIN32_LEAN_AND_MEAN

#include "Types.h"
#include "Session.h"
#include "Packet.h"

#include <iostream>
#include <vector>

#include <WinSock2.h>
#include <mswsock.h>
#include <WS2tcpip.h>

#pragma comment(lib, "ws2_32.lib")

using namespace std;