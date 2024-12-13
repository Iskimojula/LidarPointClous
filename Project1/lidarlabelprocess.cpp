#include "lidarlabelprocess.h"
#include "tools.h"
#include "argumentpass.h"
#define  VIEWER 0

void LiderLabelProcess::Init()
{

	//��ʼ������ļ��У�����ļ��д��ڣ���ô����ļ��е����ݣ�����ļ��в����ڣ��½��ļ���
	newfolder(ArgumentPass::Instance().get_gtfolderworkdir());
	newfolder(ArgumentPass::Instance().get_gtfolderpath());
	newfolder(ArgumentPass::Instance().get_lidarmap());

	//not use
	AddFilter(&CFilterHandler::octreevolexgridfilter);
	AddFilter(&CFilterHandler::valuefilterZ);
	AddFilter(&CFilterHandler::valuefilterX);
	AddFilter(&CFilterHandler::valuefilterY);

	AddSeg(&CSegHandler::clusterseg);
	//not use
}

void LiderLabelProcess::Process()
{
	//�����������ļ��������ļ���ʱ�����
	fileprocess.Process();
	boost::shared_ptr<std::vector<align_lidar_pair>> filelist = fileprocess.GetLidarAlignFileList();
#if 1
	//��鼤����Ƶ�ͼ�Ƿ���ڣ���������ڣ����½�ͼ
	if (!mapexist())
	{
		std::cout << "need mapping ..." << std::endl;
		//����ÿһ������bin�ļ�
		for (size_t i = 0; i < filelist->size(); i++)
		{
			align_lidar_pair lidarfile = (*filelist)[i];
			//left lidar
			//LidardateCenter::Instance().readunilaterallidar(lidarfile.first.pos, lidarfile.first);
			
			//right lidar ����ת�����״�����->�Գ�����->��������
			LidardateCenter::Instance().readunilaterallidar(lidarfile.second.pos, lidarfile.second);
			m_dataptr = LidardateCenter::Instance().GetLidarClouds();
			printProgressBar(i, filelist->size() - 1);
		}
		//��ȡ��������
		m_dataptr = LidardateCenter::Instance().GetLidarClouds();
		std::cout << "total cloud size: " << m_dataptr->size() << std::endl;

		//�����·��ʯ����Ҫ�ָ��·��ʯ
		if (ArgumentPass::Instance().IsRoadTrafficStone)
		{
			std::cout << "\n" << "label road traffic stone, plane segment working ..." << std::endl;
			seghandler.planeseg(m_dataptr);
			std::cout << "cloud size plan segment: " << m_dataptr->size() << std::endl;
		}
		//���ƽ��������˲�
		filterhandler.volexgridfilter(m_dataptr);
		std::cout << "cloud size after downsampling: " << m_dataptr->size() << std::endl;
		//���ӻ�
		Viewer();
		//�洢��map.csv
		Savemap();
		
	}
	//����������ڣ����ȡ��ͼ
	else
	{
		std::cout << "map exists ..." << std::endl;
		std::string mapath = std::string(ArgumentPass::Instance().LIDARFOLDE_arg) + "/" + std::string(OUTMAPFILE);
		LidardateCenter::Instance().ReadLidarPointClouds(mapath,0);
		m_dataptr = LidardateCenter::Instance().GetLidarClouds();

	}
#endif
	//��ȡ�������ݣ�����ʱ���������DR��ֵ
	std::string usspath = std::string(ArgumentPass::Instance().LIDARFOLDE_arg) + "/" + std::string(USSFOLDER) + "/" + std::string(USSFILE);
	UssdateCenter::Instance().ReadUssPo(usspath, fileprocess.GetPoMap());
	boost::shared_ptr<std::vector<tObjProperty3D>> ussproperty = UssdateCenter::Instance().GetUssProperty3D();
	int labelcount = 0;

	//������������
	for (int i = 0; i < ussproperty->size(); i++)
	{
		//��ȡ����DR��ʱ���
		TPose vehpose = { (*ussproperty)[i].f32X ,(*ussproperty)[i].f32Y, (*ussproperty)[i].f32Yaw};
		TimestampType ts = (*ussproperty)[i].u64Timestamp_us;
		
		//��ȡȫ�������е�bev��Χ
		
		CPolygon bev(GetBevRange_5()[0].x + PIXELSIZE,
			         GetBevRange_5()[0].y + PIXELSIZE,
					GetBevRange_5()[1].x + PIXELSIZE,
					GetBevRange_5()[1].y - PIXELSIZE,
					GetBevRange_5()[2].x - PIXELSIZE,
					GetBevRange_5()[2].y - PIXELSIZE,
					GetBevRange_5()[3].x - PIXELSIZE,
					GetBevRange_5()[3].y + PIXELSIZE);
		bev.trans2W(vehpose);

		//ɸѡ����bev��Χ�ڵĵ���,����������ȫ������
		pcl::PointCloud<pcl::PointXYZI>::Ptr clouds_in_bev = filterhandler.polygonfilter(m_dataptr,bev);
		//���bev��Χ�ڴ��ڵ���
		if (clouds_in_bev->size())
		{
			//������Գ������µ�boundary��Z����Ϊ0
			pcl::PointCloud<pcl::PointXYZI> boundary_in_frame = featurehandler.freespace(clouds_in_bev, vehpose);

			bevprocess.SetLidarFreespace(boost::make_shared<pcl::PointCloud<pcl::PointXYZI>>(boundary_in_frame));
			bevprocess.SetUssTimestamp(ts);

			//����freespace��עgt
			if (bevprocess.Process())
			{
				pclviewer.bevinmapviewer(m_dataptr, (*ussproperty)[i]);
				labelcount++;
			}
		}
		printProgressBar(i, ussproperty->size()-1);
	}

	std::string ussoutpath = ArgumentPass::Instance().get_outcsvbasename();

	UssdateCenter::Instance().WriteUssLabel(usspath, ussoutpath, bevprocess.GetLabelUssTs());

	std::cout << "--- lidar label process finish ! :) ---" << std::endl;
	std::cout << "--- total " << labelcount << " uss file labeled ! ---" << std::endl;
	std::cout << "--- gt path :" << ArgumentPass::Instance().get_gtfolderworkdir() << " ---" << std::endl;

}

