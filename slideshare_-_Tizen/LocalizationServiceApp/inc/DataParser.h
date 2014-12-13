/*
 * DataParser.h
 *
 *  Created on: Nov 30, 2014
 *      Author: misha
 */

#include <FApp.h>
#include <FBase.h>
#include <FBaseString.h>
#include "LectureInfo.h"

#ifndef DATAPARSER_H_
#define DATAPARSER_H_

class DataParser {
public:
	DataParser();
	virtual ~DataParser();
	LectureInfo* ParseString(Tizen::Base::String input);
};


#endif /* DATAPARSER_H_ */
