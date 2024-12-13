#include "ussdatacenter.h"
#define READBUFFSIZE 10000
#define CSVDATASIZE 4144
#define FRAMETOTAL 8000

UssdateCenter UssdateCenter::instance;
UssdateCenter& UssdateCenter::Instance()
{
	return instance;
}
FILEERR UssdateCenter::ReadUssPo(const std::string ussfile, boost::shared_ptr<std::map<TimestampType, TPose>> polist)
{
	std::ifstream istrm(ussfile);
	if (!istrm.is_open())
	{
		std::cout << "uss file open error!" << std::endl;
		return FILEERR::ERROR_FREAD;
	}

	char readbuffer[READBUFFSIZE];
	uint32_t frame = 0;
	char *token = NULL;

	TimestampType now_interval;
	TimestampType max_interval = 0;
	while (istrm.peek() != EOF && frame < FRAMETOTAL)
	{
		memset(readbuffer, 0, sizeof(char));
		istrm.getline(readbuffer, READBUFFSIZE);

		static uint8_t csvdata[CSVDATASIZE];
		memset(csvdata,0,sizeof(uint8_t)*CSVDATASIZE);
		int fieldCount = 0;
		char *data = STRTOK(readbuffer, ",", token);
		while (fieldCount < CSVDATASIZE)
		{
			fieldCount++;
			if (fieldCount >= 3U)
			{
				if (fieldCount < 50U)
				{
					csvdata[fieldCount - 3U] = std::atoi(data);
				}
				else
				{
					csvdata[fieldCount + 1U] = std::atoi(data);
				}
			}
			data = STRTOK(token, ",", token);
		}
		ExtU_ultrasonic_algo_T UssSrcData;
		int size = sizeof(ExtU_ultrasonic_algo_T);
		memcpy(&UssSrcData, csvdata, sizeof(ExtU_ultrasonic_algo_T));
		TimestampType curts = UssSrcData.sObstacleInfoAll.u64Timestamp_us;
		tObjProperty3D  curusspo = { 0 };
		curusspo.u64Timestamp_us = curts;

		TPose curpose = { 0 };
		now_interval = GetPosebyTime(curts, curpose,polist);
		if (now_interval > max_interval)
		{
			max_interval = now_interval;
		}
		curusspo.f32X = curpose.x;
		curusspo.f32Y = curpose.y;
		curusspo.f32Yaw = curpose.theta;

		m_usspo.push_back(curusspo);
	
		frame++;

	}
	istrm.close();
	std::cout << "max interval :" << max_interval << std::endl;
	std::cout << "uss size£º" << m_usspo.size() << std::endl;
	ussposample();
	std::cout << "uss size after sample: " << m_usspo.size() << std::endl;
	return FILEERR::NOT_ERROR;
}

FILEERR UssdateCenter::WriteUssLabel(const std::string ussinfile, const std::string ussoutfile, boost::shared_ptr<std::vector<TimestampType>> usslabelts)
{
	std::ifstream istrm(ussinfile);
	if (!istrm.is_open())
	{
		std::cout << "uss file open error!" << std::endl;
		return FILEERR::ERROR_FREAD;
	}

	char readbuffer[READBUFFSIZE];
	uint32_t frame = 0;
	int needlabel = 0;
	char *token = NULL;
	while (istrm.peek() != EOF && frame < FRAMETOTAL)
	{
		memset(readbuffer, 0, sizeof(char));
		istrm.getline(readbuffer, READBUFFSIZE);
		char readbufferoriginal[READBUFFSIZE];
		memcpy(readbufferoriginal, readbuffer,sizeof(char) * READBUFFSIZE);

		static uint8_t csvdata[CSVDATASIZE];
		memset(csvdata, 0, sizeof(uint8_t)*CSVDATASIZE);
		int fieldCount = 0;
		char *data = STRTOK(readbuffer, ",", token);
		while (fieldCount < CSVDATASIZE)
		{
			fieldCount++;
			if (fieldCount >= 3U)
			{
				if (fieldCount < 50U)
				{
					csvdata[fieldCount - 3U] = std::atoi(data);
				}
				else
				{
					csvdata[fieldCount + 1U] = std::atoi(data);
				}
			}
			data = STRTOK(token, ",", token);
		}
		ExtU_ultrasonic_algo_T UssSrcData;
		memcpy(&UssSrcData, csvdata, sizeof(ExtU_ultrasonic_algo_T));

		if (std::find(usslabelts->begin(), usslabelts->end(), UssSrcData.sObstacleInfoAll.u64Timestamp_us) != usslabelts->end())
		{
			//Write2CSV(&UssSrcData, ussoutfile);
			Write2CSV(readbufferoriginal, ussoutfile,needlabel*0.05f);
			needlabel++;
		}

		frame++;

	}
	istrm.close();

	return FILEERR::NOT_ERROR;
}

