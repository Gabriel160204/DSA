#include <iostream>
#include <string>
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

int main() {
	std::unordered_map<std::string, uint32_t> mapWords;
	std::unordered_map<std::string, uint32_t>::iterator it;
	std::vector<std::pair<std::string, uint32_t>> result;
	std::string especial_chars = "0123456789!@#$%¨&()__+\'\"¹²³£º¢§¬{}[]\\´`^~,.;/<>:ª»©¡«?|/*-";
	std::string word, fullFile;

	std::ifstream ifs("src/maps/texts.txt", std::ifstream::in);
	if (ifs) {
		while (ifs >> word) {
			fullFile += word + ' ';
		}
		ifs.close();
	}
	for (const char& ch : especial_chars) {
		fullFile.erase(std::remove(fullFile.begin(), fullFile.end(), ch), fullFile.end());
	}
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
	std::ofstream ofs("src/maps/result.csv", std::ofstream::out | std::ofstream::trunc);
	if (ofs) {
		for (const auto& [_word, _total] : result) {
			word = _word + ','+ std::to_string(_total) + '\n';
			ofs << word;
		}
		ofs.close();
	}
}
