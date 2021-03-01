#include <bits/stdc++.h>
using namespace std;

struct Node {
    int type;
    pair<int,int> __str__;
    vector<Node*> val_list;
    map<string, Node*> val_map;

    Node (int tp) : type(tp) {}

    string repr (string &str) {
        return str.substr(__str__.first, __str__.second);
    }

    Node *operator[] (string idx) {
        assert(type == 3 || type == 4);
        if (type == 3) return val_list[stoi(idx)];
        else return val_map[idx];
    }
};

int skip_space (string &str, int st) {
    while (st < int(str.size()) && str[st] == ' ') st++;
    return st;
}

pair<Node*, int> build(string &str, int idx);

pair<Node*, int> parse_map (string &str, int idx) {
    Node *res = new Node(4);

    int hd = idx;
    idx++;
    while (true) {
        idx = skip_space(str, idx);

        // parse key
        assert(str[idx] == '"');
        int key_ed = int(find(str.begin()+idx+1, str.end(), '"') - str.begin());
        string key = str.substr(idx+1, key_ed-idx-1);

        assert(str[key_ed] == '"');
        idx = skip_space(str, key_ed+1);
        assert(str[idx] == ':');
        idx = skip_space(str, idx+1);

        // parse value
        pair<Node*, int> val = build(str, idx);
        res->val_map[key] = val.first;
        idx = val.second;

        // next
        idx = skip_space(str, idx);
        if (str[idx] == '}') {
            break;
        }  else {
            assert(str[idx] == ',');
            idx++;
        }
    }
    res->__str__ = pair<int,int>(hd, idx-hd+1);
    return {res, idx+1};
}

pair<Node*, int> parse_list (string &str, int idx) {
    Node *res = new Node(3);
    int hd = idx;
    idx++;
    while (true) {
        // elements
        pair<Node*, int> val = build(str, idx);
        res->val_list.emplace_back(val.first);
        idx = val.second;

        // next
        idx = skip_space(str, idx);
        if (str[idx] == ']') {
            break;
        }  else {
            assert(str[idx] == ',');
            idx++;
        }
    }
    res->__str__ = pair<int,int>(hd, idx-hd+1);
    return {res, idx+1};
}

pair<Node*, int> parse_string (string &str, int idx) {
    Node *res = new Node(1);
    int ed = int(find(str.begin()+idx+1, str.end(), '"') - str.begin());
    res->__str__ = pair<int,int>(idx, ed-idx+1);
    return {res, ed+1};
}

pair<Node*, int> parse_bool (string &str, int idx) {
    Node *res = new Node(2);
    int ed = int(find(str.begin()+idx+1, str.end(), 'e') - str.begin());
    res->__str__ = pair<int,int>(idx, ed-idx+1);
    return {res, ed+1};
}

pair<Node*, int> parse_int (string &str, int idx) {
    Node *res = new Node(2);
    int ed = idx;
    while (ed < int(str.size()) && isdigit(str[ed])) ed++;
    res->__str__ = pair<int,int>(idx, ed-idx);
    return {res, ed};
}

pair<Node*,int> build (string &str, int idx) {
    idx = skip_space(str, idx);
    if (str[idx] == '{') {
        return parse_map(str, idx);
    } else if (str[idx] == '[') {
        return parse_list(str, idx);
    } else if (str[idx] == '"') {
        return parse_string(str, idx);
    } else if (str[idx] == 't' || str[idx] == 'f') {
        return parse_bool(str, idx);
    } else {
        return parse_int(str, idx);
    }
}

string query (Node *cur, string &str, string::iterator ptr, string &json) {
    if (ptr == str.end()) {
        return cur->repr(json);
    } else {
        auto ed = find(ptr, str.end(), ']');
        string index = str.substr(ptr-str.begin()+1, ed-ptr-1);
        if (index[0] == '"') index = index.substr(1, index.size()-2);
        return query((*cur)[index], str, ed+1, json);
    }
}

void clear (Node *cur) {
    for (auto ptr : cur->val_list) {
        clear(ptr);
        delete ptr;
    }
    for (auto pa : cur->val_map) {
        clear(pa.second);
        delete pa.second;
    }
    cur->val_list.clear();
    cur->val_map.clear();
}

int main () {
    string json_string;
    getline(cin,json_string);
    pair<Node*, int> parsed = build(json_string, 0);
    assert(parsed.second == int(json_string.size())); // assert parsed all

    string query_string;
    getline(cin, query_string);
    auto bg = find(query_string.begin(), query_string.end(), '['); // remove obj prefix
    cout << query(parsed.first, query_string, bg, json_string) << endl;

    clear(parsed.first); // free the memory
    delete parsed.first;

}
/*
{"skps1450":"GG"}
obj["skps1450"]

{"Kirito":[{"Busna":"OAO"},"startburst"]}
obj["Kirito"][0]
*/
