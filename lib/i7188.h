// compat

#include <stdlib.h>
#include <stdarg.h>

void *__cdecl __saveregs malloc_wrapper(unsigned size)
{
    return malloc(size);
}
#pragma aux malloc_wrapper "_malloc"

void __cdecl __saveregs free_wrapper(void *ptr)
{
    free(ptr);
}
#pragma aux free_wrapper "_free"

// unsigned char _8087 = 0;
// unsigned char _real87 = 0;

extern int Borland_vsprintf(char *__s, const char *__format, __va_list __arg);
#pragma aux(__cdecl) Borland_vsprintf "_vsprintf"

extern int OW_vsprintf(char *__s, const char *__format, __va_list __arg);
#pragma aux OW_vsprintf "vsprintf_"

int Borland_vsprintf(char *s, const char *format, __va_list arg)
{
    return (OW_vsprintf(s, format, arg));
}

// compat

#define IN_BUF_SIZE 1024

typedef unsigned int uint;
typedef unsigned int WORD;
typedef unsigned char uchar;
typedef unsigned char BYTE;
typedef unsigned long ulong;
typedef unsigned long DWORD;

#define NoError 0
#define InitPinIsOpen 0
#define InitPinIsNotopen 1
#define QueueIsEmpty 0
#define QueueIsNotEmpty 1
#define PortError -1
#define DataError -2
#define ParityError -3
#define StopError -4
#define TimeOut -5
#define QueueEmpty -6
#define QueueOverflow -7
#define PosError -8
#define AddrError -9
#define BlockError -10
#define WriteError -11
#define SegmentError -12
#define BaudRateError -13
#define CheckSumError -14
#define ChannelError -15
#define BaudrateError -16
#define TriggerLevelError -17
#define DateError -18
#define TimeError -19
#define TimeIsUp 1

#ifndef __FILE_DATA__
#define __FILE_DATA__
typedef struct
{
    unsigned mark; /* 0x7188 -> is file */
    unsigned char fname[12];
    unsigned char year;
    unsigned char month;
    unsigned char day;
    unsigned char hour;
    unsigned char minute;
    unsigned char sec;
    unsigned long size;
    char far *addr;
    unsigned CRC;
    unsigned CRC32;
} FILE_DATA;
#endif

#define SEND_CMD(port, cmd, timeout, checksum) SendCmdTo7000(port, cmd, checksum)
#define RECEIVE_CMD ReceiveResponseFrom7000

extern char hex_to_ascii[16];

