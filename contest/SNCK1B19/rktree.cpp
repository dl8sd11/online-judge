#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp> // Common file
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std;

typedef tree<int,null_type,greater<int>,rb_tree_tag,tree_order_statistics_node_update> rktree;

int main() {
    rktree tr;
    tr.insert(1);
    tr.insert(2);
    tr.insert(3);
    tr.insert(4);
    tr.insert(5);
    tr.insert(6);

    cout<<*tr.find_by_order(3)<<endl;
    return 0;
}
