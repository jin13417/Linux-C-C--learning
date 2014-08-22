#include "myclass.h"
#include "interface.h"

#ifdef __cplusplus
extern "C"{
#endif

void interface()
{
    Myclass obj;
    obj.Operation();
}

#ifdef __cplusplus
}
#endif
