#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include <algorithm>
#include <bitset>
#include <vector>
#include <string>

using namespace std;

ifstream fin("router.in");
ifstream fout("router.out");

#define maxn (500010)
#define bSize (10000)
#define VBOUND (500000)

void Msg(int pct, string msg )
{
    cout << pct << ' ' << msg << endl;
    try
    {
        fin.close();
        fout.close();
    }
    catch (string ex) {}
    exit(0);
}

int n, ntot, m, edgeBudget, powerBudget, score;
vector<int> v[maxn], vinv[maxn];

void readFiles()
{
    if (!fin)
        Msg(0, "Input file is missing");

     if(!fout)
        Msg(0, "Missing output file router.out!");

    if (!(fin>>n>>edgeBudget>>powerBudget))
        Msg(0, "Input file corrupted!");
    if (n < 1 || n > 10000)
        Msg(0, "Input file corrupted, N out of bounds!");

    if(!(fout>>ntot))
        Msg(0, "Corrupted output file router.out!");
    if(!(fout>>m))
        Msg(0, "Corrupted output file router.out!");

    if(ntot>VBOUND)
        Msg(0, "WA: Vertex number out of bounds!");

    if(m > edgeBudget)
        Msg(0, "WA: Edge budget exceeded!");

    for(int i=0; i<m; ++i)
    {
        int a, b;
        if(!(fout>>a))
            Msg(0, "Missing edge from output file!");
        if(!(fout>>b))
            Msg(0, "Missing edge from output file!");

        if(a<=0 || a>ntot || b<=0 || b>ntot)
            Msg(0, "WA: Invalid vertex ID!");

        if(a>n && a<=2*n)
            Msg(0, "WA: Out-going edge from output vertex!");

        if(b>0 && b<=n)
            Msg(0, "WA: In-going edge to input vertex!");

        v[a].push_back(b);
        vinv[b].push_back(a);
    }
}

vector<int> toposort()
{
    int degree[ntot+1];

    for(int i=1; i<=ntot; ++i)
        degree[i]=0;

    for(int i=1; i<=ntot; ++i)
        for(vector<int> :: iterator it = v[i].begin(); it != v[i].end(); ++it)
            ++degree[*it];

    vector<int> q;

    for(int i=1; i<=ntot; ++i)
        if(degree[i]==0)
            q.push_back(i);

    for(int i=0; i<q.size(); ++i)
    {
        int nod=q[i];

        for(vector<int> :: iterator it = v[nod].begin(); it != v[nod].end(); ++it)
        {
            --degree[*it];
            if(degree[*it]==0)
                q.push_back(*it);
        }
    }

    if(q.size()!=ntot)
        Msg(0, "WA: Graph is not acyclic");

    return q;
}

bitset<bSize> inAccess[maxn], outAccess[maxn];

void judge(vector<int> nodes)
{
    for(int i=1; i<=n; ++i)
    {
        inAccess[i][i-1]=1;
        outAccess[n+i][i-1]=1;
    }

    for(vector<int> :: iterator node = nodes.begin(); node != nodes.end(); ++node)
    {
        for(vector<int> :: iterator anc = vinv[*node].begin(); anc != vinv[*node].end(); ++anc)
        {
            if((inAccess[*node] & inAccess[*anc]).any())
                Msg(0, "WA: Path between input / output is not unique"); // no unique path

            inAccess[*node] |= inAccess[*anc];
        }
    }

    reverse(nodes.begin(), nodes.end());

    for(vector<int> :: iterator node = nodes.begin(); node != nodes.end(); ++node)
    {
        for(vector<int> :: iterator anc = v[*node].begin(); anc != v[*node].end(); ++anc)
        {
            if((outAccess[*node] & outAccess[*anc]).any())
                Msg(0, "WA: Path between input / output is not unique"); // no unique path

            outAccess[*node] |= outAccess[*anc];
        }
    }

    for(int i=1; i<=n; ++i)
    {
        if(outAccess[i].count() != n)

            Msg(0, "WA: Unconnected pair of input "+to_string(outAccess[i].count()));
        if(inAccess[n+i].count() != n)
            Msg(0, "WA! Unconnected pair of output"+to_string(n+i));
    }

    int pMax = 0;

    for(int i=1; i<=ntot; ++i)
        pMax = max(pMax, int(inAccess[i].count() * outAccess[i].count()));

    if(pMax > powerBudget)
        Msg(0, "WA! Power budget exceeded! " + to_string(pMax));
    Msg(score, "OK!");
}

int main(int argc, char *argv[])
{
    score = atoi(argv[4]);
    readFiles();
    judge(toposort());

	return 0;
}
