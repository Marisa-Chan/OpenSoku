#include <stdlib.h>
#include <stdio.h>
#include <list>
#include <string>
#include <array>
#include <map>

using namespace std;
//
//class node {
//public:
//    node *ret;
//};
//
//class func: node {
//public:
//    list<node *> blocks;
//};
//
//class

int maxlines = 200;

map<int, list<string>::iterator> labellist;

void trace_goto(list<string>::iterator it, list<string>::iterator en, list<string> &out)
{
    int brk = 0;
    out.push_back("{\n");
    while (it != en && out.size() < maxlines)
    {
        if (it->find("else") != it->npos && brk < 0)
        {
            it++;
            if (it->find("{") != it->npos)
                {
                    while (it->find("}") == it->npos)
                        it++;
                }
            it++;
            brk = 0;
        }

        if (brk < 0)
            brk = 0;

        if ((it->find("break;") != it->npos || it->find("return;") != it->npos) && brk <=0 )
        {
            out.push_back(*it);
            break;
        }

        if (it->find("{") != it->npos)
        {
            out.push_back(*it);
            brk++;
        }
        else if (it->find("}") != it->npos)
        {
            if (brk > 0)
                out.push_back(*it);
            brk --;
        }
        else if (it->find("goto") != it->npos)
        {
            int lbl;
            sscanf(it->c_str(),"%*[^g]goto LABEL_%d;", &lbl);
            map<int, list<string>::iterator>::iterator mapit = labellist.find(lbl);
            if (mapit != labellist.end())
            {
                trace_goto(mapit->second, en, out);
            }
            else
                out.push_back(*it);
            if (brk <= 0)
                break;
        }
        else if (it->find("LABEL") == it->npos)
            out.push_back(*it);

        it++;
    }
    out.push_back("}\n");
}


int main(int argc, const char **argv)
{
    if (argc == 1)
    {
	printf("usage infile.cpp [maxlines]\n");
	return 0;
    }
    FILE *f = fopen(argv[1],"r");

    char buf[1024];

    list<string> lines;

    while(!feof(f)) {
        fgets(buf, 1023, f);
        string line = string(buf);
        lines.push_back(string(buf));
    }
    fclose(f);
    
    if (argc == 3)
	maxlines = atoi(argv[2]);

    list<string>::iterator it;

    it = lines.begin();
    while (it != lines.end())
    {
        if (it->find("LABEL") != it->npos && it->find(':') != it->npos)
        {
            int labl;
            sscanf(it->c_str(), "LABEL_%d:", &labl);
            it++;
            labellist[labl] = it;
        }
        else
            it++;
    }

    map<int, list<string>::iterator>::iterator mapit = labellist.begin();

    map<int, list<string>> seqv;


    while (mapit != labellist.end())
    {
        //printf("%d\n",mapit->first);
        trace_goto(mapit->second, lines.end(), seqv[mapit->first]);
        mapit++;
    }

    it = lines.begin();
    list<string>::iterator prev = it;
    while (it != lines.end())
    {
        if (it->find("LABEL") == it->npos || it->find(':') == it->npos)
        {
            if (it->find("goto") != it->npos)
            {
            int lbl;
            sscanf(it->c_str(),"%*[^g]goto LABEL_%d;", &lbl);

            map<int, list<string>>::iterator maps = seqv.find(lbl);
            if (maps != seqv.end())
            {
                if (maps->second.size() < maxlines)
                {
                    if (prev->find("if") != prev->npos || prev->find("do") != prev->npos || prev->find("for") != prev->npos || prev->find("while") != prev->npos || prev->find("else") != prev->npos)
                    {
                        list<string>::iterator lblit = maps->second.begin();
                        while (lblit != maps->second.end())
                        {
                            printf("%s", lblit->c_str());
                            lblit++;
                        }
                    }
                    else
                    {
                        list<string>::iterator lblit = maps->second.begin();
                        lblit++;
                        while (lblit != maps->second.end())
                        {
                            list<string>::iterator pp = lblit;
                            lblit++;
                            if (lblit != maps->second.end())
                                printf("%s", pp->c_str());
                        }
                    }
                }
                else
                    printf("%s", it->c_str());
            }
            else
                    printf("%s", it->c_str());
            }
            else
                    printf("%s", it->c_str());
        }
        else
        {
            int labl;
            sscanf(it->c_str(), "LABEL_%d:", &labl);
            map<int, list<string>>::iterator maps = seqv.find(labl);
            if (maps != seqv.end())
            {
                if (maps->second.size() >= maxlines)
                    printf("%s", it->c_str());
            }
        }
        prev = it;
        it++;
    }

    //trace_goto(lines.begin(), lines.end());

    return 0;
}
