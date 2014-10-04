#include "stdafx.h"
#include "../NString.h"

#include <algorithm>

namespace NUI
{
    namespace Base
    {

        NString::NString()
        {
            argPos_ = 1;
        }

        NString::NString(const NString& arg)
        {
            argPos_ = arg.argPos_;
            data_ = arg.data_;
        }

        NString::NString(LPCTSTR arg)
        {
            argPos_ = 1;
            data_ = arg;
        }

        NString& NString::operator = (const NString& arg)
        {
            if(this != &arg)
            {
                argPos_ = arg.argPos_;
                data_ = arg.data_;
            }
            return (*this);
        }

        NString::~NString()
        {
            ;
        }

        NString& NString::operator = (TCHAR arg)
        {
            data_ = arg;
            return (*this);
        }

        NString& NString::operator = (LPCTSTR arg)
        {
            data_ = arg;
            return (*this);
        }

        NString NString::operator + (TCHAR arg) const
        {
            NString result(*this);
            result += arg;
            return result;
        }

        NString& NString::operator += (TCHAR arg)
        {
            data_ += arg;
            return (*this);
        }

        NString NString::operator + (LPCTSTR arg) const
        {
            NString result(*this);
            result += arg;
            return result;
        }

        NString& NString::operator += (LPCTSTR arg)
        {
            data_ += arg;
            return (*this);
        }

        bool NString::operator == (LPCTSTR arg) const
        {
            return (data_ == arg);
        }

        bool NString::operator != (LPCTSTR arg) const
        {
            return (data_ != arg);
        }

        NString NString::operator + (NString arg) const
        {
            NString result(*this);
            result += arg;
            return result;
        }

        NString& NString::operator += (NString arg)
        {
            data_ += arg.data_;
            return (*this);
        }

        bool NString::operator == (NString arg) const
        {
            return data_ == arg.data_;
        }

        bool NString::operator != (NString arg) const
        {
            return data_ != arg.data_;
        }

        NString& NString::Assign(LPCTSTR arg, size_t length)
        {
            argPos_ = 1;
            data_.assign(arg, length);
            return (*this);
        }

        NString& NString::MakeLower()
        {
            std::transform(data_.begin(), data_.end(), data_.begin(), &::_totlower);
            return (*this);
        }

        NString& NString::MakeUpper()
        {
            std::transform(data_.begin(), data_.end(), data_.begin(), &::_totupper);
            return (*this);
        }

        NString& NString::Trim()
        {
            if(IsEmpty())
                return (*this);

            LPCTSTR start = data_.c_str();

            // Right
            LPCTSTR end = data_.c_str() + data_.length() - 1;
            while(end > start && _istspace(*end))
            {
                -- end;
            }

            // Left
            while(_istspace(*start) && (*start))
            {
                ++ start;
            }

            if(start == end)
                data_ = TEXT("");
            else
                data_ = data_.substr(start - data_.c_str(), end - start + 1);

            return (*this);
        }

        NString& NString::Replace(LPCTSTR szSrc, LPCTSTR szDes)
        {
            if(szSrc == NULL || szSrc[0] == 0 || szDes == NULL)
                return (*this);

            size_t nSrcLength = _tcslen(szSrc);
            size_t nDesLength = _tcslen(szDes);

            size_t pos = 0;
            while( (pos = data_.find(szSrc, pos)) != tstring::npos)
            {
                data_.replace(pos, nSrcLength, szDes);
                if(nDesLength > nSrcLength)
                    pos += (nDesLength - nSrcLength) + 1;
                else
                    pos += nDesLength;
            }
            return (*this);
        }

        NString NString::SubString(size_t startPos)
        {
            if(startPos < 0 || startPos >= data_.length())
                return _T("");
            NString result;
            result.data_ = data_.substr(startPos);
            return result;
        }

        NString NString::SubString(size_t startPos, size_t count)
        {
            if(startPos + count < 0 || startPos + count >= data_.length())
                return _T("");
            NString result;
            result.data_ = data_.substr(startPos, count);
            return result;
        }

        bool NString::CompareNoCases(LPCTSTR arg) const
        {
            NString lowerData(data_.c_str());
            NString lowerArg(arg);
            lowerData.MakeLower();
            lowerArg.MakeLower();
            return (lowerData == lowerArg);
        }

        bool NString::IsEmpty() const
        {
            return data_.empty();
        }

        size_t NString::IndexOf(LPCTSTR arg) const
        {
            size_t pos = data_.find(arg);
            if(pos == tstring::npos)
                return -1;
            return pos;
        }

        size_t NString::IndexOf(LPCTSTR arg, size_t startPos) const
        {
            size_t pos = data_.find(arg, startPos);
            if(pos == tstring::npos)
                return -1;
            return pos;
        }

        size_t NString::LastIndexOf(LPCTSTR arg) const
        {
            size_t pos = data_.rfind(arg);
            if(pos == tstring::npos)
                return -1;
            return pos;
        }

        size_t NString::LastIndexOf(LPCTSTR arg, size_t startPos) const
        {
            size_t pos = data_.rfind(arg, startPos);
            if(pos == tstring::npos)
                return -1;
            return pos;
        }

        size_t NString::IndexOf(TCHAR arg) const
        {
            size_t pos = data_.find(arg);
            if(pos == tstring::npos)
                return -1;
            return pos;
        }

        size_t NString::IndexOf(TCHAR arg, size_t startPos) const
        {
            size_t pos = data_.find(arg, startPos);
            if(pos == tstring::npos)
                return -1;
            return pos;
        }

