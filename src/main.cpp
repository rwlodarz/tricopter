/*
 * main.cpp
 *
 *  Created on: Jul 3, 2015
 *      Author: rwlodarz
 */

#include "lib/include/logger.hpp"
#include "include/pid.hpp"

int main()
{
    PidConfiguration config {1, 0, 0, 0.1, -10, 10};
    Pid pid(config,1);

    for(int i = 0; i < 100000; ++i)
        LOG(ERROR, "dupa");

    return 0;
}
