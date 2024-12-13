#pragma once
#pragma once
#include "cppheader.h"
#include "base_struct.h"
#include "ultrasound_def.h"
#include <boost/make_shared.hpp>
#include "poconvert.h"
#include "fileprocess.h"
/*
 * @brief 单例模式，用于操作超声csv数据的模块，包括读取原始超声数据，写入gt超声数据
 */
class UssdateCenter
{
public:
	UssdateCenter() {};
	~UssdateCenter() {};
	static UssdateCenter& Instance() ;
public:

/*
* @brief 寻找每条原始超声数据的dr数据，并写入成员变量m_usspo
* @param ussfile 原始超声数据路径
* @param polist 激光雷达.bin文件生成的ts_dr列表
* @return err info
*/
	FILEERR ReadUssPo(const std::string ussfile, boost::shared_ptr<std::map<TimestampType, TPose>> polist);

/*
* @brief 将参与标定的超声数据写入输出csv中
* @param ussinfile 原始超声数据路径
* @param ussoutfile 参与标定的超声数据路径
* @param usslabelts 参与标定的超声时间戳
* @return err info
*/
	FILEERR WriteUssLabel(const std::string ussinfile, const std::string ussoutfile,boost::shared_ptr<std::vector<TimestampType>> usslabelts);

/*
* @brief 清除超声ts-dr列表
*/
	void	Clear();

/*
* @brief 获取一个指向成员变量m_usspo的指针
*/
	boost::shared_ptr<std::vector<tObjProperty3D>> GetUssProperty3D();
private:

/*
* @brief 获取超声dr信息
* @param ts 超声时间戳
* @param po 输出的dr信息
* @param polist 激光雷达.bin文件生成的ts_dr列表
* @return TimestampType 激光时间戳
*/
	TimestampType	GetPosebyTime(TimestampType ts,TPose &po, boost::shared_ptr<std::map<TimestampType, TPose>> polist);

/*
* @brief 函数重写，将超声数据写入csv
*/
	void Write2CSV(const ExtU_ultrasonic_algo_T *infoptr,std::string ussoutfile);
	void Write2CSV(const char *infoptr,std::string ussoutfile);
	void Write2CSV(const char *infoptr, std::string ussoutfile, float32_t stream_ts);

/*
* @brief 根据USSDOWNSAMPLE配置，将超声数据下采样
*/
	void ussposample();
private:
	static UssdateCenter instance;

/*
* @brief 成员变量，超声dr信息的verctor,时间戳为超声时间戳
*/
	std::vector<tObjProperty3D> m_usspo;



};
