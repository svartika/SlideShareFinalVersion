
#ifndef _LECTURE_INFO_H_
#define _LECTURE_INFO_H_

static struct LectureInfo{
	Tizen::Base::String latitude, longitude, timing;
	long lastShownAt = 0;
	LectureInfo* next = null;
};
#endif /* _LECTURE_INFO_H_ */
