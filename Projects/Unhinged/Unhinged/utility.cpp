//
//  utility.cpp
//  Unhinged
//
//  Created by Arsh Malik on 3/9/22.
//

#include "utility.h"

bool compareEmailCounts(const EmailCount& lhs, const EmailCount& rhs)
{
    if (lhs.count>rhs.count)
        return true;
    else if (lhs.count<rhs.count)
        return false;
    else if (lhs.email<rhs.email)
        return true;
    return false;
}
