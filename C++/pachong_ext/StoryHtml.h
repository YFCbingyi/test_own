/*************************************************************************
	> File Name: StoryHtml.h
	> Author: 
	> Mail: 
	> Created Time: 2020年05月25日 星期一 18时02分58秒
 ************************************************************************/

#ifndef _STORYHTML_H
#define _STORYHTML_H

#include "PageHtml.h"
// #include "IHtml.h"
class StoryHtml : public IHtml
{
public:
	StoryHtml(std::string name,std::string html) : _name(name),_html(html){}
	~StoryHtml(){}
	void start() {
		std::string result;
		getHtmlData(_html,result);
		std::cout << "html :" << _html << std::endl;
		parse(result);
		for(auto &t : _pages) {
			std::cout << t << std::endl;
			PageHtml page(_name,t);
			page.start();
			// break;
		}
	}
private:
	void parse(std::string &msg) {
		//遍历获取PageHtml的链接集合
		htmlcxx::HTML::ParserDom parser;
		tree<HTML::Node> dom = parser.parseTree(msg);
		for (auto t = dom.begin(); t != dom.end(); t++)
		{
			t->parseAttributes();
			
			if (t->isTag()){
				
			} else if(t->isComment()){
 
			} else {
				if((t->text().find("共") != std::string::npos) && (t->text().find("页") != std::string::npos)) {
					std::string pa = t->text().substr(t->text().find("共") + 3, t->text().find("页") - 3);
                    int pageCount = std::stoi(pa);
					std::string str = ".html";
					std::string page_html_base = _html.substr(0,_html.length()-str.length());
					_pages.push_back(_html);
					for(int i = 2;i <=pageCount ; i++) {
						std::string page_html = page_html_base + "_" + std::to_string(i) + str;
						_pages.push_back(page_html);
					}
				}
			}
		}
	}
private:
	std::string _name,_html;
	std::vector<std::string> _pages;
};


#endif
