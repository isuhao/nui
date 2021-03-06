#include "stdafx.h"

#include "../NModule.h"
#include "../../base/NString.h"
#include "../../Util/NFileUtil.h"


namespace nui
{
    namespace Data
    {
        NModule NModule::instance_;

        NModule::NModule()
        {
            nuiModule_ = ::GetModuleHandle(NULL);
            bigIcon_ = NULL;
            smallIcon_ = NULL;
            mainThreadId_ = 0;
        }

        NModule::~NModule()
        {
            nuiModule_ = NULL;
        }

        NModule& NModule::GetInst()
        {
            return instance_;
        }

        bool NModule::Init(HMODULE nuiModule)
        {
            if(nuiModule != NULL)
                nuiModule_ = nuiModule;

            TCHAR tempPath[1024];
            ::GetModuleFileName(NULL, tempPath, 1024);
            appFullName_ = tempPath;
            appPath_ = Util::File::GetParentFolder(tempPath);
            mainThreadId_ = ::GetCurrentThreadId();
            return true;
        }

        bool NModule::IsValid() const
        {
            return (nuiModule_ != NULL);
        }

        HICON NModule::GetBigIcon()
        {
            if(bigIcon_ != NULL)
                return bigIcon_;
            ::ExtractIconEx(appFullName_, 0, &bigIcon_, &smallIcon_, 1);
            return bigIcon_;
        }

        HICON NModule::GetSmallIcon()
        {
            if(smallIcon_ != NULL)
                return smallIcon_;
            ::ExtractIconEx(GetAppPath(), 0, &bigIcon_, &smallIcon_, 1);
            return smallIcon_;
        }

        HMODULE NModule::GetNUIModule() const
        {
            return nuiModule_;
        }

        Base::NString NModule::GetAppPath() const
        {
            return appPath_;
        }

        Base::NString NModule::GetAppFullName() const
        {
            return appFullName_;
        }

        DWORD NModule::GetMainThreadId() const
        {
            return mainThreadId_;
        }
    }
};
