#include <iostream>
#include <unordered_map>
#include <vector>
#include <fstream>
#include <algorithm>
#include <climits>
#include <bits/stdc++.h>


#define hashmap unordered_map<char,node*>
using namespace std;
class node{
public:
    char data;
    hashmap h;
    bool isTerminal;
    string str;

    node(char d)
    {
        data =d;
        isTerminal = false;
        str="";
    }
};
class Trie{
    node* root;

public:
    Trie(){
        root=new node('\0');
    }
    /// Insertion
    void addWord(string word,string s)
    {
        node* temp=root;
        for(int i=0;word[i]!='\0';i++)
        {
            char ch=word[i];

            if(temp->h.count(ch) == 0)
            {
                node* child=new node(ch);
                temp->h[ch]=child;
                temp=child;
            }
            else{
                temp=temp->h[ch];
            }
        }
        temp->isTerminal=true;
        temp->str=s;
    }

    /// LookUp
    bool search(string word){
        node* temp=root;

        for(int i=0;word[i]!='\0';i++)
        {
            char ch=word[i];
            if(temp->h.count(ch)){
                temp=temp->h[ch];
            }
            else{
                return false;
            }

        }
        cout<<temp->str<<"\n\n\n\n";
        return temp->isTerminal;
    }
    


};
bool mySort(pair<string,int> p1,pair<string,int> p2){

    if(p1.second < p2.second){
        return true;
    }
    return false;

}
vector<string> searchSuggestion(string word,vector<string> allWords){
        
    // node* temp = root;

    // for(int i=0;word[i]!='\0';i++){
    //     char ch = word[i];
    //     if(temp->h.count(ch)){
    //         temp=temp->h[ch];
    //     }else{
    //         return vector<string>();
    //     }
        
    // }


    vector<pair<string,int> > tempWords;


    for(string s:allWords){
        
        if(word[0] == s[0]){
            tempWords.push_back(make_pair(s,1));
        }


    }
    allWords.clear();
    vector<pair<string,int> > tempWords2;

    for(pair<string,int> s:tempWords){
        string stg = s.first;
        int count=1;
        for(int i=0;i<word.length() && i<stg.length() ;i++){
            if(word[i] == stg[i]){
                count++;
            }else{
                break;
            }
        }
        tempWords2.push_back(make_pair(stg,count));

    }
    tempWords.clear();

    sort(tempWords2.begin(),tempWords2.end(),mySort);
  

    vector<string> final;
    int check=0;
    for(int i=tempWords2.size()-1;i>=0;i--){

        if(check<10){
            final.push_back(tempWords2[i].first);
            check++;
            continue;
        }
        break;

    }
    tempWords2.clear();
    
    
    return final;
    


}

// void suggestions(Trie t,string s,vector<string> allWords){

    
//     Trie crawl = t;

//     // sabse pehla letter utha string ka search kr saare words daal de
//     // first+second word uthao
//     vector<string> final;
//     string temp;

//     for(int i=0;i<s.length();i++){

//         for(int j=0;j<=i;j++){
//             temp.push_back(s[j]);
//         }


//         vector<string> loop = searchSuggestion(temp,allWords);
//         for(int i=0;i<loop.size();i++){
//             final.push_back(loop[i]);
//         }
        
//         temp.clear();

//     }

//     // manage operations with final
//     ;



// }
std::ostream& bold_on(std::ostream& os)
{
    return os << "\e[1m";
}

std::ostream& bold_off(std::ostream& os)
{
    return os << "\e[0m";
}
void format(){

    cout<<bold_on<<"Welcome to the Next Gen SPELL CHECKER!\n"<<bold_off;
    cout<<bold_on<<"Here you will get to know the meaning of the given word if exists,otherwise will printsome suggestions.\n"<<bold_off;


}
int max(int a,int b){

    if(a>b){
        return a;
    }
    return b;

}
int calculateLength(vector<string> v){

    int maxLength = INT_MIN;

    for(int i=0;i<v.size();i++){
        maxLength = max(maxLength,v[i].length());
    }
    return maxLength;

}
int main()
{
    // formatting

    format();
    
    cout<<"Enter your choice!\n";
    cout<<"Press 1 to enter a word!\n 2 to quit!\n";
    int choice;
    cin>>choice;
    
    while(choice != 2){


        vector<pair<string,string> > wordMeaning;

        string str = "data.json";
        ifstream is(str);
        char c;
        int check=0;
        string temp;
        bool lenaHai=false;
        pair<string,string> pairs;
        while(is.get(c)){

            if(lenaHai && c != '"'){
                temp.push_back(c);
            }
            
            else if(check == 0 && c == '"'){   // word has started

                lenaHai=true;
                check=1;

            }else if(check == 1 && c == '"'){  // word has ended

                lenaHai=false;
                check=2;
                pairs.first = temp;
                temp.clear();

            }else if(check == 2 && c == '['){  // meaning start

                if(is.get(c)){
                    if(c == '"'){
                        lenaHai=true;
                        check=3;
                    }
                }
            }else if(check == 3 && c == '"'){ // meaning end
                if(is.get(c)){
                    if(c == ']'){
                        lenaHai=false;
                        check=0;
                        pairs.second=temp;
                        temp.clear();

                        wordMeaning.push_back(make_pair(pairs.first,pairs.second));
                    }
                }
                

            }
      

        }

        is.close();


        // cout<<wordMeaning.size();
        vector<string> allWords;
        for(int i=0;i<wordMeaning.size();i++){
            allWords.push_back(wordMeaning[i].first);
        }


        Trie t;
        for(int i=0;i<wordMeaning.size();i++)
        {
            t.addWord(wordMeaning[i].first , wordMeaning[i].second);
        }
        // char searchWord[100];
        // cin.getline(searchWord,100);
        string searchWord;
        cin>>searchWord;


        if(t.search(searchWord)){
            //cout<<searchWord<<" found "<<endl;

        }
        else{
            cout<<"You have entered the wrong word!\n Following are the suggested words.\n\n\n\n";
            //vector<string> newWords = suggestions(t,searchWord);
            vector<string> newWords =  searchSuggestion(searchWord,allWords);
            //int maxLength = calculateLength(newWords);

            for(int i=0;i<10;i++){
                cout<<"*  "<<i+1<<"->"<<newWords[i];
                for(int i=0;i<20-newWords[i].length()-6;i++){
                    //cout<<" ";
                }
                 cout<<"\n";
            }

            // calculate maximum

            


        }
        cout<<"<============================================================>\n\n\n\n";
        cout<<"Enter your choice!\n";
        cout<<"Press 1 to enter a word!\n 2 to quit!\n";

        cin>>choice;


    }
    
    


    // end formatting

    return 0;

    
}