        size_t NString::LastIndexOf(TCHAR arg) const
        {
            size_t pos = data_.rfind(arg);
            if(pos == tstring::npos)
                return -1;
            return pos;
        }

        size_t NString::LastIndexOf(TCHAR arg, size_t startPos) const
        {
            size_t pos = data_.rfind(arg, startPos);
            if(pos == tstring::npos)
                return -1;
            return pos;
        }

        LPCTSTR NString::GetData() const
        {
            return data_.c_str();
        }

        size_t NString::GetLength() const
        {
            return data_.length();
        }

        NString& NString::Format(LPCTSTR szFormat, ...)
        {
            va_list args;
            va_start(args, szFormat);

            const int nDefaultBufferSize = 256;
            TCHAR szBuffer[nDefaultBufferSize] = {0};
            int nCount = _vsctprintf(szFormat, args);
            if(nCount + 1 < nDefaultBufferSize)
            {
                nCount = _vsntprintf(szBuffer, nDefaultBufferSize, szFormat, args);
                if(nCount > 0)
                    data_ = szBuffer;
            }
            else
            {
                TCHAR* pBuffer = NNewArray<TCHAR>(nCount + 1);
                nCount = _vsntprintf(pBuffer, nCount, szFormat, args);
                if(nCount > 0)
                {
                    pBuffer[nCount] = 0;
                    data_ = szBuffer;
                }
                NFreeArray(pBuffer);
            }
            return (*this);
        }

        bool NString::Tokenize(size_t& position, LPCTSTR szSplitter, bool includeEmpty, NString& token) const
        {
            if(position == -1)
                return false;

            if(szSplitter == NULL || szSplitter[0] == 0)
            {
                if(position < data_.length())
                {
                    token = data_[position];
                    ++ position;
                    return true;
                }
                else
                {
                    token = _T("");
                    position = -1;
                    return false;
                }
            }

            size_t last = position;
            position = data_.find(szSplitter, position);
            if(position == tstring::npos)
            {
                if(last > 0 && last < data_.length())
                {
                    position = -1;
                    token = data_.substr(last).c_str();
                    return true;
                }
                position = -1;
                return false;
            }

            size_t splitterLen = _tcslen(szSplitter);
            if(position == last)
            {
                position += splitterLen;
                if(includeEmpty)
                {
                    token = TEXT("");
                    return true;
                }
                else
                {
                    return Tokenize(position, szSplitter, includeEmpty, token);
                }
            }
            else
            {
                token.Assign(data_.c_str() + last, position - last);
                position += splitterLen;
                return true;
            }
        }

        NString NString::arg(LPCTSTR wstr) const
        {
            return ArgImpl(wstr);
        }

        NString NString::arg(short n) const
        {
            TCHAR szBuffer[10];
            _sntprintf(szBuffer, 10, _T("%hd"), n);
            return ArgImpl(szBuffer);
        }

        NString NString::arg(unsigned short n) const
        {
            TCHAR szBuffer[10];
            _sntprintf(szBuffer, 10, _T("%hu"), n);
            return ArgImpl(szBuffer);
        }

        NString NString::arg(int n) const
        {
            TCHAR szBuffer[15];
            _sntprintf(szBuffer, 15, _T("%d"), n);
            return ArgImpl(szBuffer);
        }

        NString NString::arg(unsigned int n) const
        {
            TCHAR szBuffer[15];
            _sntprintf(szBuffer, 15, _T("%u"), n);
            return ArgImpl(szBuffer);
        }

        NString NString::arg(long n) const
        {
            TCHAR szBuffer[15];
            _sntprintf(szBuffer, 15, _T("%ld"), n);
            return ArgImpl(szBuffer);
        }

        NString NString::arg(unsigned long n) const
        {
            TCHAR szBuffer[15];
            _sntprintf(szBuffer, 15, _T("%u"), n);
            return ArgImpl(szBuffer);
        }

        NString NString::arg(LONGLONG n) const
        {
            TCHAR szBuffer[40];
            _sntprintf(szBuffer, 40, _T("%I64d"), n);
            return ArgImpl(szBuffer);
        }

        NString NString::arg(ULONGLONG n) const
        {
            TCHAR szBuffer[40];
            _sntprintf(szBuffer, 40, _T("%I64u"), n);
            return ArgImpl(szBuffer);
        }

        NString NString::arg(wchar_t n) const
        {
            TCHAR szBuffer[5];
            _sntprintf(szBuffer, 5, _T("%c"), n);
            return ArgImpl(szBuffer);
        }

        NString NString::arg(double d) const
        {
            TCHAR szBuffer[50];
            _sntprintf(szBuffer, 50, _T("%lf"), d);
            return ArgImpl(szBuffer);
        }

        NString NString::arg(const NString& str) const
        {
            return ArgImpl(str.GetData());
        }

        TCHAR& NString::operator [] (size_t index)
        {
            return data_[index];
        }

        NString NString::ArgImpl(LPCTSTR str) const
        {
            tstring strTemp;
            NString strResult;

            TCHAR szBuffer[50];
            _sntprintf(szBuffer, 50, _T("%%%d"), argPos_);
            strTemp = szBuffer;

            size_t pos = data_.find(strTemp);
            if(pos == std::wstring::npos)
                return (*this);

            strResult.data_ = data_.substr(0, pos);
            strResult.data_ += str;
            strResult.data_ += data_.substr(pos + strTemp.length());
            strResult.argPos_ = argPos_ + 1;
            return strResult;
        }

    }
}