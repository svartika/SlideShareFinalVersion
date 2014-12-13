/*
 * DataParser.cpp
 *
 *  Created on: Nov 30, 2014
 *      Author: misha
 */

#include "DataParser.h"
//#include "LectureInfo.h"
using namespace Tizen::Base;

DataParser::DataParser() {
	// TODO Auto-generated constructor stub

}

DataParser::~DataParser() {
	// TODO Auto-generated destructor stub
}

LectureInfo* DataParser::ParseString(String input)	{
	String delimiter(L"`");
	Tizen::Base::Utility::StringTokenizer tokenizer(input, delimiter);
	int count = tokenizer.GetTokenCount();
	String token;
	int index = 0;
	LectureInfo* lectureInfo = null;
	LectureInfo* temp = null;
	AppLog("ParseString is called. Number of tokens: %d for input %S", count, input.GetPointer());
	while (tokenizer.HasMoreTokens())	{
		AppLog("token is ",  token.GetPointer());
		if(index == 0){
			if(lectureInfo==null){
				AppLog("ParseString is called. in while loop and lectureInfo was null");
				lectureInfo = new LectureInfo();
				temp = lectureInfo;
			} else{
				AppLog("ParseString is called. in while loop and lectureInfo was NOT null");
				LectureInfo* lectemp = new LectureInfo();
				temp->next = lectemp;
				temp = temp->next;
			}
		}

		tokenizer.GetNextToken(token);
		switch(index){
			case 0:
				temp->timing=token;
				AppLog("ParseString is called. index is %d: value is %S", index, token.GetPointer());
				break;
			case 1:
				temp->longitude=token;
				AppLog("ParseString is called. index is %d: value is %S", index, token.GetPointer());
				break;
			case 2:
				temp->latitude=token;
				AppLog("ParseString is called. index is %d: value is %S", index, token.GetPointer());
				break;
			}
		index = (1+index)%3;
	}
	return lectureInfo;
}


