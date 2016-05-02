#pragma once
#ifndef __GNH_UTIL_H_
#define __GNH_UTIL_H_

#include "cocos2d.h"

#include <string>
#include <fstream>
#include <streambuf>
#include <algorithm>

#define GNH_RESOURCE_PATH(FILENAME) cocos2d::FileUtils::getInstance()->fullPathForFilename(FILENAME)

namespace gnh {
	void readFileToStr(std::string& filename, std::string& readString) {
		std::ifstream t(filename.c_str());

		t.seekg(0, std::ios::end);
		readString.reserve(t.tellg());
		t.seekg(0, std::ios::beg);

		readString.assign((std::istreambuf_iterator<char>(t)),
						  std::istreambuf_iterator<char>());
	}

	std::string toLowerCase(const std::string& input) {
		std::string result;
		result.reserve(input.size());

		std::transform(input.begin(), input.end(), result.begin(), ::tolower);

		return result;
	}
}

#endif