void LiderLabelProcess::Clear()
{
	LidardateCenter::Instance().Clear();
	UssdateCenter::Instance().Clear();
}


void LiderLabelProcess::AddFilter(FilterFuncHandlePtr fun)
{
	filter.push_back(fun);
}

void LiderLabelProcess::AddSeg(SegFuncHandlerPtr fun)
{
	seg.push_back(fun);
}

void LiderLabelProcess::Filterprocess()
{
	for (int i = 0; i < filter.size(); i++)
	{
		(filterhandler.*filter[i])(m_dataptr);
	}
}

void LiderLabelProcess::Segprocess()
{
	for (int i = 0; i < seg.size(); i++)
	{
		(seghandler.*seg[i])(m_dataptr);
	}
}

void LiderLabelProcess::Viewer()
{
	//viewer
	pcl::visualization::PCLVisualizer::Ptr viewer(new pcl::visualization::PCLVisualizer("Point Cloud Viewer 1"));

	pcl::visualization::PointCloudColorHandlerGenericField<pcl::PointXYZI> color_handler(m_dataptr, "z" );
	viewer->addPointCloud(m_dataptr, color_handler, "sample cloud");

	while (!viewer->wasStopped()) {
		viewer->spinOnce(100);
		std::this_thread::sleep_for(std::chrono::milliseconds(100));

	}
}

void LiderLabelProcess::Viewer(std::string)
{
	pcl::visualization::PCLVisualizer::Ptr viewer(new pcl::visualization::PCLVisualizer("point cloud viewer"));

	for (size_t i = 0; i < m_clusterptr->size();i++)
	{
		pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZRGB>);
		for (rsize_t j = 0; j < (*m_clusterptr)[i].indices.size(); j++)
		{
			pcl::PointXYZRGB pt;
			pt.x = m_dataptr->points[(*m_clusterptr)[i].indices[j]].x;
			pt.y = m_dataptr->points[(*m_clusterptr)[i].indices[j]].y;
			pt.z = m_dataptr->points[(*m_clusterptr)[i].indices[j]].z;
			cloud->push_back(pt);
		}
		pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZRGB> color_handler(cloud,getrandcolor(),getrandcolor(),getrandcolor());
		viewer->addPointCloud(cloud,color_handler,std::to_string(i));


	}
	
	pcl::PointCloud<pcl::PointXYZ>::Ptr freespaceptr = boost::make_shared<pcl::PointCloud<pcl::PointXYZ>>(m_lidar_freespace);
	viewer->addPointCloud(freespaceptr, "freespace");
	viewer->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 5, "freespace");
	

	while (!viewer->wasStopped()) {
		viewer->spinOnce(100);
		std::this_thread::sleep_for(std::chrono::milliseconds(100));

	}
}

void LiderLabelProcess::CalcPointSize()
{
	pcl::PointXYZI min_pt, max_pt;
	min_pt.x = min_pt.y = min_pt.z = std::numeric_limits<float>::max();
	max_pt.x = max_pt.y = max_pt.z = -std::numeric_limits<float>::max();

	for (size_t i = 0; i < m_dataptr->points.size(); ++i) {
		if (m_dataptr->points[i].x < min_pt.x) min_pt.x = m_dataptr->points[i].x;
		if (m_dataptr->points[i].y < min_pt.y) min_pt.y = m_dataptr->points[i].y;
		if (m_dataptr->points[i].z < min_pt.z) min_pt.z = m_dataptr->points[i].z;

		if (m_dataptr->points[i].x > max_pt.x) max_pt.x = m_dataptr->points[i].x;
		if (m_dataptr->points[i].y > max_pt.y) max_pt.y = m_dataptr->points[i].y;
		if (m_dataptr->points[i].z > max_pt.z) max_pt.z = m_dataptr->points[i].z;
	}

	m_minx = min_pt.x;
	m_miny = min_pt.y;
	m_minz = min_pt.z;

	m_maxx = max_pt.x;
	m_maxy = max_pt.y;
	m_maxz = max_pt.z;
}

