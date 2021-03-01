#include "./music2.cc"
int main(){
    PlayMusic p;
    Music* mptr = p.play(STAR);
    cout << mptr -> getname() << endl; //LITTLE STAR
    mptr->sheet_music();//CCGGAAGFFEEDDCGGFFEEDGGFFEEDCCGGAAGFFEEDDC
 
    Music* Mptr = p.play(BEE);
    cout << Mptr -> getname() << endl;//BEE
    Mptr->sheet_music();//SolMiMiFaReReDoReMiFaSolSolSolSolMiMiFaReReDoMiSolSolMiReReReReReMiFaMiMiMiMiMiFaSolSolMiMiFaReReDoMiSolSolDo
 
}
