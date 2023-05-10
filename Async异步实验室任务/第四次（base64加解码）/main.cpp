#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using size_b = unsigned int;		//与typedef作用类似
char chart[64];		//映射表
size_b reverse_chart[0x7E];		//反映射表

class base64in		//输入类
{
private:
	std::ifstream filein;
	std::vector<char> content;
	std::string filename;
public:
	~base64in()
	{
		if (filein.is_open())
		{
			filein.close();
		}
	}
	bool getFilename(const std::string& file)
	{
		//std::ifstream filein;
		filein.open(file, std::ios::in);
		return filein.is_open();
	}
	void getContent()
	{
		if (filein.is_open())
		{
			while (!filein.eof())
			{
				char temp;
				filein.get(temp);
				content.push_back(temp);
			}
			content.pop_back();
		}
		else
		{
			std::cout << "Enter your words:" << std::endl;
			char temp = 0;
			while (temp != '\n')
			{
				std::cin.get(temp);
				content.push_back(temp);
			}
			content.pop_back();
		}
	}

	std::vector<char> encode()
	{
		union
		{
			struct
			{
				char a;
				char b;
				char c;
			} in;
			struct
			{
				size_b x : 6;
				size_b y : 6;
				size_b z : 6;
				size_b t : 6;
			} out;
		} convert;
		std::vector<char> outv;
		int i;
		for (i = 2; i < content.size(); i += 3)
		{
			convert.in.a = 0;
			convert.in.b = 0;
			convert.in.c = 0;
			convert.in.c = content.at(i - 2);
			convert.in.b = content.at(i - 1);
			convert.in.a = content.at(i);
			outv.push_back(chart[convert.out.t]);
			outv.push_back(chart[convert.out.z]);
			outv.push_back(chart[convert.out.y]);
			outv.push_back(chart[convert.out.x]);
		}
		i -= 3;
		if (content.size() % 3 == 1)
		{
			convert.in.a = 0;
			convert.in.b = 0;
			convert.in.c = 0;
			convert.in.c = content.at(i + 1);
			outv.push_back(chart[convert.out.t]);
			outv.push_back(chart[convert.out.z]);
			outv.push_back('=');
			outv.push_back('=');
		}
		if (content.size() % 3 == 2)
		{
			convert.in.a = 0;
			convert.in.b = 0;
			convert.in.c = 0;
			convert.in.c = content.at(i + 1);
			convert.in.b = content.at(i + 2);
			outv.push_back(chart[convert.out.t]);
			outv.push_back(chart[convert.out.z]);
			outv.push_back(chart[convert.out.y]);
			outv.push_back('=');
		}
		return outv;
	}
	std::vector<char> decode()
	{
		union
		{
			struct
			{
				char a;
				char b;
				char c;
			} out;
			struct
			{
				size_b x : 6;
				size_b y : 6;
				size_b z: 6;
				size_b t : 6;
			} in;
		} convert;
		int i;
		std::vector<char> outv;
		for (i = 0; i < content.size(); i += 4)
		{
			convert.out.a = 0;
			convert.out.b = 0;
			convert.out.c = 0;
			convert.in.t = reverse_chart[content.at(i)];
			convert.in.z = reverse_chart[content.at(i + 1)];
			if (content.at(i + 2) == '=')
			{
				outv.push_back(convert.out.c);
				return outv;
			}
			else if (content.at(i + 3) == '=')
			{
				convert.in.y = reverse_chart[content.at(i + 2)];
				outv.push_back(convert.out.c);
				outv.push_back(convert.out.b);
				return outv;
			}
			else
			{
				convert.in.y = reverse_chart[content.at(i + 2)];
				convert.in.x = reverse_chart[content.at(i + 3)];
				outv.push_back(convert.out.c);
				outv.push_back(convert.out.b);
				outv.push_back(convert.out.a);
			}
		}
		return outv;
	}
};

