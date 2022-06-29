#define _CRT_SECURE_NO_WARNINGS
#include <io.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <ostream>


using namespace std;

/**
 * @brief ͼ���ļ��ṹ��
 */
struct ImageFile
{
	std::string file_name; /*!< �ļ��� */
	int order_number; /*!< �ļ����, ȡ�ļ��� */
};

/**
* @brief ����������С����
* @param img1  ͼƬ1
* @param img2  ͼƬ2
* @return ����ͼƬ1������Ƿ�С��ͼƬ2
*	-- True ��ʾͼƬ1С��ͼƬ2
*   -- False ��ʾͼƬ1����ͼƬ2
*/
bool SortByImageFiles(const ImageFile img1, const ImageFile img2)
{
	return img1.order_number < img2.order_number;
}

/**
* @brief �ַ��ָ��, this function adapt from: https://blog.csdn.net/mary19920410/article/details/77372828
* @param str  ���зָ���ַ���
* @param delim  �ָ��
* @return ���طָ����ַ�vector
*/
vector<string> split(const string& str, const string& delim)
{
	vector<string> res;
	if ("" == str) return res;
	char* strs = new char[str.length() + 1];
	strcpy(strs, str.c_str());

	char* d = new char[delim.length() + 1];
	strcpy(d, delim.c_str());

	char* p = strtok(strs, d);
	while (p) {
		string s = p;
		res.push_back(s);
		p = strtok(NULL, d);
	}
	

	return res;
}

/**
* @brief �ַ��ָ��
* @param folder_path  �ļ���·��
* @param file_format  �ļ�����
* @param file_names  ImageFile���͵�vector�����ڴ��ͼƬ����
*/
void GetImagePaths(std::string folder_path, std::string file_format, std::vector<ImageFile>& file_names)
{
	intptr_t hFile = 0;
	_finddata_t fileInfo;
	std::string file_path = folder_path;
	file_path = file_path.append(file_format);
	hFile = _findfirst(file_path.c_str(), &fileInfo);
	ImageFile temp_path;
	vector<string> split_result;
	if (hFile != -1) {
		/*cout << "----ԭ˳��----" << endl;*/
		do {
			if ((fileInfo.attrib & _A_SUBDIR)) {
				continue;
			}
			else {
				temp_path.file_name = folder_path + fileInfo.name;
				split_result = split(fileInfo.name, ".");
				temp_path.order_number = atoi(split_result[0].c_str());
				file_names.push_back(temp_path);
				//cout << temp_path.file_name << endl;
			}

		} while (_findnext(hFile, &fileInfo) == 0);
		std::sort(file_names.begin(), file_names.end(), SortByImageFiles);

		_findclose(hFile);
	}
}

int main()
{
	std::vector<ImageFile> file_names;
	GetImagePaths("C:/Users/hq/Desktop/temp/", "*.bmp", file_names);


	//file_names[1]=
	/*cout << "----��˳��----" << endl;*/


	for (auto lin : file_names) {
		cout << lin.file_name << endl;
		/*cout << lin.order_number << endl;*/
		
	}
	///*cout << a[1][2];*/
	//string a[250][4];
	//int rows = 249;
	//int columns = 4;
	//
	//for (int i = 0; i < rows; i++) {
	//	for (int j = 0; j < columns; j++) {
	//		//cout << file_names[i * columns + j] << " ";//a0[i*columns+j]�ȼ���a0[i][j]

	//		a[i][j] = file_names[4 * i + j].file_name;
	//	}
	//	cout << endl;
	//}

	return 0;
}
