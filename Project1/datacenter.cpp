#include "lidardatacenter.h"
#include "argumentpass.h"
LidardateCenter LidardateCenter::instance;

LidardateCenter& LidardateCenter::Instance()
{
	return instance;
}

void LidardateCenter::ReadLidarPointClouds(const std::string lidarpointclouds, const int skipline)
{
	std::ifstream lidarfile(lidarpointclouds);

	if (lidarfile.is_open())
	{
		std::string line;

		while (std::getline(lidarfile, line))
		{
			pcl::PointXYZI lidarpoint;
			std::vector<std::string> token = splitstring(line);
			lidarpoint.x = std::stof(token[0]);
			lidarpoint.y = std::stof(token[1]);
			lidarpoint.z = std::stof(token[2]);
			lidarpoint.intensity = std::stoi(token[3]);
			m_cloud.push_back(lidarpoint);
		}


		std::cout << "lidar data count :" << m_cloud.size() << std::endl;
	}
	lidarfile.close();
}

void LidardateCenter::ReadLidarPointClouds(align_lidar_pair lidarpointclouds)
{
	//m_cloud.clear();
	readunilaterallidar(lidarpointclouds.first.pos, lidarpointclouds.first);
	readunilaterallidar(lidarpointclouds.second.pos, lidarpointclouds.second);
}

pcl::PointCloud<pcl::PointXYZI>::Ptr LidardateCenter::GetLidarClouds()
{
	return boost::make_shared<pcl::PointCloud<pcl::PointXYZI>>(m_cloud);
}

void LidardateCenter::Clear()
{
	m_cloud.clear();
}

std::vector<std::string> LidardateCenter::splitstring(const std::string & str)
{
	std::vector<std::string> res;
	std::stringstream ss(str);
	std::string token;

	while (std::getline(ss, token, ',')) {
		res.push_back(token);
	}

	return res;

}

bool LidardateCenter::IsInFov(const PointT lidarpoint_v)
{
	if (ArgumentPass::Instance().IsRoadTrafficStone)
	{
		return (std::fabs(lidarpoint_v.x) <= LIDARXYFOV && std::fabs(lidarpoint_v.y) <= LIDARXYFOV && lidarpoint_v.z <= LIDARZFOV );
	}
	else
	{
		return (std::fabs(lidarpoint_v.x) <= LIDARXYFOV && std::fabs(lidarpoint_v.y) <= LIDARXYFOV && lidarpoint_v.z <= LIDARZFOV && lidarpoint_v.z > 0);
	}
}
//��ȡ���߼����״�����bin
//���룺 label ���״�/���״�
//      fileinfo ��������Bin�ļ�
void LidardateCenter::readunilaterallidar(std::string label, LidarFileInfo &fileinfo)
{
	std::string lidarpointclouds = fileinfo.filepath;
	TPose vehpose = fileinfo.po;
	LidarIndex index = (label == LEFTLIDARFOLDER) ? LEFTLidar : RIGHTLidar;

	std::ifstream lidarfile(lidarpointclouds);
	if (lidarfile.is_open())
	{
		lidarfile.seekg(0, lidarfile.end);
		unsigned int len = lidarfile.tellg();
		lidarfile.seekg(0, lidarfile.beg);

		std::size_t cloudsize = len / sizeof(PointT);

		//std::cout << label<< ", "<<
		//	".bin len:"<<len << ", " 
		//	"PointT size: "<< sizeof(PointT) << ", " 
		//	"cloud size: "<< cloudsize << std::endl;

		char *buffer = new char[len];
		lidarfile.read(buffer, len);
		char *slidptr = buffer;
		//pcl::PointCloud<pcl::PointXYZI>::Ptr cloudtmp(new pcl::PointCloud<pcl::PointXYZI>);
		for (int i = 0; i < cloudsize; i++)
		{
			//�����Ϊ��������ϵ
			PointT lidarcloud = { 0 };
			memcpy(&lidarcloud, slidptr, sizeof(PointT));
			slidptr += sizeof(PointT);
			//ת��Ϊ�Գ�����,���ݱ궨�ļ�
			PointT lidarpoint_v = lidarconvert.trans2V(index, lidarcloud);
			//�ж��Ƿ��ڼ���fov��
			if (IsInFov(lidarpoint_v))//20m *20m
			{
				//ת��Ϊȫ������
				TPoint lidarpoint_v_xy = { lidarpoint_v.x,lidarpoint_v.y };
				TPoint lidarpoint_w_xy = poconvert.trans2W(lidarpoint_v_xy, vehpose);

				pcl::PointXYZI lidarpoint;
				lidarpoint.x = lidarpoint_w_xy.x;
				lidarpoint.y = lidarpoint_w_xy.y;
				lidarpoint.z = lidarpoint_v.z;
				lidarpoint.intensity = lidarpoint_v.intensity;
				m_cloud.push_back(lidarpoint);
			}
		}
#if 0
		std::cout << "cloud before seg " << cloudtmp->size() << std::endl;
		CSegHandler seghandler;
		seghandler.planeseg(cloudtmp);
		std::cout << "cloud after seg " << cloudtmp->size() << std::endl;
		m_cloud = m_cloud + *cloudtmp;
		std::cout << "cloud total " << m_cloud.size() << std::endl;
#endif

	}
	lidarfile.close();

}
