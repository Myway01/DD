#include "CliInfo.h"

CliInfo::CliInfo(){

}

CliInfo* CliInfo::info = new CliInfo();
CliInfo* CliInfo::getCliInfo(){
    return info;
}
