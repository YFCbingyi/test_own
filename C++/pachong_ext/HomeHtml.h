/*************************************************************************
	> File Name: HomeHtml.h
	> Author: 
	> Mail: 
	> Created Time: 2020年05月25日 星期一 18时03分07秒
 ************************************************************************/

#ifndef _HOMEHTML_H
#define _HOMEHTML_H

// #include "IHtml.h"
#include "StoryHtml.h"

class HomeHtml : public IHtml
{
public:
	HomeHtml(std::string html) : _html(html) {}
	~HomeHtml(){}
	void start(std::string &url) {
		std::string result;
		getHtmlData(url,result);
		std::cout << "url :" << url << std::endl;
		std::cout << "html :" << _html << std::endl;
		parse(result,_html);
		for(auto &t : _stories) {
			std::string folter = t.first;
			creatFolter(folter);
			StoryHtml story(t.first,t.second);
			story.start();
			// break;
		}
	}
private:
	void creatFolter(std::string &file)
    {
        std::string cmd = "mkdir " + file;
        ::system(cmd.c_str());
    }
	void parse(std::string &msg,std::string &url) {
		//遍历获取StoryHtml的链接集合
		htmlcxx::HTML::ParserDom parser;
		tree<HTML::Node> dom = parser.parseTree(msg);
		std::cout << "dom size " << dom.size() << std::endl;
		std::string end_page;
		std::string str = "/html/manhua/";
		for (auto t = dom.begin(); t != dom.end(); t++)
		{
			t->parseAttributes();
			
			if (t->isTag())
			{
				if(t->attribute("href").second.find(".html") != std::string::npos && t->attribute("href").second.find("manhua") != std::string::npos) {
						std::string story_html = t->attribute("href").second;
						story_html = story_html.substr(str.length(),story_html.length());
						story_html = url + story_html;
						t+=3;
						t->parseAttributes();
						std::string story_name = t->attribute("alt").second;
						_stories.insert(std::make_pair(story_name,story_html));
				}
			}
		}
	}

private:
	std::string _html;
	std::map<std::string,std::string> _stories;
};

#endif
