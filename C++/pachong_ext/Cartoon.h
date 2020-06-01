/*************************************************************************
	> File Name: Cartoon.h
	> Author: 
	> Mail: 
	> Created Time: 2020年05月25日 星期一 18时03分24秒
 ************************************************************************/

#ifndef _CARTOON_H
#define _CARTOON_H

#include "HomeHtml.h"

// #include "IHtml.h"

class Cartoon : public IHtml
{
public:
	Cartoon() {}
	~Cartoon() {}

	void start(std::string &url)
	{
		std::string result;
		getHtmlData(url, result);
		parse(result,url);
		HomeHtml html(url);
		for (auto &t : _htmls)
		{
			// std::cout << " -- > " << t << std::endl;
			html.start(t);
			// break;
		}
	}

private:
	void parse(std::string &msg,std::string &url)
	{
		//遍历获取homeHtml链接集合
		htmlcxx::HTML::ParserDom parser;
		tree<HTML::Node> dom = parser.parseTree(msg);
		std::cout << "dom size " << dom.size() << std::endl;
		std::string end_page;
		for (auto t = dom.begin(); t != dom.end(); t++)
		{
			t->parseAttributes();
			
			if (t->isTag())
			{
				if((t->attribute("class").second == "pagenum extend") && (t->attribute("href").second.find(".html") != std::string::npos)){
					end_page = t->attribute("href").second;
				}
			}
		}
		std::string first = "list_1_";
		std::string end = ".html";
		std::string ll = end_page.substr(first.length(),end_page.length());
		std::string lll = ll.substr(0,ll.length()-end.length());
		int count_page = std::atoi(lll.c_str());

		for(int i = 1; i <= count_page ; i++) {
			std::string html = url + first + std::to_string(i) + end;
			_htmls.push_back(html);						
		}
	}

private:
	std::vector<std::string> _htmls;
};

#endif
