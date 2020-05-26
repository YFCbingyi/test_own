/*************************************************************************
	> File Name: HomeHtml.h
	> Author: 
	> Mail: 
	> Created Time: 2020年05月25日 星期一 18时03分07秒
 ************************************************************************/

#ifndef _HOMEHTML_H
#define _HOMEHTML_H

#include "StoryHtml.h"

class HomeHtml : public IHtml
{
public:
	HomeHtml(std::string html) : _html(html) {}
	~HomeHtml(){}
	void start() {
		std::string result;
		getHtmlData(_html,result);
		parse(result);
		for(auto &t : _stories) {
			StoryHtml story(t.first,t.second);
			story.start();
		}
	}
private:
	void parse(std::string &msg) {
		//遍历获取StoryHtml的链接集合
	}

private:
	std::string _html;
	std::map<std::string,std::string> _stories;
};

#endif