class base64out		//输出类
{
private:
	std::ofstream fileout;
	std::vector<char> content;
	std::string filename;
public:
	~base64out()
	{
		if (fileout.is_open())
		{
			fileout.close();
		}
	}
	bool getFilename(const std::string& file)
	{
		fileout.open(file, std::ios::out);
		return fileout.is_open();
	}
	void getContentVector(std::vector<char>& in)
	{
		content = in;
	}
	void show()
	{
		for (auto i = content.begin(); i < content.end(); i++)
		{
			std::cout << *i;
		}
		std::cout << std::endl;
	}
	void writeToFile()
	{
		for (auto i = content.begin(); i < content.end(); i++)
		{
			fileout << *i;
		}
	}
};

int main(int argc, char* argv[])	//接收命令参数的main函数，每个参数是一个字符串，每个argv指向参数字符串的首地址
{
	if (argc <= 2)
	{
		std::cout << "参数不足。" << std::endl;
		return 0;
	}
	int i = 0;
	//----------------创建映射表--------------
	for (char al = 'A'; al <= 'Z'; al++)
	{
		chart[i] = al;
		i++;
	}
	for (char al = 'a'; al <= 'z'; al++)
	{
		chart[i] = al;
		i++;
	}
	for (char al = '0'; al <= '9'; al++)
	{
		chart[i] = al;
		i++;
	}
	chart[62] = '+';
	chart[63] = '/';
	//---------------映射表创建结束-------------
	//---------------创建反映射表---------------
	int j;
	j = 0;
	for (char i = 'A'; i <= 'Z'; i++)
	{
		reverse_chart[i] = j;
		j++;
	}
	for (char i = 'a'; i <= 'z'; i++)
	{
		reverse_chart[i] = j;
		j++;
	}
	for (char i = '0'; i <= '9'; i++)
	{
		reverse_chart[i] = j;
		j++;
	}
	chart['+'] = 62;
	chart['/'] = 63;
	//----------------反映射表创建结束----------
	base64in conin;
	base64out conout;
	if (argv[1][1] == 'e')
	{
		if (argv[2][1] == 'f')
		{
			if (conin.getFilename(argv[3]))
			{
				conin.getContent();
				std::vector<char> temp = conin.encode();
				conout.getContentVector(temp);
				if (argc == 3)
				{
					conout.show();
				}
				else
				{
					conout.getFilename(argv[4]);
					conout.writeToFile();
				}
			}
			else
			{
				std::cout << "Invalid file." << std::endl;
			}
		}
		else if (argv[2][1] == 'k')
		{
			conin.getContent();
			std::vector<char> temp = conin.encode();
			conout.getContentVector(temp);
			if (argc == 3)
			{
				conout.show();
			}
			else
			{
				conout.getFilename(argv[3]);
				conout.writeToFile();
			}
		}
		else
		{
			std::cout << "Unknown command of " << argv[1] << std::endl;
			return 0;
		}
	}
	else if (argv[1][1] == 'd')
	{
		if (argv[2][1] == 'f')
		{
			if (conin.getFilename(argv[3]))
			{
				conin.getContent();
				std::vector<char> temp = conin.decode();
				conout.getContentVector(temp);
				if (argc == 3)
				{
					conout.show();
				}
				else
				{
					conout.getFilename(argv[4]);
					conout.writeToFile();
				}
			}
			else
			{
				std::cout << "Invalid file." << std::endl;
			}
		}
		else if (argv[2][1] == 'k')
		{
			conin.getContent();
			std::vector<char> temp = conin.decode();
			conout.getContentVector(temp);
			if (argc == 3)
			{
				conout.show();
			}
			else
			{
				conout.getFilename(argv[3]);
				conout.writeToFile();
			}
		}
		else
		{
			std::cout << "Unknown command of " << argv[2] << std::endl;
			return 0;
		}
	}
	else if (argv[1][1] == 'h')
	{
		std::cout << "<参数1> <参数2> <输入文件名（可选）> <输出文件名（可选）> " << std::endl;
		std::cout << "参数1： -e：编码，-d：解码" << std::endl;
		std::cout << "参数2： -f：来自文件，-k：来自用户输入" << std::endl;
	}
	else
	{
		std::cout << "Unknown command of " << argv[1] << std::endl;
	}
	return 0;
}