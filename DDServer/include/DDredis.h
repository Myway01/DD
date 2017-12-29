#ifndef DDREDIS_H
#define DDREDIS_H

#include <hiredis/hiredis.h>

#include "socktype.h"

class DDredis
{
    public:
        DDredis();
        virtual ~DDredis();

        bool connect(char *host, int port);
        void close();

        bool setGeo(char *tel, char *lng, char *lat, char *key);
        bool delGeo(char *tel, char *key);
        bool getGeo(char *tel, char *key);
        bool getGeoAround(char *lng, char *lat, char *km, char *key);

        bool setOrdPos(char *clitel, char *startPos, char *endPos);
        bool setOrdState(char *clitel, char *state);
        bool setOrdDriver(char *clitel, char *driver);
        bool setOrdFare(char *clitel, char *fare);
        bool delOrd(char *clitel);
        bool getOrdStartPos(char *clitel);
        bool getOrdEndPos(char *clitel);
        bool getOrdState(char *clitel);
        bool getOrdDriver(char *clitel);
        bool getOrdFare(char *clitel);

        char *strRes;
        DD_geo **geoRes;
        size_t geoReslen;

    protected:

    private:
        void freeRes();
        redisContext *_conn;
        redisReply *_reply;
};

#endif // DDREDIS_H
