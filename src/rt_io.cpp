#include "rt_io.h"

using namespace std;

bool rt_io_read(const s8 *filename,u32 offset,s8 *buffer,u32 size)
{
	s8 result  = false;
	ifstream in(filename,ios::in|ios::binary|ios::ate);
	do{
		if(!in.seekg(offset,ios::beg)){
			io_error("file seek error \n");
			break;
		}

		if(!in.read((char*)buffer,size)){
			io_error("read file error \n");
			break;
		}

		result = true;
		break;
	}while(1);

	in.close();
	return result;
}

bool rt_io_write(const s8 *filename,u32 offset,s8 *buffer,u32 size)
{
	s8 result = false;
	ofstream out(filename,ios::out|ios::binary|ios::ate);
	do{
		if(!out.seekp(offset,ios::beg)){
			io_error("file seek error \n");
			break;
		}

		if(!out.write((char*)buffer,size)){
			io_error("read file error \n");
			break;
		}

		result = true;
		break;
	}while(1);
	out.close();
	return result;
}


bool rt_io_create(const s8 *filename)
{
	ofstream out(filename);

	if(!out){
		io_error("create file error \n");
		return false;
	}
	return true;
}


