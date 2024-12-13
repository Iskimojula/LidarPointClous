/*
* pcl version : PCL_1.8.1
* opencv version :  opencv4.5
* MSVC �� 2017
*/
#include "lidarlabelprocess.h"
#include "fileprocess.h"
#include "tools.h"
#include "argumentpass.h"
int main(int argc, char* argv[])
{
	while (1) {
		//�ն������ļ���ַ
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
		//�����д��������������ļ���ַ,��ʱδʹ��
		else
		{
			ArgumentPass::Instance().LIDARFOLDE_arg = argv[1];

		}
		if (checkLidarFoldervaild(ArgumentPass::Instance().LIDARFOLDE_arg))//���Ϸ��ԣ�ֻ����ļ���
		{
			//���log����
			ArgumentPass::Instance().GTPREFIX_arg = getprefix(ArgumentPass::Instance().LIDARFOLDE_arg);
			std::replace(ArgumentPass::Instance().LIDARFOLDE_arg.begin(), ArgumentPass::Instance().LIDARFOLDE_arg.end(), '\\', '/');

			//��ʼ��
			LiderLabelProcess lidarlabel;
			lidarlabel.Init();

			//������
			lidarlabel.Process();

			//clear,����������ݣ���������
			lidarlabel.Clear();
		}

	}
	return 0;
}
