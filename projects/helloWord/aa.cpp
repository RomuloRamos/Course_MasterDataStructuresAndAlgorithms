/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <iostream>
#include <cstring>
using namespace std;

bool cfncRefactoLetterA(string *strWord){
    //dcbaacb
    bool bLetterFound = false;
    string strToCheck = *strWord;
//    string::reverse_iterator strHelpToHandle = strToCheck.rbegin();
    string strRev = string(strToCheck.rbegin(), strToCheck.rend());
    //bcaacd
    size_t found = strRev.find("aa");
    //found = 2
    if(found!=string::npos){
        strRev.replace(found,2,"å");
        //bcåcd
        strToCheck = string(strRev.rbegin(), strRev.rend());
        //dcåcb
        strWord->assign(strToCheck);
        return true;
    }
    return false;
}

string vfnctMyCopyString(const char* strToCopy){
     string strRet = strToCopy;
     return strRet;
}

bool vfnctCheckWords(string* strWord1, string* strWord2){
    
    const char *cWord1 = strWord1->data(), *cWord2 = strWord2->data();
    bool bResult = true;
    unsigned int uiLetter1 = 0, uiLetter2 = 0, uiCounter = 0;
    while((*(cWord1+uiCounter) != '\0')/* && (*cWord2 != '\0')*/){
        uiLetter1 = (unsigned int) *(cWord1+uiCounter);
        uiLetter2 = (unsigned int) *(cWord2+uiCounter);
        if(uiLetter1 < uiLetter2){
            return true;
        }
        else if( uiLetter1 > uiLetter2 ){
            if(uiLetter2==97 /* "a" */){
                //Caso a letra atual e a seguinte forem "a", analiza se a proxima letras da segunda palavra é maior 


                unsigned int uiCheck1 = 0;
                unsigned int uiCheck2 = (unsigned int)*(cWord2+(uiCounter+1));
                if(uiCheck2==97){
                    unsigned int uiCntCheckLetters1 = uiCounter;
                    unsigned int uiCntCheckLetters2 = 0;
                    if(cWord1 == "å"){
                        uiCntCheckLetters1 = uiCounter+1;
                    }
                    unsigned int uiCntCheckAfter = uiCounter+1;
                    bool bCheckNextLetters = true;
                    while((*(cWord2+uiCntCheckAfter) != '\0')){
                        uiCheck1 = (unsigned int) *(cWord1+uiCounter+uiCntCheckAfter+1);
                        uiCheck2 = (unsigned int) *(cWord2+uiCounter+uiCntCheckAfter+1);
                        if(uiCheck1 < uiCheck2){
                            strWord2->replace(uiCounter,2,"å");
                            return vfnctCheckWords(strWord1, strWord2);
                        }
                        if(uiCheck1 > uiCheck2){
                            bCheckNextLetters = false;
                            break;
                        }
                        uiCntCheckAfter++;
                    }
                    if(bCheckNextLetters){
                        //Saiu do laço com todas as letras iguais após o "aa" - Condição de sucesso
                        strWord2->replace(uiCounter,2,"å");
                        return vfnctCheckWords(strWord1, strWord2);
                    }
                }
            }
            if(uiCounter != 0){
            //laço for até encontrar letra a duas vezes ou contador igual a zero
                for(int iCheckBefore = uiCounter; iCheckBefore>0; iCheckBefore--){
                    uiLetter2 = (unsigned int) *(cWord2+iCheckBefore);
                    if(uiLetter2==97 /* "a" */){
                        if((unsigned int)*(cWord2+(iCheckBefore-1))==97){
                            strWord2->replace((iCheckBefore-1),2,"å");
                            return vfnctCheckWords(strWord1, strWord2);
                        }
                    }
                }
                return false;
                    
            }
        }
        uiCounter++;
        if((*(cWord2+uiCounter) == '\0') && (*(cWord1+uiCounter) != '\0')) return false;
    }

    return bResult;
}

void vfnctCheckOrder(string *cWordBuffer, unsigned int uiBufferSize){
//    Para cada letra, eu vejo se o seu valor na tabela ascii é menor ou igual ao da letra na mesma posição da palavra seguinte.
    bool bResult = true;
    for(unsigned int uiCounter = 0; uiCounter < (uiBufferSize - 1); uiCounter++){
        bResult &= vfnctCheckWords(&cWordBuffer[uiCounter],&cWordBuffer[uiCounter+1]);
    }
    if(bResult){
        cout << "yes"<<endl;
    }
    else{
        cout << "no"<<endl;
    }
    
}

int main() {
    // Write C++ code here
    unsigned int uiCounter = 0, uiArraySize = 0;

    cin >> uiCounter;
    uiArraySize = uiCounter;
    string strArrayWord[uiArraySize];
    for(uiCounter; uiCounter > 0; uiCounter--){
        cin >> strArrayWord[(uiArraySize - uiCounter)];
    }
    vfnctCheckOrder(strArrayWord, uiArraySize);
//    cout << "Program Finished!";

    return 0;
}
