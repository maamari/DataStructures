#ifndef WEB_PAGE_H
#define WEB_PAGE_H
#include <set>
#include <string>
#include <vector>
#include <map>

class WebPage{

  public:
    WebPage();
    ~WebPage();
    void parse(std::string &doc, std::string &filename, WebPage &page);
    std :: map <std :: string , std :: vector<std:: string> > text;
    std :: map <std :: string, std :: set <std :: string> > wrds;
    std :: map <std :: string, std :: vector< std:: string> > links;
};
#endif
