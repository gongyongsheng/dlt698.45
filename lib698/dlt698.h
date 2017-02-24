

#ifndef DLT698_H_
#define DLT698_H_
#include "Objectdef.h"

extern int doObjectAction(OAD oad,INT8U *data);
extern int StateProcess(CommBlock* nst, int delay_num);
extern int ProcessData(CommBlock *com);
extern int Link_Request(LINK_Request request,INT8U *addr,INT8U *buf);
extern void testframe(INT8U *apdu,int len);
extern int  create_OAD(INT8U *data,OAD oad);
extern INT8U Report_Event(CommBlock *com,Reportevent report_event);
/*----------------------抄表相关*************************/
INT16S composeProtocol698_GetRequest(INT8U*,CLASS_6015,TSA);

int createFile(const char * path, int length, unsigned char crc, unsigned short bs);
int appendFile(int shift, int length, unsigned char *buf);
#endif