void UssdateCenter::Clear()
{
	m_usspo.clear();
}

boost::shared_ptr<std::vector<tObjProperty3D>> UssdateCenter::GetUssProperty3D()
{
	return boost::make_shared<std::vector<tObjProperty3D>>(m_usspo);
}


TimestampType UssdateCenter::GetPosebyTime(TimestampType ts, TPose &po , boost::shared_ptr<std::map<TimestampType, TPose>> polist)
{ 
	TimestampType min_interval = ULLONG_MAX;
	TimestampType alignts = 0;
	for (auto apo : (*polist))
	{
		TimestampType interval = absoluteunsignedlonglong((long long)(ts - apo.first));
		if (interval < min_interval)
		{
			min_interval = interval;
			alignts = apo.first;
		}
	}

	po = (*polist)[alignts];
	return min_interval;
}

void UssdateCenter::Write2CSV(const ExtU_ultrasonic_algo_T * infoptr, std::string ussoutfile)
{
	int size = sizeof(ExtU_ultrasonic_algo_T);
	uint8 * ptr = (uint8 *)infoptr;

	std::ofstream out(ussoutfile, std::ios::app);

	if (out.is_open())
	{
		out << 0 << "," << size << ",";
		for (int i = 0; i < size - 1; i++)
		{
			uint8 * bytePtr = reinterpret_cast<uint8*>(ptr);
			uint8 byte = (*bytePtr);
			out << (int)byte << ",";
			ptr++;
		}
		uint8 * bytePtr_ = reinterpret_cast<uint8*>(ptr);
		uint8 byte_ = (*bytePtr_);
		out << (int)byte_ << std::endl;
	}
	out.close();
}

void UssdateCenter::Write2CSV(const char * infoptr,  std::string ussoutfile)
{
	uint8 * ptr = (uint8 *)infoptr;

	std::ofstream out(ussoutfile, std::ios::app);

	if (out.is_open())
	{
		while ((*ptr) != '\0')
		{
			if ((*ptr) != ',')
			{
				out << (*ptr) ;
			}
			else
			{
				out << ",";
			}
			ptr++;
		}
		out << "\n" ;

	}
	out.close();
}

void UssdateCenter::Write2CSV(const char * infoptr, std::string ussoutfile, float32_t stream_ts)
{
	uint8 * ptr = (uint8 *)infoptr;

	std::ofstream out(ussoutfile, std::ios::app);

	if (out.is_open())
	{
		out << stream_ts;
		ptr++;
		while ((*ptr) != '\0')
		{
			if ((*ptr) != ',')
			{
				out << (*ptr);
			}
			else
			{
				out << ",";
			}
			ptr++;
		}
		out << "\n";

	}
	out.close();
}

void UssdateCenter::ussposample()
{
	float32_t odo = 0;
	auto m_usspocopy = m_usspo;
	m_usspo.clear();
	m_usspo.push_back(m_usspocopy[0]);

	for (int i = 1;i< m_usspocopy.size();i++)
	{
		odo += sqrt(pow((m_usspocopy[i].f32X - m_usspocopy[i - 1].f32X), 2) + pow((m_usspocopy[i].f32Y - m_usspocopy[i - 1].f32Y), 2));
		if (odo > USSDOWNSAMPLE)//if(odo >= USSDOWNSAMPLE)
		{
			m_usspo.push_back(m_usspocopy[i]);
			odo = 0.0f;
		}
		
	}

}
