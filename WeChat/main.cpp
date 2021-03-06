// main.cpp : Defines the entry point for the application.
//

#include "stdafx.h"

#include "LoginUi.h"
#include "MainUi.h"
#include "HttpUtil.h"
#include "MiscUtil.h"


nui::Base::NString GetResourcePath();

int APIENTRY _tWinMain(HINSTANCE hInstance,
                       HINSTANCE hPrevInstance,
                       LPTSTR    lpCmdLine,
                       int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);


    HttpUtil::InitHttpUtil();

    nui::Data::NModule::GetInst().Init(::GetModuleHandle(NULL));

    nui::Base::NString resPath = GetResourcePath();
    nui::Base::NInstPtr<nui::Base::NCore> core(MemToolParam);
    core->InitCore(resPath.GetData(), _T("2052"), NRenderType::GdiRender);

    bool needShowMainUi = false;
    {
        LoginUi loginUi;
        needShowMainUi = loginUi.Show();
    }

    bool needRestart = false;
    if(needShowMainUi)
    {
        MainUi mainUi;
        needRestart = mainUi.Show();
    }

    core->DestroyCore();

    HttpUtil::UnInitHttpUtil();

    if(needRestart)
    {
        TCHAR selfPath[1024] = _T("");
        ::GetModuleFileName(NULL, selfPath, _countof(selfPath));
        ::ShellExecute(NULL, _T("open"), selfPath, NULL, NULL, SW_SHOW);
    }
    return 0;
}



nui::Base::NString GetResourcePath()
{
    nui::Base::NString resPath = nui::Data::NModule::GetInst().GetAppPath();
    nui::Base::NString tmp = nui::Util::File::CombinePath(resPath, _T("WeChat"));
    if(!nui::Util::File::IsFolderExists(tmp.GetData()))
    {
        tmp = nui::Util::File::GetParentFolder(tmp);
        tmp = nui::Util::File::GetParentFolder(tmp);
        tmp = nui::Util::File::GetParentFolder(tmp);
        tmp = nui::Util::File::CombinePath(tmp, _T("uidata"));
        tmp = nui::Util::File::CombinePath(tmp, _T("WeChat"));
    }
    return tmp;
}