#include <iostream>
#include <fstream>
using namespace std;
 
class Music {
    public:
        char notation[7] = {'C','D','E','F','G','A','B'};
        string scale[7] = {"Do","Re","Mi","Fa","Sol","La","Si"};
        string sheet="";
        fstream file;
        Music(string filenamepath){
            //TODO
            // use ios::in to read the sheet music to variable sheet
            file.open(filenamepath, ios::in);

            if(!file)    cout<<"Can't open file!\n";
        }
        virtual string  getname(){
            //return this->getname();
            return "unknow";
            //return this->getname();
        }
        virtual void sheet_music(){
            //return this->sheet_music();
            cout << "Let's Music!" << endl;
               //return this->sheet_music();
        }
};
class Star : public Music{
    public:
        Star(string filenamepath):Music(filenamepath){}
        string getname() override {
            return "LITTLE STAR";
        }
        void sheet_music() override
        {
            string str;
            //cout<<"test"<<endl;
            if(file>>str)
            {
                for(int i=0;i<str.length();i++)
                {
                    cout<<notation[str[i]-'0'-1];
                }
                cout<<endl;
            }
        }
        //TODO
};
 
class Bee : public Music{
    public:
        Bee(string filenamepath):Music(filenamepath){}
        string getname() override {
            return "BEE";
        }
        //TODO
        void sheet_music() override
        {
            string str;
            //cout<<"test"<<endl;
            if(file>>str)
            {
                for(int i=0;i<str.length();i++)
                {
                    cout<<scale[str[i]-'0'-1];
                }
                cout<<endl;
            }
 
        }
};
 
enum MUSIC_LIST{
    STAR,
    BEE
};
 
class PlayMusic{
public:
    //TODO
    Music* play(MUSIC_LIST chosenSong)    {
        if(chosenSong == 0)
        {
            Star* little_star = new Star("../app/star.txt");
            return little_star;
        }
        else if(chosenSong == 1)
        {
            Bee* bee_song = new Bee("../app/bee.txt");
            return bee_song;     
        } else {
            return nullptr;
        }
    }
};
