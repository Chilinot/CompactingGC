#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include "string_util.h"
#ifdef __sparc__
int PLATFORM = 1;
#else
int PLATFORM = 0;
#endif
/**
* Concatinates a '*' or a 'r' on to the headerstring depending on platform,
* number of items and size of item.
*@param value Number of items.
*@param headerString String on which to concatinate.
*@param size Size of the item.
*@param rOrStar '*' or 'r' wheter if the item is a void* or not.
*@return Returns the concatinated string.
*/
char* concateFormatString(int value, char* headerString, int size, char* rOrStar, int is64or32){
int wholeSize = (value * size);
int temp = wholeSize;{
if(is64or32 == 0){ // 32bit platform
if(wholeSize <= 4 && wholeSize > 0){ // If type can fit in a word
strcat(headerString, rOrStar);
return headerString;
}
wholeSize = wholeSize / 4; // r is 4 bytes
for(int i = 0; i < wholeSize; i++){
strcat(headerString, rOrStar);
}
if (temp % 4 != 0){ // If any remainder, add to string
strcat(headerString, rOrStar);
}
}
if(is64or32 == 1){ // 64bit platform
if(wholeSize <= 8 && wholeSize > 0){
strcat(headerString, rOrStar);
if(strcmp(rOrStar, "r") == 0){
strcat(headerString, rOrStar);
}
return headerString;
}
if(strcmp(rOrStar,"*") == 0){
wholeSize /= 8;
}
else{
wholeSize /= 4;
}
for(int i = 0; i < wholeSize; i++){
strcat(headerString, rOrStar);
}
if (temp % 8 != 0){
strcat(headerString, rOrStar);
strcat(headerString, rOrStar);
}
}
}
return headerString;
}
int lengthOfFormatStringToAllocate(char* layout){
int headerLength = 0;
for(int i = 0; i < strlen(layout); i++){
if isdigit(layout[i]){
headerLength += returnDigit(layout, i) *2;
i = newPos(layout, i);
}
else{
headerLength += 2;
}
}
return headerLength;
}
/**
* Searches for integers in a row in a substring until end of string or a non-integer item is found
* and converts the string of integers to an integer.
*@param layout The formatstring.
*@param digitPos Position of the first integer in the substring of the formatstring.
*@return Returns the converted value of the substring.
*/
int returnDigit(char* layout, int digitPos){
assert(digitPos >= 0 && digitPos <= strlen(layout));
int nr = 0;
for(int i = digitPos; i < strlen(layout); i++){
if(isdigit(layout[i])){
nr++;
}
}
char stringValue[strlen(layout)];
memcpy(stringValue, layout + digitPos, nr);
return atoi(stringValue);
}
/**
* True if character l or d exists in the formatstring
*@param layout The formatstring
*@return Returns 1 if true, else 0
*/
int checkForPointerDoubleLong(char* layout){
for(int i = 0; i < strlen(layout); i++){
if(sizeof(void*) == 8){
if(layout[i] == 'l' || layout[i] == 'd' || layout[i] == '*'){
return 1;
}
}
else{
if( layout[i] == 'd'){
return 1;
}
}
}
return 0;
}
/**
* Searches from current position after non-integer or until end of string and returns that
* position
*@param layout The formatstring
*@param currentPos Current position in the formatstring.
*@return Returns the position of the next non-integer of the string.
*/
int newPos(char* layout, int currentPos){
int i;
int newPos;
for(i = currentPos; i < strlen(layout); i++){
if(isdigit(layout[i])){
}
else{
newPos = i;
return newPos;
}
}
newPos = i;
return newPos;
}
/**
*Given a formatstring, converts the string into a headerstring that describes the memorylayout.
*If no string is given, terminate the program.
*@param The formatstring to be converted.
*@return Returns a headerstring.
*/
char* formatStringToHeaderString(char* layout){
char* headerString;
int longOrDoubleExists;
int is64or32;
if(layout == NULL){
puts("No formatstring to allocate");
exit(0);
}
if(sizeof(void*) == 8){
if(checkForPointerDoubleLong(layout) == 1){ // Check on which platform the program is run
is64or32 = 1;
}
else{
is64or32 = 0;
}
}
if(sizeof(void*) == 4){
is64or32 = 0;
}
if(PLATFORM == 1){
longOrDoubleExists = checkForPointerDoubleLong(layout);
if(longOrDoubleExists == 1){
is64or32 = 1;
}
else{
is64or32 = 0;
}
}
headerString = calloc(lengthOfFormatStringToAllocate(layout), 1);
char* r = "r";
char* star = "*";
int length = strlen(layout);
int value;
int prevSize = 0;
for(int newPosition = 0; newPosition < length; newPosition++){
if(isdigit(layout[newPosition])){
value = returnDigit(layout, newPosition); // value is the integer-value before a character
newPosition = newPos(layout, newPosition); // change position to next character if possible
if(length == newPosition){
concateFormatString(value, headerString, 1, r, is64or32);
return headerString;
}
}
else{
value = 1; // default value
}
if(layout[newPosition] == '*'){
int size = sizeof(void*);
concateFormatString(value, headerString, size, star, is64or32 );
printf("%d\n",prevSize);
prevSize = 0;
}
if(layout[newPosition] != 'c' && layout[newPosition] != '*' && layout[newPosition] != 'l' && layout[newPosition] != 'd' && layout[newPosition] != 'i' && layout[newPosition] != 'f'){
if(layout[newPosition] == '\0'){
return headerString;
}
else{
puts("Not a valid formatstring");
return NULL;
}
}
if(layout[newPosition] == 'c') { // Check if several chars are in a row
int size = sizeof(char);
if(is64or32 == 0 ){
if (layout[newPosition + 1] == 'c'){
newPosition++;
}
if (layout[newPosition + 1] == 'c'){
newPosition++;
}
if (layout[newPosition + 1] == 'c'){
newPosition++;
}
concateFormatString(value, headerString, size, r, is64or32);
}
if(is64or32 == 1 ){
if (layout[newPosition + 1] == 'c'){
newPosition++;
value++;
prevSize = size * value;
}
if (layout[newPosition + 1] == 'c'){
newPosition++;
value++;
prevSize = size * value;
}
if (layout[newPosition + 1] == 'c'){
newPosition++;
value++;
prevSize = size * value;
}
if (layout[newPosition + 1] == 'c'){
newPosition++;
value++;
prevSize = size * value;
}
if (layout[newPosition + 1] == 'c'){
newPosition++;
value++;
prevSize = size * value;
}
if (layout[newPosition + 1] == 'c'){
newPosition++;
value++;
prevSize = size * value;
}
if (layout[newPosition + 1] == 'c'){
newPosition++;
value++;
prevSize = size * value;
}
if (layout[newPosition + 1] == 'c'){
newPosition++;
value++;
prevSize = size * value;
concateFormatString(value, headerString, size, r, is64or32);
}
if(layout[newPosition + 1] == '\0' || layout[newPosition + 1] == '*' || layout[newPosition + 1] == 'd' || layout[newPosition + 1] == 'l' || value > 4){
concateFormatString(value, headerString, size, r, is64or32);
if(value > 8){
prevSize %= 8;
}
}
}
}
if(layout[newPosition] == 'l') {
int size = sizeof(long);
concateFormatString(value, headerString, size, r, is64or32 );
prevSize = 0;
}
if(layout[newPosition] == 'i'){
int size = sizeof(int);
if(is64or32 == 1){
if(prevSize + (size*value) < 8){
if(layout[newPosition + 1] == '\0' || layout[newPosition + 1] == '*' || layout[newPosition + 1] == 'd' || layout[newPosition + 1] == 'l'){
concateFormatString(value, headerString, size, r, is64or32 );
}
else{
prevSize = prevSize + size * value;
}
}
else{
concateFormatString(value, headerString, size, r, is64or32 );
prevSize = 0;
}
}
else{
concateFormatString(value, headerString, size, r, is64or32 );
}
}
if(layout[newPosition] == 'd') {
int size = sizeof(double);
concateFormatString(value, headerString, size, r, is64or32 );
prevSize = 0;
}
if(layout[newPosition] == 'f') {
int size = sizeof(float);
if(is64or32 == 1){
if(prevSize + (size*value) < 8){
if(layout[newPosition + 1] == '\0'){
concateFormatString(value, headerString, size, r, is64or32 );
return headerString;
}
}
else{
concateFormatString(value, headerString, size, r, is64or32 );
prevSize = 0;
}
}
else{
concateFormatString(value, headerString, size, r, is64or32 );
}
prevSize = size * value;
}
}
return headerString;
}
size_t headerStringToSize(char* layout){
switch(*layout){
case 'r':
return sizeof(int) + headerStringToSize(layout + 1);
case '*':
return sizeof(void*) + headerStringToSize(layout + 1);
case '\0':
return 0;
}
return 0; // should not happen
}
/*
int main(int argc, char* argv[]){
char * test = formatStringToHeaderString(argv[1]);
printf("input: %s\n",test);
return 0;
}
*/
