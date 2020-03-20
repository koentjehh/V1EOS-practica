#include <iostream>
#include <string>

int main(int argc, char *argv[]){
  string resultaat = "";
  
  for(int i=0; argv.size(); i++){
    if(argv[i]){ // hoofdletters
      resultaat += char(int(argv[i]+argc-65)%26 +65);
    }else{ // kleine letters
      resultaat += char(int(argv[i]+argc-97)%26 +65);
    }
  }
  return resultaat;
}
