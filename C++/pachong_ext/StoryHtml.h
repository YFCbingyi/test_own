/*************************************************************************
	> File Name: StoryHtml.h
	> Author: 
	> Mail: 
	> Created Time: 2020年05月25日 星期一 18时02分58秒
 ************************************************************************/

#ifndef _STORYHTML_H
#define _STORYHTML_H

#include "PageHtml.h"
class StoryHtml : public IHtml
{
public:
	StoryHtml(std::string name,std::string html) : _name(name),_html(html){}
	~StoryHtml(){}
	void start() {
		std::string result;
		getHtmlData(_html,result);
		parse(result);
		for(auto &t : _pages) {
			PageHtml page(_name,t);
			page.start();
		}
	}
private:
	void parse(std::string &msg) {
		//遍历获取PageHtml的链接集合
	}
private:
	std::string _name,_html;
	std::vector<std::string> _pages;
};


#endif
