#include "DDredis.h"

#include <cstring>

//#include <iostream>
//using std::cout;

DDredis::DDredis()
{
    strRes = NULL;
    geoRes = NULL;
    geoReslen = 0;
    _conn = NULL;
    _reply = NULL;
    //ctor
}

DDredis::~DDredis()
{
    //dtor
}

bool DDredis::connect(char *host, int port){
    _conn = redisConnect(host, port);
    if(_conn == NULL || _conn->err)  {
        return false;
    }
    return true;
}
void DDredis::close(){
    if (_conn !=NULL){
        redisFree(_conn);
    }
    freeRes();
}

bool DDredis::setGeo(char *tel, char *lng, char *lat, char *key){
    freeRes();
    _reply = (redisReply*)redisCommand(_conn, "GEOADD %s %s %s %s", key, lng, lat, tel);
    if (_reply->type == REDIS_REPLY_ERROR){
        return false;
    }
    else {
        return true;
    }
}
bool DDredis::delGeo(char *tel, char *key){
    freeRes();
    _reply = (redisReply*)redisCommand(_conn, "ZREM %s %s", key, tel);
    if (_reply->type == REDIS_REPLY_ERROR){
        return false;
    }
    else {
        return true;
    }
}
bool DDredis::getGeo(char *tel, char *key){
    freeRes();
    _reply = (redisReply*)redisCommand(_conn, "GEOPOS %s %s", key, tel);
    if (_reply->type == REDIS_REPLY_ERROR){
        return false;
    }
    else {
        geoReslen = _reply->elements;
        DD_geo **g = new DD_geo*[geoReslen];
        for (int i = 0; i < geoReslen; i++){
            g[i] = new DD_geo();
            //cout << _reply->element[i]->elements << "\n";
            //cout << _reply->element[i]->element[0]->str << " " << _reply->element[i]->element[0]->len << "\n";
            memcpy(g[i]->name, tel, strlen(tel)+1);
            memcpy(g[i]->lng, _reply->element[i]->element[0]->str, _reply->element[i]->element[0]->len+1);
            memcpy(g[i]->lat, _reply->element[i]->element[1]->str, _reply->element[i]->element[1]->len+1);
        }
        geoRes = g;
        return true;
    }
}
bool DDredis::getGeoAround(char *lng, char *lat, char *km, char *key){
    freeRes();
    _reply = (redisReply*)redisCommand(_conn, "GEORADIUS %s %s %s %s km WITHCOORD", key, lng, lat, km);
    if (_reply->type == REDIS_REPLY_ERROR){
        return false;
    }
    else {
        geoReslen = _reply->elements;
        DD_geo **g = new DD_geo*[geoReslen];
        for (int i = 0; i < geoReslen; i++){
            g[i] = new DD_geo();
            memcpy(g[i]->name, _reply->element[i]->element[0]->str, _reply->element[i]->element[0]->len+1);
            memcpy(g[i]->lng, _reply->element[i]->element[1]->element[0]->str, _reply->element[i]->element[1]->element[0]->len+1);
            memcpy(g[i]->lat, _reply->element[i]->element[1]->element[1]->str, _reply->element[i]->element[1]->element[1]->len+1);
        }
        geoRes = g;
        return true;
    }
}

bool DDredis::setOrdPos(char *clitel, char *startPos, char *endPos){
    freeRes();
    _reply = (redisReply*)redisCommand(_conn, "HMSET ord:%s startPos %s endPos %s", clitel, startPos, endPos);
    if (_reply->type == REDIS_REPLY_ERROR){
        return false;
    }
    else {
        return true;
    }
}
bool DDredis::setOrdState(char *clitel, char *state){
    freeRes();
    _reply = (redisReply*)redisCommand(_conn, "HSET ord:%s state %s", clitel, state);
    if (_reply->type == REDIS_REPLY_ERROR){
        return false;
    }
    else {
        return true;
    }
}
bool DDredis::setOrdDriver(char *clitel, char *driver){
    freeRes();
    _reply = (redisReply*)redisCommand(_conn, "HSET ord:%s driver %s", clitel, driver);
    if (_reply->type == REDIS_REPLY_ERROR){
        return false;
    }
    else {
        return true;
    }
}
bool DDredis::delOrd(char *clitel){
    freeRes();
    _reply = (redisReply*)redisCommand(_conn, "DEL ord:%s ", clitel);
    if (_reply->type == REDIS_REPLY_ERROR){
        return false;
    }
    else {
        return true;
    }
}
bool DDredis::getOrdStartPos(char *clitel){
    freeRes();
    _reply = (redisReply*)redisCommand(_conn, "HGET ord:%s startPos", clitel);
    if (_reply->type == REDIS_REPLY_ERROR){
        return false;
    }
    else {
        strRes = _reply->str;
        return true;
    }
}
bool DDredis::getOrdEndPos(char *clitel){
    freeRes();
    _reply = (redisReply*)redisCommand(_conn, "HGET ord:%s endPos", clitel);
    if (_reply->type == REDIS_REPLY_ERROR){
        return false;
    }
    else {
        strRes = _reply->str;
        return true;
    }
}
bool DDredis::getOrdState(char *clitel){
    freeRes();
    _reply = (redisReply*)redisCommand(_conn, "HGET ord:%s state", clitel);
    if (_reply->type == REDIS_REPLY_ERROR){
        return false;
    }
    else {
        strRes = _reply->str;
        return true;
    }
}

void DDredis::freeRes(){
    if (_reply != NULL){
        freeReplyObject(_reply);
        _reply = NULL;
    }
    if (geoRes != NULL){
        for(int i = 0; i < geoReslen; i++){
            delete geoRes[i];
        }
        delete [] geoRes;
        geoRes = NULL;
        geoReslen = 0;
    }
    strRes = NULL;
}
