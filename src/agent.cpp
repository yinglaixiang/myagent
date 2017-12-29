#include <cstdio>
#include <iostream>
#include "agent.h"

using namespace std;


int main()
{
	cout<<"hello world";

	rt_io_create("./hello_world");
	rt_io_write("./hello_world",0,"hello",sizeof("hello"));
	return 0;
}