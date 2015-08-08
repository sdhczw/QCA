/*
  * Copyright (c) 2013 Qualcomm Atheros, Inc..
  * All Rights Reserved.
  * Qualcomm Atheros Confidential and Proprietary.
  */
#include <qcom_common.h>
#include <qcom_system.h>
#include <threadx/tx_api.h>
#include <qcom_cli.h>
#include <Base.h>
#include <qcom_scan.h>

#include <zc_qca_adpter.h>


TX_THREAD g_struCloudThread;

TX_BYTE_POOL pool;

#define BYTE_POOL_SIZE (5*1024)
#define PSEUDO_HOST_STACK_SIZE (4 * 1024)   /* small stack for pseudo-Host thread */
extern void QC_Init(void); 
extern void user_pre_init(void);
extern void QC_Cloudfunc(ULONG which_thread);

extern void QC_CloudUartfunc(unsigned int which_thread);

extern int qcom_task_start(void (*fn) (unsigned int), unsigned int arg, int stk_size, int tk_ms);

void user_main(void)
{
    int i;
    CHAR *pointer;
    user_pre_init();
    //console_setup();
    QC_Init();

    tx_byte_pool_create(&pool, "cdrtest pool", TX_POOL_CREATE_DYNAMIC, BYTE_POOL_SIZE);
    tx_byte_allocate(&pool, (VOID **) & pointer, PSEUDO_HOST_STACK_SIZE, TX_NO_WAIT);

    tx_thread_create(&g_struCloudThread, "QC_Cloudfunc", QC_Cloudfunc, i, pointer, PSEUDO_HOST_STACK_SIZE, 16, 16, 4, TX_AUTO_START);
    qcom_task_start(QC_CloudUartfunc, 2, 3072, 50);
}