std::pair<float, float> LiderLabelProcess::CalcPointSize(pcl::PointCloud<pcl::PointXYZI>::Ptr ptr, std::string label)
{
	pcl::PointXYZI min_pt, max_pt;
	min_pt.x = min_pt.y = min_pt.z = std::numeric_limits<float>::max();
	max_pt.x = max_pt.y = max_pt.z = -std::numeric_limits<float>::max();

	for (size_t i = 0; i < ptr->points.size(); i++) {
		if (ptr->points[i].x < min_pt.x) min_pt.x = ptr->points[i].x;
		if (ptr->points[i].y < min_pt.y) min_pt.y = ptr->points[i].y;
		if (ptr->points[i].z < min_pt.z) min_pt.z = ptr->points[i].z;

		if (ptr->points[i].x > max_pt.x) max_pt.x = ptr->points[i].x;
		if (ptr->points[i].y > max_pt.y) max_pt.y = ptr->points[i].y;
		if (ptr->points[i].z > max_pt.z) max_pt.z = ptr->points[i].z;
	}

	if (label == "x")
	{
		return std::make_pair(min_pt.x, max_pt.x);
	}

	if (label == "y")
	{
		return std::make_pair(min_pt.y, max_pt.y);
	}

	if (label == "z")
	{
		return std::make_pair(min_pt.z, max_pt.z);
	}
}

bool LiderLabelProcess::mapexist()
{
	boost::filesystem::path folder(std::string(LIDARFOLDER));
	boost::filesystem::path filetocheck = std::string(ArgumentPass::Instance().LIDARFOLDE_arg) + "/" + std::string(OUTMAPFILE);
	return ((boost::filesystem::exists(filetocheck)) && (boost::filesystem::is_regular_file(filetocheck)));

}

void LiderLabelProcess::Freespace()
{
	for (size_t i = 0; i < m_clusterptr->size(); i++)
	{
		pcl::PointCloud<pcl::PointXYZI>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZI>);
		for (rsize_t j = 0; j < (*m_clusterptr)[i].indices.size(); j++)
		{
			pcl::PointXYZI pt;
			pt.x = m_dataptr->points[(*m_clusterptr)[i].indices[j]].x;
			pt.y = m_dataptr->points[(*m_clusterptr)[i].indices[j]].y;
			pt.z = m_dataptr->points[(*m_clusterptr)[i].indices[j]].z;
			cloud->push_back(pt);
		}

		Freespace(cloud);

	}
	
	
}

void LiderLabelProcess::Freespace(pcl::PointCloud<pcl::PointXYZI>::Ptr ccloud)
{
	std::pair<float, float> range_y = CalcPointSize(ccloud, "y");

	for (auto step = range_y.first; step <= range_y.second; step += PIXELSIZE)
	{
		pcl::PointCloud<pcl::PointXYZI>::Ptr slicer_cloud(new pcl::PointCloud<pcl::PointXYZI>);
		pcl::PassThrough<pcl::PointXYZI> pass;
		pass.setInputCloud(ccloud);
		pass.setFilterFieldName("y");
		pass.setFilterLimits(step,step + PIXELSIZE);
		pass.filter(*slicer_cloud);

		std::pair<float, float> range_x = CalcPointSize(slicer_cloud, "x");
		if (range_x.first <= RANGEX_MAX)
		{
			pcl::PointXYZ bnd = { range_x.first,static_cast<float>((step + step + PIXELSIZE) / 2.0f ),0 };
			m_lidar_freespace.push_back(bnd);
		}
		
	}
}

void LiderLabelProcess::Savemap()
{
	std::string outpath = (std::string)ArgumentPass::Instance().LIDARFOLDE_arg + "/map.csv";

	std::ofstream outfile(outpath);
	if (outfile.is_open())
	{
		for (int k = 0; k < m_dataptr->size(); k++)
		{
			outfile << m_dataptr->points[k].x << "," << m_dataptr->points[k].y << ","
				<< m_dataptr->points[k].z << "," << ((int)m_dataptr->points[k].intensity) << std::endl;
		//	printProgressBar(k, m_dataptr->size() - 1);
		}
		
	}
	else
	{
		std::cout << outpath << " open error!" << std::endl;
	}
	outfile.close();
}
