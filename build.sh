#!/usr/bin/env bash
flex scanner.l
gcc lex.yy.c -lfl -o scanner
