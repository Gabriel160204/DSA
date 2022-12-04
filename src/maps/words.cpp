#include <cctype>
#include <iostream>
#include <string.h>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <fstream>

bool cmp(const std::pair<std::string, uint32_t>& a,
		 const std::pair<std::string, uint32_t>& b) {
	return a.second > b.second;
}

std::vector<std::pair<std::string, uint32_t>> sort(const std::unordered_map<std::string, uint32_t>& map) {
	std::vector<std::pair<std::string, uint32_t>> result;
	for (const auto& m : map) {
		result.push_back(m);
	}
	std::sort(result.begin(), result.end(), cmp);
	return result;
}

int main(int argc, char* argv[]) {
	if (argc < 2) {
		std::cout << "Insufficient arguments\n"
			<< "-h for help\n";
		return -1;
	}
	if (strcmp(argv[1], "-h") == 0) {
		std::cout << "First argument for source file\n"
			<< "Second argument for the output, if empty it will autogenerate a file in the current directory\n";
		return 1;
	}

	std::unordered_map<std::string, uint32_t> mapWords;
	std::unordered_map<std::string, uint32_t>::iterator it;
	std::vector<std::pair<std::string, uint32_t>> result;
	std::string especial_chars = "0123456789!@#$%¨&()__+\'\"¹²³£º¢§¬{}[]\\´`^~,.;/<>:ª»©¡«?|/*-";
	std::string word, fullFile, output;
	if (argc < 3) {
		output = "result.csv";
	} else {
		output = argv[2];
		output += ".csv";
	}

	std::ifstream ifs(argv[1], std::ifstream::in);
	if (ifs) {
		while (ifs >> word) {
			fullFile += word + ' ';
		}
		ifs.close();
	} else {
		std::cout << "Failed to open the file\n";
		return -2;
	}
	for (const char& ch : especial_chars) {
		fullFile.erase(std::remove(fullFile.begin(), fullFile.end(), ch), fullFile.end());
	}
		std::transform(fullFile.begin(), fullFile.end(), fullFile.begin(),
			[](unsigned char ch){ return std::tolower(ch);});
	std::stringstream ss(fullFile);
	while (ss >> word) {
		it = mapWords.find(word);
		if (it != mapWords.end()) {
			it->second += 1;
		} else {
			mapWords[word] = 1;
		}
	}
	result = sort(mapWords);
	std::ofstream ofs(output, std::ofstream::out | std::ofstream::trunc);
	if (ofs) {
		for (const auto& [_word, _total] : result) {
			word = _word + ','+ std::to_string(_total) + '\n';
			ofs << word;
		}
		ofs.close();
	} else {
		std::cout << "Failed to create the file\n";
		return -3;
	}
	return 0;
}
