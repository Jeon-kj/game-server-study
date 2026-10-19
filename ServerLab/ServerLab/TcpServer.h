#pragma once

SOCKET CreateListenSocket();
void RunAcceptLoop(SOCKET listenSocket);
