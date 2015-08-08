
#ifndef _QCA_SNIFFER_H_
#define _QCA_SNIFFER_H_

/** 
 * @brief: sniffer mode 
 * SCAN_CHANNEL_MODE��snifferǰɨ���ŵ���ֻ̽��ɨ�赽��AP�����ŵ�,�е����ܼӿ������ŵ����ٶ�
 * ALL_CHANNEL_MODE��ɨ�������ŵ���1~13�� 
*/
typedef enum  
{
	SCAN_CHANNEL_MODE = 1,			  
	ALL_CHANNEL_MODE				 
}tChannelMode_Type;

/** 
 * @brief: sniffer mode 
 * SCAN_CHANNEL_MODE��snifferǰɨ���ŵ���ֻ̽��ɨ�赽��AP�����ŵ�,�е����ܼӿ������ŵ����ٶ�
 * ALL_CHANNEL_MODE��ɨ�������ŵ���1~13�� 
*/
typedef enum  
{
	SNIFFER = 1,			  
	AIRKISS				 
}tSuccessMode_Type;


/** 
 * @brief: ģʽʹ�ܿ���
*/
typedef enum  
{
	DIS_ALL	= 0,	// �ر�snifferģʽ
	EN_ALL	= 1,	// ͬʱ����sniffer��airkissģʽ
	EN_SNIFFER,		// ������snifferģʽ
	EN_AIRKISS		// ������airkissģʽ
}tEnable_Type;


/** 
 * @brief:	sniffer�ɹ���ִ�еĻص�����ָ��
 * *ssid��		ssid
 * *password��	password
 * response��	��Ӧ��
 * tmode:		�ɹ�ģʽ	SNIFFER��response = 0(�ڲ�ר��), �ظ�find����
 *									response !=0������udp_sniffer_respond(6001, 10, &response, 1);
 *							AIRKISS������udp_sniffer_respond(10000, 10, &response, 1);
*/
typedef void (*sniffer_cb)(char *ssid, char *password, unsigned char response, tSuccessMode_Type tmode);


/**
***************************************************************************
*@brief		��	��ȡsniffer lib�汾��Ϣ
*@param[in]	��	void
*@return	��	none
*@warning	��
*@see		��
***************************************************************************
*/
char * qca_sniffer_get_version(void);

/**
***************************************************************************
*@brief		��	����sniffer
*@param[in]	��	mode��			snifferɨ��ģʽ
*				sniffer_func��	sniffer�ɹ���Ļص���
*@return	��	none
*@see		��	
***************************************************************************
*/
void qca_sniffer_start(tChannelMode_Type mode, sniffer_cb sniffer_func);

/**
***************************************************************************
*@brief		��	set sniffer/airkiss enable/disable status
*@param[in]	��	tEnMode		ʹ��/��ֹ snifferģʽ��airkissģʽ
*@return	��	none
*@warning	��
*@see		��	����������ʹ�ܣ����ֹ��sniffer����, ��ʱ��Ч
*				Ĭ��tEnMode = EN_ALL
***************************************************************************
*/
void qca_set_sniffer_en(tEnable_Type tEnMode);

/**
***************************************************************************
*@brief		��	�����߳��ж��Ƿ���Ҫ�����߳�
*@param[in]	��	0	������
*				1	����
*@return	��	none
*@see		��	sniffer�ؼ�ʱ�������߳���ù�������Ӱ��snifferЧ��
*				��֪��������������ɨ��AP,��Ϊɨ��AP��Ҫ�����һᵼ��sniffer
*				����������������, ɨ��AP���Ե��ú�����qca_sniffer_check_ap()��
***************************************************************************
*/
int qca_get_thread_suspend(void);

/**
***************************************************************************
*@brief		��	�ж�AP�Ƿ����
*@param[in]	��	*ssid
*@return	��	0	�ҵ�
*				-1  δ�ҵ�
*@see		��	������stationģʽʱ����AP��ʱ�����������smart linkģʽ��
*				��ͨ���˽ӿں������AP�Ƿ���ڣ��������Ƿ����stationģʽ
***************************************************************************
*/
int qca_sniffer_check_ap(char *ssid);


/**
***************************************************************************
*@brief		��	�ظ�sniffer/airkiss��Ӧ
*@param[in]	��	port	�˿ںţ�Airkiss��10000��
*				count	�ظ�����
*				*datas	������ʼ��ַ
*				length	���ݳ���
*@return	��	
*@see		��	
***************************************************************************
*/
int udp_sniffer_response(int port, int count, char *data, int length);

#endif

