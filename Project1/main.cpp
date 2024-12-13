/*
* pcl version : PCL_1.8.1
* opencv version :  opencv4.5
* MSVC ： 2017
*/
#include "lidarlabelprocess.h"
#include "fileprocess.h"
#include "tools.h"
#include "argumentpass.h"
int main(int argc, char* argv[])
{
	while (1) {
		//终端输入文件地址
		if (argc == 1)
		{
			std::cout <<"\n"<< "Please input lidarfolder :" << std::endl;
			std::cin >> ArgumentPass::Instance().LIDARFOLDE_arg;

			std::cout << "" << std::endl;
			std::cout << "Is road traffic stone ?(1/0)" << std::endl;
			int in;
			std::cin >> in;

			ArgumentPass::Instance().IsRoadTrafficStone = (in == 1);

		}
		//命令行窗口启动，输入文件地址,暂时未使用
		else
		{
			ArgumentPass::Instance().LIDARFOLDE_arg = argv[1];

		}
		if (checkLidarFoldervaild(ArgumentPass::Instance().LIDARFOLDE_arg))//检查合法性，只检查文件夹
		{
			//获得log名字
			ArgumentPass::Instance().GTPREFIX_arg = getprefix(ArgumentPass::Instance().LIDARFOLDE_arg);
			std::replace(ArgumentPass::Instance().LIDARFOLDE_arg.begin(), ArgumentPass::Instance().LIDARFOLDE_arg.end(), '\\', '/');

			//初始化
			LiderLabelProcess lidarlabel;
			lidarlabel.Init();

			//主程序
			lidarlabel.Process();

			//clear,清除激光数据，超声数据
			lidarlabel.Clear();
		}

	}
	return 0;
}
