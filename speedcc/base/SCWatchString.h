//
//  SCWatchString.h
//  libspeedcc
//
//  Created by Kevin on 18/12/2017.
//  Copyright © 2017 speedcc. All rights reserved.
//

#ifndef __SPEEDCC__SCWATCHSTRING_H__
#define __SPEEDCC__SCWATCHSTRING_H__

#include "SCObject.h"
#include "SCString.h"

namespace SpeedCC
{
    class SCWatchString :
    public SCString,
    public SCObject
    {
    public:
        SC_DEFINE_CLASS_PTR(SCWatchString)
        
        typedef SCString  type;
        
        SCWatchString(const SCWatchString& watch);
        
        SC_DEFINE_CREATE_FUN0(SCWatchString)
        SC_DEFINE_CREATE_FUN1(SCWatchString,const SCString&)
        SC_DEFINE_CREATE_FUN1(SCWatchString,const char*)
        
        void setEmpty();
        void format(const char* pszFormat, ...);
        
        int replace(char chOld, char chNew);
        int replace(const char* pszOld, const char* pszNew);
        int replace(const std::string& strOld,const std::string& strNew);
        int remove(int nBegin,int nLength=1);
        int remove(char chRemove);
        int remove(const char* pszStr);
        int remove(const std::string& str);
        
        int insert(int nIndex, const char* pstr);
        int insert(int nIndex, char ch);
        int insert(int nIndex, const std::string& str);
        
        int trimRight(char c);
        int trimRight(const char* szStr);
        int trimRight(const std::string& str);
        
        int trimLeft(char c);
        int trimLeft(const char* szStr);
        int trimLeft(const std::string& str);
        
        void makeUpper();
        void makeLower();
        
        void setAt(const int nIndex, const char ch);
        char& operator[](int nIndex) = delete;
        
        const SCString& operator+=(const SCString& string);
        const SCString& operator+=(char ch);
        const SCString& operator+=(const char* psz);
        const SCString& operator+=(const std::string& str);
        const SCString& operator+=(const int nNumber);
        const SCString& operator+=(const float fNumber);
        const SCString& operator+=(const unsigned uNumber);
        const SCString& operator+=(const SCEncodingChar& encodingChar);
        
        // assign
        const SCString& operator=(const SCString& stringSrc);
        const SCString& operator=(char ch);
        const SCString& operator=(const char* psz);
        const SCString& operator=(const unsigned short* pszStr); // utf16 encoding
        const SCString& operator=(const std::string& str);
        const SCString& operator=(const SCEncodingChar& encodingChar);
        const SCString& operator=(const int nNumber);
        //    const SCString& operator=(const float fNumber);
        const SCString& operator=(const unsigned uNumber);
        
        int addUpdateFun(const std::function<void(Ptr watchPtr,
                                                     const SCString& strNew,
                                                     const SCString& strOld)>& fun);
        
        void removeUpdateFun(const int nID);
        inline SCString getValue() const {return *this;}
        
    protected:
        SCWatchString();
        SCWatchString(const SCString& str);
        
    private:
        void checkChange();
        
    private:
        int                 _nIDCounter;
        std::map<int,std::function<void(Ptr watchPtr,
                                        const SCString& strNew,
                                        const SCString& strOld)> >    _postUpdateFunMap;
        SCString        _strLast;
    };
}

#endif // __SPEEDCC__SCWATCHSTRING_H__
