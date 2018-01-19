//
//  SCWatchString.h
//  libspeedcc
//
//  Created by Kevin on 18/12/2017.
//  Copyright © 2017 speedcc. All rights reserved.
//

#include "SCWatchString.h"

namespace SpeedCC
{
    SCWatchString::SCWatchString(const SCWatchString& watch):
    SCString(watch.getValue()),
    _nIDCounter(0)
    {
    }
    
    SCWatchString::SCWatchString():
    _nIDCounter(0)
    {
    }
    
    SCWatchString::SCWatchString(const SCString& str):
    SCString(str),
    _nIDCounter(0)
    {
        
    }
    
    int SCWatchString::addUpdateFunc(const std::function<void(Ptr ptrWatch,
                                                                const SCString& strNew,
                                                                const SCString& strOld)>& fun)
    {
        ++_nIDCounter;
        _postUpdateFunMap[_nIDCounter] = fun;
        return _nIDCounter;
    }
    
    void SCWatchString::removeUpdateFunc(const int nID)
    {
        if(_postUpdateFunMap.find(nID)!=_postUpdateFunMap.end())
        {
            _postUpdateFunMap.erase(nID);
        }
    }
    
    void SCWatchString::checkChange()
    {
        if(_strLast!=*this)
        {
            for(const auto& it : _postUpdateFunMap)
            {
                it.second(this->makeObjPtr(this),*this,_strLast);
            }
            
            _strLast = (*this);
        }
    }
    
    ///----------------------
    void SCWatchString::setEmpty()
    {
        this->SCString::setEmpty();
    }
    
    void SCWatchString::format(const char* pszFormat, ...)
    {
        this->setEmpty();
        
        va_list argList;
        va_start(argList, pszFormat);
        this->formatV(pszFormat, argList);
        va_end(argList);
        
        this->checkChange();
    }
    
    int SCWatchString::replace(char chOld, char chNew)
    {
        auto ret = this->SCString::replace(chOld,chNew);
        this->checkChange();
        return ret;
    }
    
    int SCWatchString::replace(const char* pszOld, const char* pszNew)
    {
        auto ret = this->SCString::replace(pszOld,pszNew);
        this->checkChange();
        return ret;
    }
    
    int SCWatchString::replace(const std::string& strOld,const std::string& strNew)
    {
        auto ret = this->SCString::replace(strOld,strNew);
        this->checkChange();
        return ret;
    }
    
    int SCWatchString::remove(int nBegin,int nLength)
    {
        auto ret = this->SCString::remove(nBegin,nLength);
        this->checkChange();
        return ret;
    }
    
    int SCWatchString::remove(char chRemove)
    {
        auto ret = this->SCString::remove(chRemove);
        this->checkChange();
        return ret;
    }
    
    int SCWatchString::remove(const char* pszStr)
    {
        auto ret = this->SCString::remove(pszStr);
        this->checkChange();
        return ret;
    }
    
    int SCWatchString::remove(const std::string& str)
    {
        auto ret = this->SCString::remove(str);
        this->checkChange();
        return ret;
    }
    
    int SCWatchString::insert(int nIndex, const char* pstr)
    {
        auto ret = this->SCString::insert(nIndex,pstr);
        this->checkChange();
        return ret;
    }
    
    int SCWatchString::insert(int nIndex, char ch)
    {
        auto ret = this->SCString::insert(nIndex,ch);
        this->checkChange();
        return ret;
    }
    
    int SCWatchString::insert(int nIndex, const std::string& str)
    {
        auto ret = this->SCString::insert(nIndex,str);
        this->checkChange();
        return ret;
    }
    
    int SCWatchString::trimRight(char c)
    {
        auto ret = this->SCString::trimRight(c);
        this->checkChange();
        return ret;
    }
    
    int SCWatchString::trimRight(const char* szStr)
    {
        auto ret = this->SCString::trimRight(szStr);
        this->checkChange();
        return ret;
    }
    
    int SCWatchString::trimRight(const std::string& str)
    {
        auto ret = this->SCString::trimRight(str);
        this->checkChange();
        return ret;
    }
    
    int SCWatchString::trimLeft(char c)
    {
        auto ret = this->SCString::trimLeft(c);
        this->checkChange();
        return ret;
    }
    
    int SCWatchString::trimLeft(const char* szStr)
    {
        auto ret = this->SCString::trimLeft(szStr);
        this->checkChange();
        return ret;
    }
    
    int SCWatchString::trimLeft(const std::string& str)
    {
        auto ret = this->SCString::trimLeft(str);
        this->checkChange();
        return ret;
    }
    
    void SCWatchString::makeUpper()
    {
        this->SCString::makeUpper();
        this->checkChange();
    }
    
    void SCWatchString::makeLower()
    {
        this->SCString::makeLower();
        this->checkChange();
    }
    
    void SCWatchString::setAt(const int nIndex, const char ch)
    {
        this->SCString::setAt(nIndex,ch);
        this->checkChange();
    }
    
    const SCString& SCWatchString::operator+=(const SCString& string)
    {
        this->SCString::operator+=(string);
        this->checkChange();
        return *this;
    }
    
    const SCString& SCWatchString::operator+=(char ch)
    {
        this->SCString::operator+=(ch);
        this->checkChange();
        return *this;
    }
    
    const SCString& SCWatchString::operator+=(const char* psz)
    {
        this->SCString::operator+=(psz);
        this->checkChange();
        return *this;
    }
    
    const SCString& SCWatchString::operator+=(const std::string& str)
    {
        this->SCString::operator+=(str);
        this->checkChange();
        return *this;
    }
    
    const SCString& SCWatchString::operator+=(const int nNumber)
    {
        this->SCString::operator+=(nNumber);
        this->checkChange();
        return *this;
    }
    
    const SCString& SCWatchString::operator+=(const float fNumber)
    {
        this->SCString::operator+=(fNumber);
        this->checkChange();
        return *this;
    }
    
    const SCString& SCWatchString::operator+=(const unsigned uNumber)
    {
        this->SCString::operator+=(uNumber);
        this->checkChange();
        return *this;
    }
    
    const SCString& SCWatchString::operator+=(const SCEncodingChar& encodingChar)
    {
        this->SCString::operator+=(encodingChar);
        this->checkChange();
        return *this;
    }
    
    // assign
    const SCString& SCWatchString::operator=(const SCString& stringSrc)
    {
        this->SCString::operator=(stringSrc);
        this->checkChange();
        return *this;
    }
    
    const SCString& SCWatchString::operator=(char ch)
    {
        this->SCString::operator=(ch);
        this->checkChange();
        return *this;
    }
    
    const SCString& SCWatchString::operator=(const char* psz)
    {
        this->SCString::operator=(psz);
        this->checkChange();
        return *this;
    }
    
    const SCString& SCWatchString::operator=(const unsigned short* pszStr)
    {
        this->SCString::operator=(pszStr);
        this->checkChange();
        return *this;
    }
    
    const SCString& SCWatchString::operator=(const std::string& str)
    {
        this->SCString::operator=(str);
        this->checkChange();
        return *this;
    }
    
    const SCString& SCWatchString::operator=(const SCEncodingChar& encodingChar)
    {
        this->SCString::operator=(encodingChar);
        this->checkChange();
        return *this;
    }
    
    const SCString& SCWatchString::operator=(const int nNumber)
    {
        this->SCString::operator=(nNumber);
        this->checkChange();
        return *this;
    }
    
    const SCString& SCWatchString::operator=(const unsigned uNumber)
    {
        this->SCString::operator=(uNumber);
        this->checkChange();
        return *this;
    }
    
    
}


