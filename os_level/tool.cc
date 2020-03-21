#include <iostream>
#include <string>

std::string translate(std::string line){
  std::string result = line;
  int sh = 23;
  
  for(int i=0; i < line.size(); i++){
    if(line[i]>= 65 && line[i] <= 90){ // hoofdletters
      result[i] = char((line[i]+sh-65)%26 +65);
    }else if(line[i]>97 && line[i] <= 122){ // kleine letters
      result[i] = char((line[i]+sh-97)%26 +97);
    }
  }
  return result;
}

int main(int argc, char *argv[])
{ std::string line;

  while(std::getline(std::cin, line))
  { std::cout << translate(line) << std::endl; } 

  return 0; }
