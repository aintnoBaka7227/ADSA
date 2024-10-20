// #include <iostream>
// #include <sstream> 
// #include <vector> 
// #include <string>
// #include <algorithm>

// int char_to_cost(char c) {
//     if ('A' <= c && 'Z' >= c) {
//         return c - 'A';
//     }
//     return c - 'a' + 26;
// }

// class UnionFind {
//     private: 
//     std::vector<int> parent;
//     std::vector<int> rank;
//     friend class RoadGraph;
//     public: 
//     UnionFind(int size) {
//         parent.resize(size,-1);
//         rank.resize(size,1);
//     }

//     int find(int i) {
//         if (parent[i] == -1) {
//             return i;
//         }
//         return parent[i] = find(parent[i]);
//     }

//     void unite(int i, int j) {
//         int root_i = find(i);
//         int root_j = find(j);

//         if (root_i != root_j) {
//             if (rank[root_i] > rank[root_j]) {
//                 parent[root_j] = root_i;
//             }
//             else if (rank[root_i] < rank[root_j]) {
//                 parent[root_i] = root_j;
//             }
//             else {
//                 parent[root_j] = root_i;
//                 rank[root_i]++;
//             }
//         }
//     }
// };

// int min_cost() {
    //     if (n == 1) {
    //         return 0;
    //     }
    //     for (int i = 0; i < n; i++) {
    //         for (int j = i + 1; j < n; j++) {
    //             if (country[i][j] == '1') {
    //             }
    //             edges.push_back({char_to_cost(build[i][j]), {i,j}});
    //         }
    //     }
    //     std::sort(edges.begin(), edges.end());

    //     UnionFind union_find(n);
    //     int total_cost = 0;
    //     std::vector<std::string> reconstructed = country;
    //     for (int i = 0; i < n; i++) {
    //         for (int j = 0; j < n; j++) {
    //             reconstructed[i][j] = '0';
    //         }
    //     }

    //     for (auto edge : edges) {
    //         int temp_cost = edge.first;
    //         int city1 = edge.second.first;
    //         int city2 = edge.second.second;

    //         if (union_find.find(city1) != union_find.find(city2)) {
    //             union_find.unite(city1, city2);
    //             reconstructed[city1][city2] = reconstructed[city2][city1] = '1';
    //             total_cost += temp_cost;
    //         }
    //     }
    //     return total_cost;
    // }

#include <iostream>
#include <vector>
#include <string>
#include <sstream> 
#include <tuple>
#include <algorithm> 
using namespace std;

class Roads{
    private:
        vector<vector<int>> country;
        vector<vector<int>> build;
        vector<vector<int>> destroy;

        void buildCountry(string s){
            country.clear(); 
            stringstream ss(s);
            string segment;
            while (getline(ss, segment, ',')) {
                vector<int> row;
                for (char c : segment) {
                    row.push_back(c - '0');
                }

                country.push_back(row);
            }
        }

        void buildBuild(string s){
            build.clear(); 
            stringstream ss(s);
            string row;
            while (getline(ss, row, ',')) {
                vector<int> rowValues;
                for (char cost : row) {
                    if (cost >= 'A' && cost <= 'Z') {
                        rowValues.push_back(cost - 'A');  // 'A' = 0, 'B' = 1, ..., 'Z' = 25
                    } else if (cost >= 'a' && cost <= 'z') {
                        rowValues.push_back(cost - 'a' + 26);  // 'a' = 26, 'b' = 27, ..., 'z' = 51
                    }
                }
                build.push_back(rowValues);
            }
        }

        void buildDestroy(string s){
            destroy.clear(); 
            stringstream ss(s);
            string row;
            while (getline(ss, row, ',')) {
                vector<int> rowValues;
                for (char cost : row) {
                    if (cost >= 'A' && cost <= 'Z') {
                        rowValues.push_back(cost - 'A'); 
                    } else if (cost >= 'a' && cost <= 'z') {
                        rowValues.push_back(cost - 'a' + 26); 
                    }
                }
                destroy.push_back(rowValues);
            }
        }

       
        int addEdge(vector<vector<int>>& toDestroy, int i, int j, int cost){
            if(toDestroy[i][j] == 1){
                return cost;   
            }
            toDestroy[i][j] = 1;
            toDestroy[j][i] = 1; 
            for(int x = 0; x < toDestroy.size(); x++){
                for(int y = 0; y < toDestroy.size(); y++){
                    for(int z = 0; z < toDestroy.size(); z++){
                        if(toDestroy[x][z] == 1 && toDestroy[z][y] == 1 && x!= y){
                            toDestroy[x][y] = 1; 
                        }
                    }
                }
            }
            return 0; 
        }

        int addEdgeToBuild(vector<vector<int>>& toDestroy, int i, int j, int cost){
            if(toDestroy[i][j] == 1){
                return 0;   
            }
            toDestroy[i][j] = 1;
            toDestroy[j][i] = 1; 
            for(int x = 0; x < toDestroy.size(); x++){
                for(int y = 0; y < toDestroy.size(); y++){
                    for(int z = 0; z < toDestroy.size(); z++){
                        if(toDestroy[x][z] == 1 && toDestroy[z][y] == 1 && x != y){
                            toDestroy[x][y] = 1; 
                        }
                    }
                }
            }
            return cost; 
        }

    public:
        int reconstruct(string c, string b, string d){
            buildCountry(c);
            buildBuild(b);
            buildDestroy(d); 
            vector<pair<int, pair<int,int>>> costDestroy;
            vector<pair<int, pair<int,int>>> costBuild;
            for(int i = 0; i < destroy.size() - 1; i++){
                for(int j = i + 1; j < destroy.size(); j++){
                    pair<int,int> point = make_pair(i, j); 
                    pair<int,pair<int,int>> costD = make_pair(destroy[i][j], point); 
                    pair<int,pair<int,int>> costB = make_pair(build[i][j], point); 
                    costDestroy.push_back(costD); 
                    costBuild.push_back(costB);
                }
            }
            sort(costDestroy.begin(), costDestroy.end());
            sort(costBuild.begin(), costBuild.end()); 

            int cost = 0; 
            vector<vector<int>> toDestroy(country.size(), vector<int>(country.size(), 0));
            for(int x = costDestroy.size() - 1; x > -1 ; x--){
                pair<int,int> p = costDestroy[x].second;
                if(country[p.first][p.second] == 1){
                    cost = cost + addEdge(toDestroy, p.first, p.second, costDestroy[x].first); 
                }
            }

            for(int x = 0; x < costBuild.size() ; x++){
                pair<int,int> p = costBuild[x].second;
                if(country[p.first][p.second] == 0){
                    cost = cost + addEdgeToBuild(toDestroy, p.first, p.second, costBuild[x].first); 
                }
            }

            return cost; 
        }

}; 

void parseLine(const std::string& line, std::string& c, std::string& b, std::string& d) {
    istringstream stream(line);
    getline(stream, c, ' '); // Get first part (c)
    getline(stream, b, ' '); // Get second part (b)
    getline(stream, d, ' '); // Get third part (d)
}

int main(){
    string input;
    getline(cin, input);
    string c, b, d;
    parseLine(input, c, b, d);
    Roads r;
    cout << r.reconstruct(c, b, d);
}   
