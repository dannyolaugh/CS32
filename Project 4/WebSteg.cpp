#include "provided.h"
#include <string>
#include "http.h"
using namespace std;

bool WebSteg::hideMessageInPage(const string& url, const string& msg, string& host)
{
    string text;
    if(!HTTP().get(url, text))
    {
        return false;
    }
    Steg::hide(text, msg, host);
    return true;
}

bool WebSteg::revealMessageInPage(const string& url, string& msg)
{
    string text;
    if(!HTTP().get(url, text))
        return false;
    Steg::reveal(text, msg);
    return  true;
}
