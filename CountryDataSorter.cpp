#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>

using namespace std;

class Country {
public:
    string name;
    int rank;
    double score;
    double change;
    
    Country() : name(""), rank(0), score(0.0), change(0.0) {}

    Country(string n, int r, double s, double c) {
        name = n;
        rank = r;
        score = s;
        change = c;
    }
};


class DatasetSort {
private:
    vector<Country> data;
    
public:
    DatasetSort(string filename) {
        ifstream file(filename);
        if (file.is_open()) {
            string line;
            while (getline(file, line)) {
                string name;
                int rank;
                double score;
                double change;
                string temp;
                
                int pos = line.find(",");
                name = line.substr(0, pos);
                line.erase(0, pos+1);
                
                pos = line.find(",");
                temp = line.substr(0, pos);
                rank = stoi(temp);
                line.erase(0, pos+1);
                
                pos = line.find(",");
                temp = line.substr(0, pos);
                score = stod(temp);
                line.erase(0, pos+1);
                
                change = stod(line);
                
                data.push_back(Country(name, rank, score, change));
            }
            file.close();
        } else {
            cout << "Error: could not open file." << endl;
        }
    }
    
    void selectionSort(string criteria) {
        int n = data.size();
        for (int i = 0; i < n-1; i++) {
            int min_idx = i;
            for (int j = i+1; j < n; j++) {
                if (criteria == "name") {
                    if (data[j].name < data[min_idx].name) {
                        min_idx = j;
                    }
                } else if (criteria == "rank") {
                    if (data[j].rank < data[min_idx].rank) {
                        min_idx = j;
                    }
                } else if (criteria == "score") {
                    if (data[j].score < data[min_idx].score) {
                        min_idx = j;
                    }
                } else if (criteria == "change") {
                    if (data[j].change < data[min_idx].change) {
                        min_idx = j;
                    }
                }
            }
            swap(data[i], data[min_idx]);
        }
    }
    
    void mergeSort(string criteria, int l, int r) {
        if (l < r) {
            int m = (l+r)/2;
            mergeSort(criteria, l, m);
            mergeSort(criteria, m+1, r);
            merge(criteria, l, m, r);
        }
    }
    
    void merge(string criteria, int l, int m, int r) {
        int n1 = m-l+1;
        int n2 = r-m;
        vector<Country> left(n1);
        vector<Country> right(n2);
        for (int i = 0; i < n1; i++) {
            left[i] = data[l+i];
        }
        for (int i = 0; i < n2; i++) {
            right[i] = data[m+1+i];
        }
        int i = 0;
        int j = 0;
        int k = l;
        while (i < n1 && j < n2) {
            if (criteria == "name") {
                                if (left[i].name <= right[j].name) {
                    data[k] = left[i];
                    i++;
                } else {
                    data[k] = right[j];
                    j++;
                }
            } else if (criteria == "rank") {
                if (left[i].rank <= right[j].rank) {
                    data[k] = left[i];
                    i++;
                } else {
                    data[k] = right[j];
                    j++;
                }
            } else if (criteria == "score") {
                if (left[i].score <= right[j].score) {
                    data[k] = left[i];
                    i++;
                } else {
                    data[k] = right[j];
                    j++;
                }
            } else if (criteria == "change") {
                if (left[i].change <= right[j].change) {
                    data[k] = left[i];
                    i++;
                } else {
                    data[k] = right[j];
                    j++;
                }
            }
            k++;
        }
        while (i < n1) {
            data[k] = left[i];
            i++;
            k++;
        }
        while (j < n2) {
            data[k] = right[j];
            j++;
            k++;
        }
    }
    
    void printTable(int numCountries, bool reverse) {
        if (reverse) {
            // at starting reverse(data.begin(), data.end());
        }
        cout << "+-------------+----------------+----------------+----------------+" << endl;
        cout << "| Country     | EPI 2022 Rank  | EPI Score      | 10-Year Change |" << endl;
        cout << "+-------------+----------------+----------------+----------------+" << endl;
        for (int i = 0; i < numCountries && i < data.size(); i++) {
            printf("| %-12s | %14d | %14.2f | %14.2f |\n", data[i].name.c_str(), data[i].rank, data[i].score, data[i].change);
        }
        cout << "+-------------+----------------+----------------+----------------+" << endl;
    }
    
    void saveToFile(string filename) {
        ofstream file(filename);
        if (file.is_open()) {
            for (int i = 0; i < data.size(); i++) {
                file << data[i].name << "," << data[i].rank << "," << data[i].score << "," << data[i].change << endl;
            }
            file.close();
        } else {
            cout << "Error: could not open file." << endl;
        }
    }
};

int main() {
    DatasetSort ds("data.csv");
    
    string sortType;
    do {
        cout << "Please choose a sort type (selection or merge): ";
        cin >> sortType;
    } while (sortType != "selection" && sortType != "merge");
    
    string criteria;
    do {
        cout << "Please choose a sorting criteria (name, rank, score, or change): ";
        cin >> criteria;
    } while (criteria != "name" && criteria != "rank" && criteria != "score" && criteria != "change");
    
    string direction;
    do {
        cout << "Please choose a sorting direction (ascending or descending): ";
        cin >> direction;
    } while (direction != "ascending" && direction != "descending");
    
    bool reverse = (direction == "descending");
    
        int numCountries;
    do {
        cout << "Please choose a number of countries to output (10, 20, 50, or 100): ";
        cin >> numCountries;
    } while (numCountries != 10 && numCountries != 20 && numCountries != 50 && numCountries != 100);
    
    string reverseChoice;
    do {
        cout << "Do you want to output the list in reverse order? (yes or no): ";
        cin >> reverseChoice;
    } while (reverseChoice != "yes" && reverseChoice != "no");
    
    reverse = (reverseChoice == "yes");
    
    do {
        cout << "Please choose a sorting algorithm (selection or merge): ";
        cin >> sortType;
    } while (sortType != "selection" && sortType != "merge");
    
    do {
        cout << "Please choose a sorting criteria (country, ranking, change, or score): ";
        cin >> criteria;
    } while (criteria != "country" && criteria != "ranking" && criteria != "change" && criteria != "score");
    
    if (sortType == "selection") {
        auto start = std::chrono::high_resolution_clock::now();
        ds.selectionSort(criteria);
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
        cout << "Selection sort took " << duration.count() << " milliseconds." << endl;
    } else {
        auto start = std::chrono::high_resolution_clock::now();
        ds.mergeSort(criteria, 0,criteria.length()-1);
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
        cout << "Merge sort took " << duration.count() << " milliseconds." << endl;
    }
    
    ds.printTable(numCountries, reverse);
    
    string saveChoice;
    do {
        cout << "Do you want to save the sorted list to a file? (yes or no): ";
        cin >> saveChoice;
    } while (saveChoice != "yes" && saveChoice != "no");
    
    if (saveChoice == "yes") {
        string filename;
        cout << "Please enter a filename to save to: ";
        cin >> filename;
        ds.saveToFile(filename);
    }
    
    string repeatChoice;
    do {
        cout << "Do you want to sort another list? (yes or no): ";
        cin >> repeatChoice;
    } while (repeatChoice != "yes" && repeatChoice != "no");
    
    if (repeatChoice == "yes") {
        main();
    }
    
    return 0;
}


