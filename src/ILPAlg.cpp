#include "ILPAlg.h"

bool better(const Node& a, const Node& b) {
    if (a.totalProfit != b.totalProfit)
        return a.totalProfit > b.totalProfit;
    if (a.palletCount != b.palletCount)
        return a.palletCount < b.palletCount;
    return a.idSum < b.idSum;
}

double bound(const Node& node, const Truck& truck, const vector<Pallet>& pallets, int n) {
    if (node.totalWeight >= truck.getMaxWeight())
        return 0.0;

    double profitBound = node.totalProfit;
    int weight = node.totalWeight;

    for (int i = node.level; i < n; ++i) {
        int w = pallets[i].getPalletWeight();
        int p = pallets[i].getPalletValue();
        if (weight + w <= truck.getMaxWeight()) {
            weight += w;
            profitBound += p;
        } else {
            int remain = truck.getMaxWeight() - weight;
            profitBound += p * (double(remain) / w);
            break;
        }
    }
    return profitBound;
}

vector<Pallet> ILPAlgorithm(Truck& truck, vector<Pallet>& pallets) {
    // sort by ratio and if tie sort by id 
    sort(pallets.begin(), pallets.end(), [](auto& a, auto& b) {
        double r1 = double(a.getPalletValue()) / a.getPalletWeight();
        double r2 = double(b.getPalletValue()) / b.getPalletWeight();
        if (r1 != r2) return r1 > r2;
        return a.getPalletId() < b.getPalletId();
    });

    int n = pallets.size();
    //keep track of best ress
    Node bestNode= {-1, 0, 0, 0, 0, {}, 0.0};

    priority_queue<Node> pq;
    // init root node
    Node root;
    root.level = 0;
    root.totalWeight = 0;
    root.totalProfit = 0;
    root.palletCount = 0;
    root.idSum = 0;
    root.path.clear();
    root.bound = bound(root, truck, pallets, n);
    pq.push(root);

    while (!pq.empty()) {
        Node curr = pq.top();
        pq.pop();

        // prune if bound is lower than the current best total profit
        if (curr.bound < bestNode.totalProfit)
            continue;

        // if no more nodes to explore, update best node
        if (curr.level == n) {
            if (curr.totalWeight <= truck.getMaxWeight() && better(curr, bestNode))
                bestNode= curr;
            continue;
        }

        int i = curr.level;
        int w = pallets[i].getPalletWeight();
        int p = pallets[i].getPalletValue();
        int id = pallets[i].getPalletId();

        // scenario 1: Include pallet i 
        if (curr.totalWeight + w <= truck.getMaxWeight()) {
            Node inc = curr;
            inc.level = i + 1;
            inc.totalWeight += w;
            inc.totalProfit += p;
            inc.palletCount += 1;
            inc.idSum += id;
            inc.path.push_back(i);
            inc.bound = bound(inc, truck, pallets, n);

            if (better(inc, bestNode))
                bestNode= inc;

            if (inc.bound >= bestNode.totalProfit)
                pq.push(inc);
        }

        // scenario 2 : dont include pallet i
        Node exc = curr;
        exc.level = i + 1;
        exc.bound = bound(exc, truck, pallets, n);

        if (exc.bound >= bestNode.totalProfit)
            pq.push(exc);
    }

    vector<Pallet> res;
    for (int idx : bestNode.path)
        res.push_back(pallets[idx]);

    //sometimes the res vector comes inverted other times no
    sort(res.begin(), res.end(), [](const Pallet& a, const Pallet& b) {
        return a.getPalletId() < b.getPalletId();
    });

    return res;
}
