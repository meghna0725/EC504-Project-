#include <iostream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <vector>
#include<fstream>


using namespace std;

vector<unordered_map<string, int>> tweets;
vector<unordered_map<string, int>> tweetsCopy;
vector<int> top10;

static int swapCount = 0;


//unordered_map<unordered_map<string, int>, int> matches;


// count unique words in input file line by line and add to map
void calcSimilarities(string s, vector<unordered_map<string, int>>& t ) {
 
    int sum = 0;
    cout << "_________________\n"<< s;

    for (int i = 0; i < t.size(); i++) {
        unordered_map<string, int> line;

        stringstream ss(s);
        string temp;

        

        line = t.at(i);
        cout << endl<<"tweet" << i << endl;

        while (getline(ss, temp, ' ')) {

            temp[0] = tolower(temp[0]);
            cout << temp << endl;

            if (line.find(temp)!= line.end() & line[temp]>= 0)
            {
                sum += line[temp];
            }

            cout << sum << " " << temp << line[temp] << endl;

        }
        
        t.at(i).insert(make_pair("***sum", sum));
        cout << "sum" << (t.at(i)).at("***sum")<< endl;
        sum = 0;
    }

}

unordered_map<string, int> countFrequency(string str, unordered_map<string, int> occ)
{

    stringstream ss(str);
    int count = 0;

    string token;

    while (getline(ss, token, ' '))
    {
        token[0] = tolower(token[0]);

        if (occ.find(token) != occ.end() & occ[token]<=0)
        {

            occ.insert(make_pair(token, 1));
        }

        else
        {
            occ[token]++;
            
        }

        cout << token << occ[token] << endl;
        
    }

    return occ;
}

void swap(int *a,  int* b)
{
    swapCount++;
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

void quicksort(int* tweetIndex, int* a, int l, int r)
{
    int i, j, v;

    if (r >= l)
    {
        v = a[r]; i = l - 1; j = r;
        for (;;)
        {
            while (a[++i] < v);
            while (a[--j] > v);
            if (i >= j) break;
            swap(&a[i], &a[j]);
            swap(&tweetIndex[i], &tweetIndex[j]);
        }
        swap(&a[i], &a[r]);
        swap(&tweetIndex[i], &tweetIndex[r]);
        quicksort(tweetIndex,a, l, i - 1);
        quicksort(tweetIndex,a, i + 1, r);
    }

}

void printMap(unordered_map<string, int> occurences)
{
    // Get an iterator pointing to begining of map
    unordered_map<string, int>::iterator it = occurences.begin();
    // Iterate over the map using iterator
    while (it != occurences.end())
    {
        std::cout << it->first << " :: " << it->second << std::endl;
        it++;
    }
}


int main(int argc, char* argv[])
{
    ifstream inFile;
    //char* infile;
    string str = "one one two three three \n five six seven";
    string str2 = " This one is ready for Google";
    unordered_map<string, int> occ;
    int count = 0;

    int countStr = 0;
    unordered_map<int, string> arrT;
 
    inFile.open(argv[1]);
  
    cout << "Search for a tweet:";
    cin >> str2;
    

    while (getline(inFile, str, '\n')) {

        tweets.push_back(countFrequency(str, occ));
        arrT[countStr]= str;
        countStr++;

        cout << str << endl;
    }

   
    //tweetsCopy = tweets;

    calcSimilarities(str2,tweets);

    int* top10 = new int[tweets.size()];
    int* top10Num = new int[tweets.size()];

    for (int i = 0; i < tweets.size(); i++) {

        top10[i] = tweets[i].at("***sum");
        top10Num[i] = i;
    }

   quicksort(top10Num,top10, 0, tweets.size()-1);
  
   cout << "\n\n Here are the top 10 tweets:" << endl;

   int count10 = 0;
   for (int i = tweets.size()-1; i > 0 && count10<=10; i--) {

       count10++;

       cout<<arrT[i]<<"\n\n";
   }

    return 0;
}