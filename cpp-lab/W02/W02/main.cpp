#define _CRTDBG_MAP_ALLOC
#include <iostream>
#include <crtdbg.h>

// Day1
void Run01Lab();
void Run02Lab();
void Run03Lab();
void Run04Lab();
// Day2
void Run05Lab();

int main()
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    //Run01Lab();
    //Run02Lab();
    //Run03Lab();
    //Run04Lab();
    Run05Lab();
}

