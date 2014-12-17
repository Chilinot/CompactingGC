
void stringExpand(char *str){
  char* cursor = str;
  size_t count = 0;
  while(cursor != \0){
    if(isnum(cursor)){
      long number = strtol(cursor, &cursor, 10);
      
    }
    else{
      cursor++;
    }
  }

}

size_t sizeOfFormatType(char c){
  switch(c){

  case '*': return 3; 
    break;
  }
}
