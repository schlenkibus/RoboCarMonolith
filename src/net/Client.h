#pragma once

#include <string>
#include <curl/curl.h>
#include <iostream>

class Client {
public:
    static std::string encode(std::string s) {
            std::string pattern = "\n";
            std::string replace = "N";
            std::string ret(s);
            size_t pos = 0;
            while((pos = ret.find(pattern, pos)) != std::string::npos)
            {
                ret.replace(pos, pattern.size(), replace);
                pos += replace.size();
            }
            return ret;
    }

	static std::string performRequest(std::string urlPlusPayload) {
	    auto url = encode(urlPlusPayload);
		auto curl = curl_easy_init();
		std::cout << url << std::endl;
		std::string response;
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
		curl_easy_setopt(curl, CURLOPT_HTTP_VERSION, CURL_HTTP_VERSION_1_0);
		curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L);
		curl_easy_setopt(curl, CURLOPT_FORBID_REUSE, 1L);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, [](auto in){
			std::cout << in << std::endl;
		});
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
		curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
		auto err = curl_easy_perform(curl);
		return response;
	}
};