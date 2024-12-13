#include "bevprocess.h"
#include "tools.h"
#include "argumentpass.h"
int BevProcess::Process()
{
	CSegHandler seghandler;

	//��boundary����ŷ������
	seghandler.clusterseg(m_bdy);
	boost::shared_ptr<std::vector<pcl::PointIndices>> clusters = seghandler.getclusterindices();
	
	//resetͼ��
	m_bev_image = cv::Mat::zeros(Const_GtResolutionH, Const_GtResolutionV, CV_8UC3);
	
	//����ÿ��cluster������cluster�������
	for (size_t i = 0; i < clusters->size(); i++)
	{
		std::vector<cv::Point> pixel_boundary;
		CImgDataConvert imgconvert;

		//����cluster�е�ÿ����
		for (rsize_t j = 0; j < (*clusters)[i].indices.size(); j++)
		{
			pixel_boundary.push_back(imgconvert.Trans2Img(m_bdy->points[(*clusters)[i].indices[j]].x, m_bdy->points[(*clusters)[i].indices[j]].y));
		}

		std::sort(pixel_boundary.begin(),pixel_boundary.end(),compare_x);
		pixel_boundary.push_back(cv::Point(pixel_boundary[pixel_boundary.size() - 1].x,0));
		pixel_boundary.push_back(cv::Point(pixel_boundary[0].x, 0));

		//�������
		cv::fillConvexPoly(m_bev_image, pixel_boundary, cv::Scalar(198, 198, 198));

		//��ʾͼ�� 
		//cv::imshow("Filled Polygon",m_bev_image);
		cv::waitKey(0);
	}
	//���cluster������0
	if (clusters->size())
	{
		//���Ѿ���ע�������ݵ�ʱ��������Ա����m_ts_trajectory
		m_ts_trajectory.push_back(m_ts);
		//��gtͼ
		std::string seqfile = ArgumentPass::Instance().GTPREFIX_arg + "_SN" + std::to_string(m_size) + "_gt.png";
		std::string gtfolderpath = ArgumentPass::Instance().get_gtfolderpath() + "/" + seqfile;
		cv::imwrite(gtfolderpath, m_bev_image);
		m_size++;
	}
	return (clusters->size());

}

void BevProcess::SetLidarFreespace(pcl::PointCloud<pcl::PointXYZI>::Ptr ptr)
{
	m_bdy = ptr;
}

void BevProcess::SetUssTimestamp(TimestampType & ts)
{
	m_ts = ts;
}

boost::shared_ptr<std::vector<TimestampType>> BevProcess::GetLabelUssTs()
{
	return boost::make_shared<std::vector<TimestampType>>(m_ts_trajectory);
}

int & BevProcess::GetLabelSize()
{
	return m_size;
}
