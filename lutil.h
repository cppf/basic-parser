#pragma once
#include <string.h>
#include <ctype.h>


// pop: remove n chars from end of string
char *pop(char *s, int n) {
  s[strlen(s) - n] = '\0';
  return s;
}

// lower: lowercase characters in place
char *lower(char *s) {
  for(char *d=s; *d; d++) { *d = tolower(*d); }
  return s;
}


char *unescape(char *s) {
  char *_s = s;
  for(char *d=s; *s; s++) {
    if (*s == '\\') {switch(s[1]) {
      case 'a': *d = '\a'; s++;
      case 'b': *d = '\b'; s++;
      case 'e': *d = '\e'; s++;
      case 'f': *d = '\f'; s++;
      case 'n': *d = '\n'; s++;
      case 'r': *d = '\r'; s++;
      case 't': *d = '\t'; s++;
      case 'v': *d = '\v'; s++;
      case '\\': *d = '\\'; s++;
      case '\'': *d = '\''; s++;
      case '\"': *d = '\"'; s++;
      case '?': *d = '\?'; s++;
      default: *d = *s; d++;
    }}
  }
  return _s;
}
