/*************************************************************************
	> File Name: Cartoon.h
	> Author: 
	> Mail: 
	> Created Time: 2020年05月25日 星期一 18时03分24秒
 ************************************************************************/

#ifndef _CARTOON_H
#define _CARTOON_H

#include "HomeHtml.h"

class Cartoon : public IHtml
{
public:
	Cartoon(){}
	~Cartoon(){}

	void start(std::string &url) {
		std::string result;
		getHtmlData(url,result);
		parse(result);
		for(auto &t : _htmls) {
			HomeHtml html(t);
			html.start();
		}
	}
private:
	void parse(std::string &msg) {
		//遍历获取homeHtml链接集合 
	}

private:
	std::vector<std::string> _htmls;	
};


#endif
