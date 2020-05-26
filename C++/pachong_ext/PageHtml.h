/*************************************************************************
	> File Name: PageHtml.h
	> Author: 
	> Mail: 
	> Created Time: 2020年05月25日 星期一 18时02分48秒
 ************************************************************************/

#ifndef _PAGEHTML_H
#define _PAGEHTML_H
#include "IHtml.h"

class PageHtml : public IHtml
{
public:
	PageHtml(std::string name,std::string html) : _name(name), _html(html) {}
	~PageHtml(){}
	void start() {
		std::string result;
		getHtmlData(_html,result);
		parse(result);
		for(auto &t : _pictures) {
			std::string path = "./"+_name +"/"+ t;
			download(t,path);
		}
	}
private:
	void parse(std::string &msg) {
		//遍历获取pageHtml下图片的链接集合
	}
private:
	std::string _name,_html;
	std::vector<std::string> _pictures;
};

#endif
