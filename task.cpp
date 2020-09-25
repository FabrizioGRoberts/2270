#include <iostream>
#include <iomanip>
#include <math.h>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

struct wordRecord
{
    string word;
    int count;
};

void getIgnoreWords(const char *ignoreWordFileName, string ignoreWords[])
{
    ifstream file;
    string holder;
    int i = 0;
    file.open(ignoreWordFileName);
    if (file.is_open())
    {
        while (getline(file,holder))
        {
           ignoreWords[i] = holder;
           i++;
        }
    }
    else
    {
        cout<< "Failed to open " << ignoreWordFileName <<endl;
    }
    file.close();
}

bool isIgnoreWord(string word, string ignoreWords[])
{
    for (int i=0; i<50; i++)
    {
        if (word == ignoreWords[i])
        {
            return 1;
        }
    }
    return 0;
}

int getTotalNumberNonIgnoreWords(wordRecord distinctWords[],int length)
{
    int sum = 0;
    for (int i=0; i<length; i++)
    {
        sum = distinctWords[i].count+sum;
    }
    return sum;
}

void sortArray(wordRecord distinctWords[], int length)
{
    
    for (int i=0; i<length-1; i++)
    {
        for (int j=0; j<length-i-1; j++)
        {
            if (distinctWords[j].count < distinctWords[j+1].count)
            {
                wordRecord holder = distinctWords[j];
                distinctWords[j] = distinctWords[j+1];
                distinctWords[j+1] = holder;
            }
            else if (distinctWords[j].count == distinctWords[j+1].count)
            {
                if(distinctWords[j].word>distinctWords[j+1].word)
                {
                    wordRecord holder = distinctWords[j];
                    distinctWords[j] = distinctWords[j+1];
                    distinctWords[j+1] = holder; 
                }
            }
            
        }
    }
}

void printTenFromN(wordRecord distinctWords[],int N, int totalNumWords)
{
    float occurProb=0.0;
    for (int i=N; i<N+10; i++)
    {
        occurProb = (float) distinctWords[i].count/(float)totalNumWords;
        cout<<fixed<<setprecision(5)<<occurProb<<" - "<< distinctWords[i].word<<endl;
    }
}

int main(int argc, char *argv[])
{
    string ignoreWords[50];
    int osize = 100;
    bool val;
    bool enter=0;
    int arrayCnt=0;
    int wordCnt=0;
    int N = stof(argv[1]);
    ifstream file;
    string word;
    wordRecord* wordsT = new wordRecord[osize];

    if (argc != 4)
    {
        cout << "Usage: Assignment2Solution <number of words> <inputfilename.txt> <ignoreWordsfilename.txt>" <<endl;
    }
    
    getIgnoreWords(argv[3], ignoreWords);

    int i = 0;
    int ws = 0;
    file.open(argv[2]);
    while(file>>word)
    {
        if(wordCnt==osize)
        {
            int nsize = 2*osize;

            wordRecord* holder = new wordRecord[nsize];
            for (int j=0;j<osize;j++)
            {
                holder[j] = wordsT[j];
            }
            delete [] wordsT;
            osize = nsize;
            wordsT = holder;
            arrayCnt++;
        }
        val = isIgnoreWord(word,ignoreWords);
        if (val==false)
        {
            enter=0;
            for(int idx=0;idx<wordCnt;idx++)
            {
                if(word==wordsT[idx].word)
                {
                    wordsT[idx].count++;
                    enter = 1;
                }
                
            }
            if (enter == 0)
            {
                wordRecord tempWrd = {word,1};
                wordsT[wordCnt]=tempWrd;
                wordCnt++;
            }
            i++;
        }
        //ws++;
    }

    //Outputting
    sortArray(wordsT,wordCnt);
    cout<<"Array doubled: "<<arrayCnt<<endl;
    cout<<"Distinct non-common words: "<<wordCnt<<endl;
    cout<<"Total non-common words: "<<i<<endl;
    cout<<"Probability of next 10 words from rank "<<argv[1]<<endl;
    cout<<"---------------------------------------"<<endl;
    printTenFromN(wordsT,N,i);
}