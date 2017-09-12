

#ifndef READ485_H_
#define READ485_H_
#include "Objectdef.h"
#include "PublicFunction.h"
#include "AccessFun.h"
#include "dlt698.h"
#include "dlt645.h"
#include "event.h"
#include "cjsave.h"
#include "libmmq.h"

#include "show_ctrl.h"
#define BUFFSIZE128 128
#define BUFFSIZE256 256
#define BUFFSIZE512 512
#define BUFFSIZE1024 1024
#define BUFFSIZE2048 2048
#define DATA_CONTENT_LEN 1024
#define NUM_07DI_698OAD 100

#define DF07_BYTES  4
#define DF07_INFO_BYTES  50
#define MAXLEN_1LINE  100
#define CLASS_601F_CFG_FILE "/nor/config/07DI_698OAD.cfg"
#define REPLENISHFILEPATH "/nand/replenish.dat"
#define PARA_CHANGE_RETVALUE  -1

#define MAX_RETRY_NUM 1 //抄表失败重试次数

#define TSA_OI 0x202a
#define DATA_TIMESTAMP_OI 0x2021
#define EVENT_INDEX_OI 0x2022
#define EVENTSTART_TIME_OI 0x201e
#define EVENTSTART_END_OI 0x2020

#define SAVE_EVENT_BUFF_HEAD_LEN 39
pthread_attr_t read485_attr_t;
int thread_read4851_id,thread_read4852_id;           //485、四表合一（I型、II型、专变）
pthread_t thread_read4851,thread_read4852;

typedef struct
{
	INT16U sernum;
	TSA addr;			//通信地址
	INT8U baud;			//波特率
	METER_PROTOCOL protocol;		//规约类型
	INT8U port;			//端口
}BasicInfo6001;
//OAD+数据
typedef struct
{
	OAD oad;
	INT8U datalen;
	INT8U data[50];
}OAD_DATA;


extern void read485_proccess();

mqd_t mqd_485_1_task;
mqd_t mqd_485_2_task;
mqd_t mqd_zb_task;
struct mq_attr attr_485_main;
struct mq_attr attr_485_1_task;
struct mq_attr attr_485_2_task;

INT32S comfd485[2];
INT8U i485port1;
INT8U readState;//是否正抄停上电事件－抄停上电事件的时候需要暂停正常抄表流程
INT8U i485port2;
INT8U isNeed4852;//0-4852维护口　1-4852抄表口
//698 OAD 和 645 07规约 数据标识对应关系
INT8U map07DI_698OAD_NUM;
CLASS_601F map07DI_698OAD[NUM_07DI_698OAD];


INT16S request9707_singleOAD(INT8U protocol,OI_698 roadOI,OAD soureOAD,CLASS_6001 to6001,CLASS_6035* st6035,INT8U* dataContent,INT8U port485);
INT16S deal6015_698(CLASS_6015 st6015, CLASS_6001 to6001,CLASS_6035* st6035,INT8U* dataContent,INT8U port485);
INT16U compose6012Buff(DateTimeBCD startTime,DateTimeBCD saveTime,TSA meterAddr,INT16U dataLen,INT8U* dataContent, INT8U port485);
INT8U getSaveTime(DateTimeBCD* saveTime,INT8U cjType,INT8U saveTimeFlag,DATA_TYPE curvedata);

#endif /* READ485_H_ */
