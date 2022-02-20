#include "solution.h"
#include "util.h"
#include <queue>
#include <map>
#include <algorithm>
#include <string>
#include <queue>
#include <sstream>
using namespace sol1236;
using namespace std;

/*takeaways
  - typical BSF - the only thing you need to pay attention
    is that only those adjacent nodes that have the same
    host name as the visiting node can be considered as
    visiting node's neighbors
*/

HtmlParser::HtmlParser(vector<string> urls, vector<vector<int>> edges)
{
  for (auto e : edges)
    _urls[urls[e[0]]].push_back(urls[e[1]]);
}

vector<string> HtmlParser::getUrls(string url)
{
  return _urls[url];
}

vector<string> Solution::crawl(string startUrl, HtmlParser htmlParser)
{
  auto result = vector<string>();
  auto q = queue<string>();
  auto visited = unordered_set<string>();

  q.push(startUrl);

  auto host = [](auto &s)
  {
    auto input = stringstream(s);
    string token;
    getline(input, token, '/'); // skip http:
    getline(input, token, '/'); // skip ''
    getline(input, token, '/');
    return token;
  };

  while (!q.empty())
  {
    auto url = q.front();
    q.pop();
    visited.insert(url);
    result.push_back(url);
    for (auto u : htmlParser.getUrls(url))
      if (visited.count(u) == 0 && host(url) == host(u))
        q.push(u);
  }
  return result;
}
