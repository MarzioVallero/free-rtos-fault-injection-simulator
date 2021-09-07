#undef UNICODE
#undef _UNICODE

#include <windows.h>
#include <string.h>

#include "../thread.h"

typedef struct
{
    HANDLE thread_id;
} thread_t;

int launchThread(void * function,
                void * address,
                unsigned long injTime,
                unsigned long offsetByte,
                unsigned long offsetBit,
                thread_t * id){
    HANDLE thread = INVALID_HANDLE_VALUE;
    DWORD thID;
    thData_t data = (thData_t) {address, injTime, offsetByte, offsetBit};
    thread = CreateThread(NULL, 0, function, data, 0, &thID);
    if(thread == INVALID_HANDLE_VALUE){
        return INJECTOR_THREAD_FAILURE;
    }
    id->thread_id = thread;
    return INJECTOR_THREAD_SUCCESS;
}

int detachThread(thread_t * id){
    CloseHandle(id->thread_id);
    return INJECTOR_THREAD_SUCCESS;
}