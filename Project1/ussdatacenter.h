#pragma once
#pragma once
#include "cppheader.h"
#include "base_struct.h"
#include "ultrasound_def.h"
#include <boost/make_shared.hpp>
#include "poconvert.h"
#include "fileprocess.h"
/*
 * @brief ����ģʽ�����ڲ�������csv���ݵ�ģ�飬������ȡԭʼ�������ݣ�д��gt��������
 */
class UssdateCenter
{
public:
	UssdateCenter() {};
	~UssdateCenter() {};
	static UssdateCenter& Instance() ;
public:

/*
* @brief Ѱ��ÿ��ԭʼ�������ݵ�dr���ݣ���д���Ա����m_usspo
* @param ussfile ԭʼ��������·��
* @param polist �����״�.bin�ļ����ɵ�ts_dr�б�
* @return err info
*/
	FILEERR ReadUssPo(const std::string ussfile, boost::shared_ptr<std::map<TimestampType, TPose>> polist);

/*
* @brief ������궨�ĳ�������д�����csv��
* @param ussinfile ԭʼ��������·��
* @param ussoutfile ����궨�ĳ�������·��
* @param usslabelts ����궨�ĳ���ʱ���
* @return err info
*/
	FILEERR WriteUssLabel(const std::string ussinfile, const std::string ussoutfile,boost::shared_ptr<std::vector<TimestampType>> usslabelts);

/*
* @brief �������ts-dr�б�
*/
	void	Clear();

/*
* @brief ��ȡһ��ָ���Ա����m_usspo��ָ��
*/
	boost::shared_ptr<std::vector<tObjProperty3D>> GetUssProperty3D();
private:

/*
* @brief ��ȡ����dr��Ϣ
* @param ts ����ʱ���
* @param po �����dr��Ϣ
* @param polist �����״�.bin�ļ����ɵ�ts_dr�б�
* @return TimestampType ����ʱ���
*/
	TimestampType	GetPosebyTime(TimestampType ts,TPose &po, boost::shared_ptr<std::map<TimestampType, TPose>> polist);

/*
* @brief ������д������������д��csv
*/
	void Write2CSV(const ExtU_ultrasonic_algo_T *infoptr,std::string ussoutfile);
	void Write2CSV(const char *infoptr,std::string ussoutfile);
	void Write2CSV(const char *infoptr, std::string ussoutfile, float32_t stream_ts);

/*
* @brief ����USSDOWNSAMPLE���ã������������²���
*/
	void ussposample();
private:
	static UssdateCenter instance;

/*
* @brief ��Ա����������dr��Ϣ��verctor,ʱ���Ϊ����ʱ���
*/
	std::vector<tObjProperty3D> m_usspo;



};
