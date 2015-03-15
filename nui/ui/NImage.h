#pragma once



#include "../base/BaseObj.h"
#include "../base/DataTypes.h"

namespace nui
{
    namespace Ui
    {
        class NUI_INTF NImage : public Base::NBaseObj
        {
        public:
            virtual LPVOID LockBits() = 0;
            virtual void UnlockBits(LPVOID bits) = 0;

            virtual int NextDelayValue(int index) = 0;
            virtual int GetFrameCount() const = 0;

            virtual const Base::NSize& GetSize() const  = 0;
            virtual bool SetCount(int horzCount, int vertCount) = 0;
            virtual void GetCount(int& horzCount, int& vertCount) const = 0;
        };
    }
}