#include <iostream>
#include <fstream>
#include <locale>
#include <string>

std::ifstream::pos_type filesize(std::string filename);

int main(int argc,char* argv[]) 
{
    if(argc==4)
    {
	std::string key,src,dst;
	key=argv[1];
	src=argv[2];
	dst=argv[3];
	std::string temp=key;
	std::ifstream file(src);
	std::ofstream file2(dst, std::ios::out | std::ios::trunc);
	while(key.length()<filesize(src))
	{
	    key.append(temp);
	}
	char buffer[int(filesize(src))];
	char* pt_buffer=buffer;
	while(file.read(pt_buffer,int(filesize(src))))
	{
	    for(size_t i=0;i<sizeof(buffer)/sizeof(char);i++)
	    {
		    file2<<(char)(buffer[i]^key[i]);
	    }
	}
	file.close();
	file2.close();
	std::cout<<"Done"<<std::endl;
    }
    else
    {
	std::cout<<"Usage: encrdecr *key* *source file* *destination file*"<<std::endl;
    }
    return 0;
}

std::ifstream::pos_type filesize(std::string filename)
{
    std::ifstream in(filename, std::ifstream::ate | std::ifstream::binary);
    return in.tellg();
}
