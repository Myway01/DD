#include "DrvInfo.h"

DrvInfo::DrvInfo()
{

}

DrvInfo* DrvInfo::info = new DrvInfo();
DrvInfo* DrvInfo::getDrvInfo(){
    return info;
}
