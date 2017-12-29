#ifndef DRVINFO_H
#define DRVINFO_H


class DrvInfo
{
public:
    static DrvInfo* getDrvInfo();
    char tel[12];
    char nickname[24];
    char card[20];
    char bal[12];
    char clitel[12];
    char clinickname[24];
    char fare[8];

private:
    DrvInfo();
    DrvInfo(const DrvInfo&);
    DrvInfo& operator=(const DrvInfo&);
    static DrvInfo* info;
};

#endif // DRVINFO_H
