#include "pcl_viewer.h"
#include "argumentpass.h"
void CPclViewer::lidarcloudmapviewer(pcl::PointCloud<pcl::PointXYZI>::Ptr clouds)
{
	pcl::visualization::PCLVisualizer::Ptr viewer(new pcl::visualization::PCLVisualizer("Point Cloud Viewer 1"));

	pcl::visualization::PointCloudColorHandlerGenericField<pcl::PointXYZI> color_handler(clouds, "z");
	viewer->addPointCloud(clouds, color_handler, "sample cloud");

	while (!viewer->wasStopped()) {
		viewer->spinOnce(100);
		std::this_thread::sleep_for(std::chrono::milliseconds(100));

	}
}

static void keyboardEventOccurred(const pcl::visualization::KeyboardEvent& event, void* viewer_void) {
	pcl::visualization::PCLVisualizer* viewer = static_cast<pcl::visualization::PCLVisualizer*>(viewer_void);

	if (event.getKeySym() == "q" && event.keyDown()) {
		viewer->close();
	}
}

//此时所有的坐标都为全局坐标
void CPclViewer::bevinmapviewer(pcl::PointCloud<pcl::PointXYZI>::Ptr clouds, pcl::PointCloud<pcl::PointXYZI>::Ptr vehoutline, pcl::PointCloud<pcl::PointXYZI>::Ptr &bevrange)
{
	pcl::visualization::PCLVisualizer::Ptr viewer(new pcl::visualization::PCLVisualizer("Point Cloud Viewer 1"));

	//画map
	pcl::visualization::PointCloudColorHandlerGenericField<pcl::PointXYZI> color_handler(clouds, "z");
	viewer->addPointCloud(clouds, color_handler, "sample cloud");

	//画车外轮廓
	viewer->addPolygon<pcl::PointXYZI>(vehoutline, 0, 1, 0, "vehoutline");
	
	//画Bev轮廓
	viewer->addPolygon<pcl::PointXYZI>(bevrange,1,0,0,"bevrange");

	viewer->registerKeyboardCallback(keyboardEventOccurred, (void*)viewer.get());

	while (!viewer->wasStopped()) {
		viewer->spinOnce(100);
		std::this_thread::sleep_for(std::chrono::milliseconds(100));

	}
}

void CPclViewer::bevinmapviewer(pcl::PointCloud<pcl::PointXYZI>::Ptr clouds, tObjProperty3D &vehpose)
{
	TPose pose = { vehpose.f32X,vehpose .f32Y,vehpose .f32Yaw};
	TimestampType ts = vehpose.u64Timestamp_us;

	pcl::visualization::PCLVisualizer::Ptr viewer(new pcl::visualization::PCLVisualizer("Point Cloud Viewer 1"));

	//画map
	pcl::visualization::PointCloudColorHandlerGenericField<pcl::PointXYZI> color_handler(clouds, "z");
	viewer->addPointCloud(clouds, color_handler, "sample cloud");

	//画车外轮廓
#if 1
	CPolygon vehoutline_polygon(GetVehoutLine_37(), 37);
	vehoutline_polygon.trans2W(pose);
	viewer->addPolygon<pcl::PointXYZI>(vehoutline_polygon.trans2Cloud(), 0, 1, 0, "vehoutline");

	//画Bev轮廓
	CPolygon bev_polygon(GetBevRange_5(), 5);
	bev_polygon.trans2W(pose);
	viewer->addPolygon<pcl::PointXYZI>(bev_polygon.trans2Cloud(), 0, 1, 0, "bev_polygon");
#endif
	viewer->spinOnce(100);

	std::string cloudfile = std::to_string(ts) + "_clouds.jpg";
	std::string gtfolderpath = ArgumentPass::Instance().get_lidarmap() +"/" + cloudfile;
	viewer->saveScreenshot(gtfolderpath);
	
	viewer->close();


#if 0 
	//viewer->registerKeyboardCallback(keyboardEventOccurred, (void*)viewer.get());
	while (!viewer->wasStopped()) {
		viewer->spinOnce(100);
		std::this_thread::sleep_for(std::chrono::milliseconds(100));

	}
#endif

}