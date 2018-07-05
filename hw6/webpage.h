#ifndef WEB_PAGE_H
#define WEB_PAGE_H
#include <vector>
#include <map>
#include <set>
#include <string>

class WebPage{

	public:
		WebPage();
		~WebPage();
		void parse(const std::string &x, const std::string &file, WebPage &wp);
		void rank(WebPage &page, std::set<std::string> &result, int step_number, double probability, std::ofstream &out);
		void sigma(WebPage &wp, double initial_rank, double probability, int step_number, std::set<std::string> &result, std::map<std::string, double> &ranking);

		std :: map<std :: string, std :: set <std :: string> > keywords;
		std :: map<std :: string, std :: vector <std:: string> > links;
		std :: map <std :: string , std :: vector<std:: string> > text;
		std :: map<std::string, std::set<std::string> > incoming_links;
};
#endif
