#include "fileprocess.h"
#include "argumentpass.h"
/*
解析激光bin文件名，将左右激光雷达的时间戳对齐，解析文件的时间戳、Dr信息，
根据里程对bin文件下采样，放到成员变量m_lidarfilelist中
参数:

返回值:

*/
void FileProcess::Process()
{
	//解析左雷达bin文件名
	std::string leftlidarfolderpath = ArgumentPass::Instance().LIDARFOLDE_arg;
	leftlidarfolderpath = leftlidarfolderpath + "/" + LEFTLIDARFOLDER;
	std::vector<LidarFileInfo> leftlidarfile;
	readlidarfolder(leftlidarfolderpath, LEFTLIDARFOLDER,leftlidarfile);
	//解析右雷达bin文件名
	std::string rightlidarfolderpath = ArgumentPass::Instance().LIDARFOLDE_arg;
	rightlidarfolderpath = rightlidarfolderpath + "/" + RIGHTLIDARFOLDER;
	std::vector<LidarFileInfo> rightlidarfile;
	readlidarfolder(rightlidarfolderpath, RIGHTLIDARFOLDER, rightlidarfile);
	//左右雷达时间戳对齐
	for (auto left : leftlidarfile)
	{
		m_lidarfilelist.push_back(lidarTsAlignment(left, rightlidarfile));
	}
	std::cout << "total file count: " << m_lidarfilelist.size() << std::endl;
	//根据里程下采样，每0.5m取一个激光数据
	lidarfiledownsampling();

	std::cout << "down sample file count: " << m_lidarfilelist.size() << std::endl;
	
	
}

boost::shared_ptr<std::vector<align_lidar_pair>> FileProcess::GetLidarAlignFileList()
{
	return boost::make_shared<std::vector<align_lidar_pair>>(m_lidarfilelist);
}

boost::shared_ptr<std::map<TimestampType, TPose>> FileProcess::GetPoMap()
{
	return boost::make_shared<std::map<TimestampType, TPose>>(m_po);
}

void FileProcess::readlidarfolder(const std::string folderpath,const std::string label ,std::vector<LidarFileInfo>& lidarinfo)
{
	boost::filesystem::path directory(folderpath);

	if (boost::filesystem::exists(directory) && boost::filesystem::is_directory(directory)) {
		for (boost::filesystem::directory_entry& entry : boost::filesystem::directory_iterator(directory)) {
			if (boost::filesystem::is_regular_file(entry.path())) {
				LidarFileInfo afile ;
				memset(&afile,0,sizeof(LidarFileInfo));
				std::string filename = entry.path().filename().string();
				afile.filepath = folderpath + "/" + filename;
				afile.pos = (std::string) label;
				getlidarinfo(filename, afile.ts, afile.po);
				lidarinfo.push_back(afile);
				m_po.insert(std::make_pair(afile.ts, afile.po));
			}
		}
	}
	else {
		std::cerr << "Directory does not exist or is not a directory" << std::endl;
	}

	
}

std::string FileProcess::removeFileExtension(const std::string & filename)
{
	size_t dotPos = filename.find_last_of('.');
	if (dotPos != std::string::npos) {
		return filename.substr(0, dotPos);
	}
	return filename;
}

TimestampType FileProcess::getlidarinfo(const std::string filename, TimestampType &ts, TPose &po)
{
	std::string  basename = removeFileExtension(filename);
	std::vector <std::string> tokens;
	std::stringstream ss(basename);
	std::string token;
	while (std::getline(ss, token, '_'))
	{
		tokens.push_back(token);
	}

	ts = std::stoull(tokens[0]);
	po.x = std::stof(tokens[1]);
	po.y = std::stof(tokens[2]);
	po.theta = std::stof(tokens[3]);
	
	return ts;
}

align_lidar_pair FileProcess::lidarTsAlignment(const LidarFileInfo left, const std::vector<LidarFileInfo>& rightlist)
{
	LidarFileInfo align_right;
	memset(&align_right, 0, sizeof(LidarFileInfo));
	TimestampType min_interval = ULLONG_MAX;
	for (auto right : rightlist)
	{ 
		TimestampType interval = absoluteunsignedlonglong((long long)(left.ts - right.ts));
		if (interval < min_interval)
		{
			min_interval = interval;
			align_right = right;
		}
	}

	return align_lidar_pair(left, align_right);
}

void FileProcess::lidarfiledownsampling()
{
	std::vector<align_lidar_pair> lidarfilelist_copy = m_lidarfilelist;
	m_lidarfilelist.clear();

	TPose samplevehpose = { FLT_MAX ,FLT_MAX ,FLT_MAX };
	for (auto file : lidarfilelist_copy)
	{
		TPose nowvehpose = file.first.po;
		float32_t odo = sqrt(pow((nowvehpose.x - samplevehpose.x),2)+pow((nowvehpose.y - samplevehpose.y),2));
		if (odo >= PODOWNSAMPLE)
		{
			m_lidarfilelist.push_back(file);
			samplevehpose = nowvehpose;
		}
		
		
	}
	
}
