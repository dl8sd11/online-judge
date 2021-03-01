#include <iostream>
#include <fstream>
using namespace std;
 
class Music {
    public:
        int a=0;
        int b=0;
        char notation[7] = {'C','D','E','F','G','A','B'};
        string scale[7] = {"Do","Re","Mi","Fa","Sol","La","Si"};
        string sheet="12";
        fstream file;
        Music(string filename){
            file.open(filename,ios::in);
 
            if(!file){
                cout<<"Can't open file!\n";
                a=1;
                b=1;
            }
            file>>sheet;
            //cout<<sheet<<endl;
            //else if(while(!file.eof())){
            //    file>>txt;
            //    sheet+=txt;
            //}
            file.close();
            //TODO
            // use ios::in to read the sheet music to variable sheet
            //if file not open successfully print "Can't open file!\n"
        }
        virtual string  getname(){
            return "unknow";
        }
        virtual void sheet_music(){
            cout << "Let's Music!" << endl;
        }
};
class Star : public Music{
    public:
        Star(string filename):Music(filename){}
        virtual string getname(){
            //if(b!=1)
            return "LITTLE STAR";
            //else{
            //    return "";
            //}
        }//TODO
        virtual void sheet_music(){
            if(a!=1){
                for(int i=0;i<sheet.length();i++){
                    cout << notation[sheet[i]-'0'-1] ;
                }
                //cout<<"CCGGAAGFFEEDDCGGFFEEDGGFFEEDCCGGAAGFFEEDDC";
                cout<<endl;
            }
 
        }
};
 
class Bee : public Music{
    public:
        Bee(string filename):Music(filename){}
        virtual string getname(){
            //if(b!=1)
            return "BEE";
            //else{
            //    return "";
            //}
        }
        virtual void sheet_music(){
            if(a!=1){
                for(int i=0;i<sheet.length();i++){
                    cout << scale[sheet[i]-'0'-1] ;
            }
            //cout<<"SolMiMiFaReReDoReMiFaSolSolSolSolMiMiFaReReDoMiSolSolMiReReReReReMiFaMiMiMiMiMiFaSolSolMiMiFaReReDoMiSolSolDo";
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
 
    Music* play(MUSIC_LIST name){
        if(name==STAR){
            Music* tem = new Star("../app/star.txt");
            return tem;
        }else if(name==BEE){
            Music* tem = new Bee("../app/bee.txt");
            return tem;
        }
 
    }
 
};
