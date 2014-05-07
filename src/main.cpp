#include <iostream>
#include <cstdlib>
int main(){
  std::cout<<"Content-type: text/html\r\n\r\n";

  std::cout<<"QUERY STRING IS:  ";
  std::cout<<std::getenv("QUERY_STRING"); // get enviroment variable
}
