#include<iostream>
#include<fstream>

#include<string>
#include<vector>

// 每行字符限制在2048字符内
#define MAXSIZE 2048

int main(void) {
	// read input.csv
	std::string ifilename("input.csv");
	std::ifstream fin(ifilename);
	if (!fin) {
		std::cout << "failed to open " << ifilename << std::endl;
		return -1;
	}
	std::vector<std::string> strs;
	while(!fin.eof()) {
		char tempstr[MAXSIZE];
		fin.getline(tempstr, MAXSIZE);
		strs.push_back(tempstr);
	}
	fin.close();

	if (strs.size() < 1) {
		std::cout << "data is empty!!!" << std::endl;
		return 0;
	}

	char split = ',', metac = '\\';
	std::vector<std::vector<std::string>> data_list;
	for (int i = 0; i < strs.size(); i++) {
		if (strs[i].size() <= 0) {
			continue;
		}
		std::vector<char> chs;
		std::string str = strs[i];
		std::vector<std::string> list;
		for (int j = 0; j < str.size(); j++) {
			if ((str[j] == metac) && (j + 1 < str.size()) && (str[j + 1] == split)) {
				j++;
				continue;
			}
			if (str[j] == split) {
				std::string target(chs.begin(), chs.end());
				list.push_back(target);
				chs.clear();
			} else {
				chs.push_back(str[j]);
			}
		}
		// 最后一个
		if (chs.size() > 0) {
			std::string target(chs.begin(), chs.end());
			list.push_back(target);
			chs.clear();
		}
		data_list.push_back(list);
	}

	// print result
	for (int i = 0; i < data_list.size(); i++) {
		std::vector<std::string> list = data_list[i];
		for (int j = 0; j < list.size(); j++) {
			std::cout << list[j] << "\t";
		}
		std::cout << std::endl;
	}

	// trans to json
	char ofilename[] = "output.json";
	FILE *pfile = NULL;
	if (!(pfile = fopen(ofilename,"w"))) {
		printf("failed to append log");
		exit(1);
	}
	fprintf(pfile,"[\n");

	std::vector<std::string> header = data_list[0];
	for (int i = 1; i < data_list.size(); i++) {
		fprintf(pfile,"\n\t[%d] = {", i - 1);
		std::vector<std::string> data = data_list[i];
		for (int j = 0; j < header.size(); j++) {
			fprintf(pfile,"\n\t\t\"%s\" : \"%s\"", header[j].c_str(), data[j].c_str());
			if (j != header.size() - 1) {
				fprintf(pfile,",");
			}
		}
		fprintf(pfile,"\n\t}");
		if (i != data_list.size() - 1) {
			fprintf(pfile,",");
		}
	}

	fprintf(pfile,"\n]");
	fflush(pfile);
	fclose(pfile);

}
