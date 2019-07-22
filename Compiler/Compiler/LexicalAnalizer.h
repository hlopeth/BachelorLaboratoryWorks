#pragma once
#include <vector>
#include <string>
#include <boost/algorithm/string.hpp>
#include <regex>
#include "Errors.h"
#include "IdentTypeTables.h"

using namespace std;

enum lexeme_type {
	DO=54/*do*/, IF=56/*IF*/, IN=22/*in*/, OF=8/*of*/, OR=23/*or*/, TO=55/*to*/,
	AND=24/*and*/,	DIV=25/*div*/, END=13/*end*/, FOR=26/*for*/, MOD=27/*mod*/,
	NIL=89/*nil*/, NOT=28/*not*/, SET=29/*set*/, VAR=30/*var*/,
	CASE=31/*case*/, ELSE=32/*else*/, FILE_S=57/*file*/, GOTO=33/*goto*/,
	ONLY=90/*only*/, THEN=52/*then*/, TYPE=34/*type*/, UNIT=35/*unit*/,
	USES=36/*uses*/, WITH=37/*with*/,
	ARRAY=34/*array*/, BEGIN=17/*begin*/, CONST=39/*const*/, LABEL=40/*label*/, 
	UNTIL=53/*until*/,	WHILE=41/*while*/, EXPORT=91/*export*/,
	IMPORT=92/*import*/, DOWNTO=55/*downto*/, MODULE=93/*module*/,
	PACKED=42/*packed*/, RECORD=43/*record*/, REPEAT=44/*repeat*/, 
	VECTOR=45/*vector*/, STRING=46/*string*/,
	FORWARD=47/*forvard*/, PROCESS=48/*process*/, PROGRAM=3/*program*/,
	SEGMENT=49/*segment*/, FUNCTION=77/*function*/, SEPARATE=78/*separate*/,
	INTERFACE=79/*interface*/, QUALIFIED=80/*qualified*/,
	IMPLEMENTATION=81/*implementation*/, DOT=61/*.*/, ASSIGN=51/*:=*/, SEMI=14/*;*/, COLON=5/*:*/,
	INT_NUMBER/*12*/, REAL_NUMBER/*12.5*/, CHAR/*'a'*/, IDENT=2/*var or const name*/,
	PLUS=70/*+*/, MINUS=71/*-*/, MULT=21/***/, DIVISION=60/*/*/, COMMA=20/*,*/, EQUAL=16/*=*/, 
	LPAR=9/*(*/, RPAR=4/*)*/, LBRACKET=11/*[*/, RBRACKET=12/*]*/, LFPAR=63/*{*/, RFPAR=64/*}*/,
	LESS=65/*<*/, GREATER=66/*>*/, LESS_EQUAL=67/*<=*/, GREATER_EQUAL=68/*>=*/, NOEQUAL=69/*<>*/,
	TRUE=1/*true*/, FALSE=0/*false*/, NULL_LEXEME
};

class Lexeme
{
public:
	lexeme_type type;
	Lexeme(lexeme_type _type) : type(_type) {};
};

class Ident : public Lexeme
{
public:
	string name;
	Ident(string _name) : Lexeme(IDENT), name(_name) {}
};

class Int_Number : public Lexeme
{
public:
	int value;
	Int_Number(int _value): Lexeme(INT_NUMBER), value(_value) {}
};

class Real_Number : public Lexeme
{
public:
	double value;
	Real_Number(double _value): Lexeme(REAL_NUMBER), value(_value) {}
};

class Char : public Lexeme
{
public:
	char value;
	Char(char _value): Lexeme(CHAR), value(_value) {}
};

vector<sError> get_lexems(string line, vector<Lexeme*>& lexemes, int line_num);
bool is_name(string s);
bool is_int_number(string s);
bool is_real_number(string s);
int add_lexeme(string word, vector<Lexeme*>& lexemes);
