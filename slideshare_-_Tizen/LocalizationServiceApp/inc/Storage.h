/*
 * Storage.h
 *
 *  Created on: Nov 29, 2014
 *      Author: misha
 */

#include <FApp.h>
#include <FBase.h>
#include <FBaseString.h>

#ifndef STORAGE_H_
#define STORAGE_H_

class Storage
{
   public:
       static Storage* getInstance(Tizen::App::AppRegistry* appRegistry );
       bool SaveKeyValuePair(Tizen::Base::String key, Tizen::Base::String value);
       ~Storage( );
       Storage(Tizen::App::AppRegistry* appRegistry );
       Storage();
       static Storage* instance;



   private:
      /* Storage(Tizen::App::AppRegistry* appRegistry );
       Storage();*/
       //static Storage* instance;
       Tizen::App::AppRegistry* m_pAppRegistry;
};



#endif /* STORAGE_H_ */
