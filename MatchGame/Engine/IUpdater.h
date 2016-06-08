//
//  IUpdater.h
//  MatchGame
//
//  Created by Xuan Yuan (Frank) on 4/26/16.
//  Copyright © 2016 frank-yuan. All rights reserved.
//

#ifndef IUpdater_h
#define IUpdater_h

namespace XYGame
{
    class IUpdater
    {
    public:
        virtual void Update() = 0;
    protected:
        ~IUpdater(){}
    };
}
#endif /* IUpdater_h */
