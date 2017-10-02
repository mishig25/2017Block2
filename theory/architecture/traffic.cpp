#import <iostream>
#import <string>
#import <fstream>

using namespace std;

struct LinkedRecord{
  int year;
  int stops;
  struct LinkedRecord* next;
};

int parse_line(string line){
  string year_next = line.substr(6,4);
  // REFERENCED FROM: https://stackoverflow.com/a/16575025/6558628
  // lines 17-18
  char * isNumber;
  int year_n = strtol(year_next.c_str(), &isNumber, 10) ;
  int year = -1;
  if(*isNumber == 0) year = year_n;
  return year;
}

LinkedRecord * list_find(LinkedRecord *head, int year){
  if(!head->year){
    head->year = year;
    LinkedRecord *new_node = new LinkedRecord();
    head->next = new_node;
    return head;
  }else if(head->year == year){
    return head;
  }
  return list_find(head->next,year);
}

void print_list(LinkedRecord *head){
  if(!head || !head->stops) return;
  cout << head->year << " had " << head->stops << " stops\n";
  print_list(head->next);
}

int main(int argc, char** argv){
  // check length of command line arg
  if(argc < 2){
    printf("Usage: %s <traffic data>\nExiting...\n", argv[0]);
    return 0;
  }
  // get file name
  char* fname = argv[1];

  // initialize LinkedRecord
  LinkedRecord *head = new LinkedRecord();

  // REFERENCED FROM: https://gsamaras.wordpress.com/code/read-file-line-by-line-in-c-and-c/
  // lines 56-60
  ifstream infile(fname);
  string line;
  // throw away header line and process data
  getline(infile,line);
  while(getline(infile,line)){
    // get the year
    int year = parse_line(line);
    LinkedRecord *current_node = list_find(head,year);
    current_node->stops++;
  }

  print_list(head);
  return 0;
}
