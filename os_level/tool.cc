#include <iostream>
#include <string>

std::string translate(std::string line){
  std::string result = line;
  
  for(int i=0; i < line.size(); i++){
    if(line[i]>= 65 && line[i] <= 90){ // hoofdletters
      result[i] = char((line[i] + 3) % (26 + line[i]));
    }else if(line[i]>97 && line[i] <= 122){ // kleine letters
      result[i] = char((line[i] + 3) % (26 + line[i]));
    }
  }
  return result;
}

int main(int argc, char *argv[])
{ std::string line;

  if(argc != 2)
  { std::cerr << "Deze functie heeft exact 1 argument nodig" << std::endl;
    return -1; }

  while(std::getline(std::cin, line))
  { std::cout << translate(line) << std::endl; } 

  return 0; }
