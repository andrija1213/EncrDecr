#include <iostream>
#include <fstream>
#include <string>

std::ifstream::pos_type filesize(std::string filename);

int main(int argc,char* argv[]) 
{
    std::cout<<"Args given: "<<argc<<std::endl;
    if(argc==4) //if right amout of arguments are passed
    {
	std::string key,src,dst;
	key=argv[1]; //first command line argument is key
	src=argv[2]; //second one is source file
	dst=argv[3]; //third one is destination
	std::string temp=key; //copy of key to add onto key
	std::ifstream file(src); //open source file in reading mode
	std::ofstream file2(dst, std::ios::out | std::ios::trunc); //open destination file in writing mode, this creates new file if it doesn't exist
	while(key.length()<filesize(src) && key.length()<=200) //while key is less than size of the file, add key on itself until it reaches size of the file
	{
	    key.append(temp);
	}
	char buffer[key.length()]; //string to store the content of the file
	char* pt_buffer=buffer; //pointer to buffer
	for(size_t i=0;i<int(filesize(src));i+=key.length())
	{
	    file.read(pt_buffer,key.length()); //read file content into the string buffer
	    for(size_t i=0;i<sizeof(buffer)/sizeof(char);i++) //iterate over each character and write xor result into the destination file
	    {
		file2<<(char)(buffer[i]^key[i]); //part that writes
	    }
	}
	file.close(); //close both files
	file2.close();
	std::cout<<"Done"<<std::endl;
    }
    else
    {
	std::cout<<"Usage: encrdecr *key* *source file* *destination file*"<<std::endl;
    }
    return 0;
}

std::ifstream::pos_type filesize(std::string filename) //function to get the filesize
{
    std::ifstream in(filename, std::ifstream::ate | std::ifstream::binary); //opens the file in reading mode and places the pointer at the end of it
    return in.tellg(); //returns pointer place in the file
}
