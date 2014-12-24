//g++ -std=c++11 0113312.cpp
#include <iostream>
#include <fstream>
#include <algorithm>
#include <list>
#include <stdio.h>
#include <unordered_map>

using namespace std;

int main()
{
	int miss, hit, frame_size = 64;
	list<string>::iterator it;
	list<string> List;
    unordered_map<string, list<string>::iterator> unmap;
    unordered_map<string, list<string>::iterator>::iterator got;

	string page;
	char temp[16], trace_file[20];
	fstream file;

	printf("Trace file : ");
	scanf("%s", trace_file);
	printf("size\tmiss\thit\tpage fault ratio\n");
	while(frame_size < 1024)
	{
		hit = miss = 0;
		List.clear();
		file.open(trace_file, ios::in);
		while(file >> temp)
		{
			file >> temp;
			temp[5] = '\0';
			page = temp;
            got = unmap.find(page);

			if( got != unmap.end() ){//found
				List.erase(unmap[page]);
				++hit;
			}else {
				if(unmap.size() >= frame_size)
				{
                    unmap.erase(List.back());
                    List.pop_back();
				}
				++miss;
			}
			List.push_front(page);
			unmap[page] = List.begin();
		}
		file.close();
        unmap.clear();
		printf("%d\t%d\t%d\t%20.9lf\n", frame_size, miss, hit, double(miss)/(hit + miss));
		frame_size <<= 1;
	}
	return 0;
}