#ifdef __cplusplus
extern "C"
{
#endif

    void __cdecl InitLib(void);
    int __cdecl InstallCom(int port, unsigned long baud, int data, int parity, int stop);
    int __cdecl InstallCom3(unsigned long baud, int data, int parity);
    int __cdecl InstallCom4(unsigned long baud, int data, int parity);
    int __cdecl RestoreCom(int port);
    int __cdecl RestoreCom3(void);
    int __cdecl RestoreCom4(void);
    int __cdecl IsCom(int port);
    int __cdecl IsCom3(void);
    int __cdecl IsCom4(void);
    int __cdecl ReadCom(int port);
    int __cdecl ReadCom3(void);
    int __cdecl ReadCom4(void);
    int __cdecl ToCom(int port, int data);
    int __cdecl ToCom3(int data);
    int __cdecl ToCom4(int data);
    int __cdecl ToComBufn(int port, char *buf, int no);
    int __cdecl ToCom3Bufn(char *buf, int no);
    int __cdecl ToCom4Bufn(char *buf, int no);
    int __cdecl ToComStr(int port, char *str);
    int __cdecl ToCom3Str(char *str);
    int __cdecl ToCom4Str(char *str);
    int __cdecl ClearCom(int port);
    int __cdecl ClearCom3(void);
    int __cdecl ClearCom4(void);
    int __cdecl WaitTransmitOver(int port);
    int __cdecl WaitTransmitOver3(void);
    int __cdecl WaitTransmitOver4(void);

    int __cdecl ReadInitPin(void);
    void __cdecl LedOff(void);
    void __cdecl LedOn(void);
    void __cdecl Init5DigitLed(void);
    int __cdecl Show5DigitLed(int position, int value);
    int __cdecl Show5DigitLedSeg(int pos, unsigned char data);
    void __cdecl DelayTimeMs(unsigned int time);

    int __cdecl ReadNVRAM(int addr);
    int __cdecl WriteNVRAM(int addr, int data);

    int __cdecl WriteEEP(int block, int addr, int data);
    int __cdecl ReadEEP(int block, int addr);
    void __cdecl EnableEEP(void);
    void __cdecl ProtectEEP(void);

    void __cdecl EnableWDT(void);
    void __cdecl RefreshWDT(void);
    void __cdecl DisableWDT(void);

    int __cdecl FlashReadId(void);
    int __cdecl FlashWrite(unsigned int seg, unsigned int offset, char data);
    int __cdecl FlashErase(unsigned int seg);
    int __cdecl FlashRead(unsigned int seg, unsigned int offset);

    void __cdecl Delay(unsigned ms);
    void __cdecl Delay_1(unsigned ms);

    int __cdecl Is7188(void);
    int __cdecl Getch(void);
    int __cdecl Kbhit(void);
    int __cdecl Ungetch(int key);
    void __cdecl Putch(int data);
    void __cdecl Puts(char *str);
    int __cdecl Print(char *fmt, ...);

    int __cdecl ascii_to_hex(char ascii);
    int __cdecl SendCmdTo7000(int iPort, unsigned char *cCmd, int iChksum);
    int __cdecl ReceiveResponseFrom7000(int iPort, unsigned char *cCmd, long lTimeout, int iChksum);

    // void  __cdecl far *_MK_FP(unsigned segment,unsigned offset);
    int __cdecl IsResetByWatchDogTimer(void);
    int __cdecl IsResetByPowerOff(void); /* for bios date 12/12/98 or later */

    int __cdecl Show5DigitLedWithDot(int pos, int data);
    void __cdecl Set5DigitLedTestMode(int mode);
    void __cdecl Set5DigitLedIntensity(int mode);
    void __cdecl Disable5DigitLed(void);
    void __cdecl Enable5DigitLed(void);
    unsigned __cdecl GetLibVersion(void);

    /* 01/07/1999  Add Timer function */
    int __cdecl TimerOpen(void);
    int __cdecl TimerClose(void);
    void __cdecl TimerResetValue(void);
    unsigned long __cdecl TimerReadValue(void);
    void __cdecl DelayMs(unsigned t);
    int __cdecl StopWatchReset(int channel);
    int __cdecl StopWatchStart(int channel);
    int __cdecl StopWatchStop(int channel);
    int __cdecl StopWatchPause(int channel);
    int __cdecl StopWatchContinue(int channel);
    int __cdecl StopWatchReadValue(int channel, unsigned long *value);
    int __cdecl CountDownTimerStart(int channel, unsigned long count);
    int __cdecl CountDownTimerReadValue(int channel, unsigned long *value);
    void __cdecl InstallUserTimer(void (*fun)(void));
    void __cdecl InstallUserTimer1C(void (*fun)(void));

    int __cdecl DataSizeInCom(int port);
    int __cdecl DataSizeInCom3(void);
    int __cdecl DataSizeInCom4(void);
    /* New for Ver 1.13 */
    /* 07-23-1999 add 4 function for COM1 /DTR,/RTS output pins */
    void __cdecl SetRtsActive(void);
    void __cdecl SetRtsInactive(void);

    /* [New for Ver 1.14] */
    /**** 07/27/1999 add 5 function for COM1/2/3/4 formated output ****/
    int __cdecl printCom(int port, char *fmt, ...);
    int __cdecl printCom3(char *fmt, ...);
    int __cdecl printCom4(char *fmt, ...);
    /* 08/06/1999 add 2 function for COM1 CTS,DSR input pins */
    int __cdecl GetCtsStatus(void);

    /* 08/25/1999 add 5 function for COM1-4 */
    int __cdecl IsTxBufEmpty(int port);
    int __cdecl IsTxBufEmpty3(void);
    int __cdecl IsTxBufEmpty4(void);
    int __cdecl IsCom3OutBufEmpty(void);
    int __cdecl IsCom4OutBufEmpty(void);

    /* 10/19/1999 add 5 function for COM1/2/3/4 change baudrate */
    int __cdecl SetBaudrate(int port, unsigned long baud);
    int __cdecl SetBaudrate3(unsigned long baud);
    int __cdecl SetBaudrate4(unsigned long baud);

    /* 10/20/1999 */
    /* (1) add 10 function for COM1/2/3/4 send/detect BREAK signal */
    int __cdecl SendBreak(int port, unsigned timems);
    void __cdecl SendBreak3(unsigned timems);
    void __cdecl SendBreak4(unsigned timems);
    int __cdecl IsDetectBreak(int port);
    int __cdecl IsDetectBreak3(void);
    int __cdecl IsDetectBreak4(void);

    /* (2) Add 3 functions for clear COM1/2/3/4 output buffer */
    int __cdecl ClearTxBuffer(int port);
    void __cdecl ClearTxBuffer3(void);
    void __cdecl ClearTxBuffer4(void);

    /* 12/29/1999 */
    /*
      Add functions for ReadOnly file system of 7188R/7188X
    */
    int __cdecl GetFileNo(void);
    int __cdecl GetFileName(int no, char *fname);
    char far __cdecl *GetFilePositionByNo(int no);
    char far __cdecl *GetFilePositionByName(char *fname);
    FILE_DATA far __cdecl *GetFileInfoByNo(int no);        /* 04/11/2000 */
    FILE_DATA far __cdecl *GetFileInfoByName(char *fname); /* 04/11/2000 */

    /*
     02/15/2000
     Add functions for system DATE/TIME
    */
    void __cdecl GetTime(int *hour, int *minute, int *sec);
    int __cdecl SetTime(int hour, int minute, int sec);
    void __cdecl GetDate(int *year, int *month, int *day);
    int __cdecl SetDate(int year, int month, int day);

    void __cdecl ClockHighLow(void);
    void __cdecl ClockHigh(void);
    void __cdecl ClockLow(void);

    /*
     03/15/2000
     Add function Scanf ...
    */
    int __cdecl LineInput(char *buf, int maxlen);            /* input one line from StdInput */
    void __cdecl ResetScanBuffer(void);                      /* Set Scanf to use default buffer(maxlen=80) */
    void __cdecl SetScanBuffer(unsigned char *buf, int len); /* Set user's buffer for Scanf*/
    int __cdecl Scanf(char *fmt, ...);                       /* like C's scanf */

    /*
     06/09/2000
     Add function for COM3/COM4
      COM3 for 7522/7523 only
      COM4 for 7523 only
    */
    int __cdecl Set485DirToTransmit(int port);
    int __cdecl Set485DirToReceive(int port);
    void __cdecl SetCom2AutoDir(void);
    void __cdecl ResetCom2AutoDir(void);
    void __cdecl SetCom1AutoDir(void);
    void __cdecl ResetCom1AutoDir(void);

    int __cdecl InstallCom1(unsigned long baud, int data, int parity, int stop);
    int __cdecl RestoreCom1(void);
    int __cdecl IsCom1(void);
    int __cdecl ToCom1(int data);
    int __cdecl ToCom1Str(char *str);
    int __cdecl ToCom1Bufn(char *buf, int no);
    int __cdecl printCom1(char *fmt, ...);
    void __cdecl ClearTxBuffer1(void);
    int __cdecl SetCom1FifoTriggerLevel(int level);
    int __cdecl SetBaudrate1(unsigned long baud);
    int __cdecl ReadCom1(void);
    int __cdecl ClearCom1(void);
    int __cdecl DataSizeInCom1(void);
    int __cdecl WaitTransmitOver1(void);
    int __cdecl IsTxBufEmpty1(void);
    int __cdecl IsCom1OutBufEmpty(void);
    void __cdecl SetDtrActive1(void);
    void __cdecl SetDtrInactive1(void);
    void __cdecl SetRtsActive1(void);
    void __cdecl SetRtsInactive1(void);
    int __cdecl GetCtsStatus1(void);
    int __cdecl GetDsrStatus1(void);

    int __cdecl InstallCom2(unsigned long baud, int data, int parity, int stop);
    int __cdecl RestoreCom2(void);
    int __cdecl IsCom2(void);
    int __cdecl ToCom2(int data);
    int __cdecl ToCom2Str(char *str);
    int __cdecl ToCom2Bufn(char *buf, int no);
    int __cdecl printCom2(char *fmt, ...);
    void __cdecl ClearTxBuffer2(void);
    int __cdecl SetCom2FifoTriggerLevel(int level);
    int __cdecl SetBaudrate2(unsigned long baud);
    int __cdecl ReadCom2(void);
    int __cdecl ClearCom2(void);
    int __cdecl DataSizeInCom2(void);
    int __cdecl WaitTransmitOver2(void);
    int __cdecl IsTxBufEmpty2(void);
    int __cdecl IsCom2OutBufEmpty(void);

    /*
      06/15/2000
     Add function for COM3
      COM3 for 7522/7523 only
    */
    void __cdecl SetRtsActive1(void);
    void __cdecl SetRtsInactive1(void);
    int __cdecl GetCtsStatus1(void);

    /*
     10/16/2000  start Ver 1.17
     Add new EEPROM functions
    */
    void __cdecl EE_WriteEnable(void);
    void __cdecl EE_WriteProtect(void);
    int __cdecl EE_RandomRead(int Block, int Addr);
    int __cdecl EE_ReadNext(int Block);
    int __cdecl EE_MultiRead(int StartBlock, int StartAddr, int no, char *databuf);
    int __cdecl EE_RandomWrite(int Block, int Addr, int Data);
    int __cdecl EE_MultiWrite(int Block, int Addr, int no, char *Data);

    /*
     11/20/2000  start Ver 1.18
    */
    void __cdecl LedToggle(void); /* 11/20/2000 Add */
#ifndef __MEMMAP__
#define __MEMMAP__
    typedef struct
    {
        int type;
        unsigned addr;
        unsigned word;
    } MemMap;
#endif
    void __cdecl InstallCom3ForTouch200(void);
    void __cdecl RestoreCom3ForTouch200(void);
    void __cdecl ToTouch(int type, int addr, unsigned data);
    int __cdecl IsTouch(void);
    MemMap __cdecl *ReadTouch(void);

/*
 08/01/2001
 Add new timer functions
*/
/* for StopWatch [�p�ɽX��] */
#ifndef _T_STOPWATCH_
#define _T_STOPWATCH_
    typedef struct
    {
        ulong ulStart, ulPauseTime;
        uint uMode; /* 0: pause, 1:run(start) */
    } STOPWATCH;
#endif

    void __cdecl T_StopWatchStart(STOPWATCH *sw);
    ulong __cdecl T_StopWatchGetTime(STOPWATCH *sw);
    void __cdecl T_StopWatchPause(STOPWATCH *sw);
    void __cdecl T_StopWatchContinue(STOPWATCH *sw);

/* For CountDown Timer[�˼ƭp��] */
#ifndef _T_COUNTDOWNTIMER_
#define _T_COUNTDOWNTIMER_
    typedef struct
    {
        ulong ulTime, ulStartTime, ulPauseTime;
        uint uMode; /* 0: pause, 1:run(start) */
    } COUNTDOWNTIMER;
#endif

    void __cdecl T_CountDownTimerStart(COUNTDOWNTIMER *cdt, ulong timems);
    void __cdecl T_CountDownTimerPause(COUNTDOWNTIMER *cdt);
    void __cdecl T_CountDownTimerContinue(COUNTDOWNTIMER *cdt);
    int __cdecl T_CountDownTimerIsTimeUp(COUNTDOWNTIMER *cdt);
    ulong __cdecl T_CountDownTimerGetTimeLeft(COUNTDOWNTIMER *cdt);
    extern unsigned long __cdecl far *TimeTicks;

#ifdef __cplusplus
}
#endif
